/**
 * @license
 * Copyright 2019 Google LLC. All Rights Reserved.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * =============================================================================
 */
import { ENGINE } from '../../engine';
import { customGrad } from '../../gradients';
import { FusedConv2D } from '../../kernel_names';
import { makeTypesMatch } from '../../tensor_util';
import { convertToTensor } from '../../tensor_util_env';
import * as util from '../../util';
import { add } from '../add';
import * as broadcast_util from '../broadcast_util';
import { conv2d as unfusedConv2d } from '../conv2d';
import { conv2DBackpropFilter } from '../conv2d_backprop_filter';
import { conv2DBackpropInput } from '../conv2d_backprop_input';
import * as conv_util from '../conv_util';
import { applyActivation, getFusedBiasGradient, getFusedDyActivation, shouldFuse } from '../fused_util';
import { op } from '../operation';
import { reshape } from '../reshape';
/**
 * Computes a 2D convolution over the input x, optionally fused with adding a
 * bias and applying an activation.
 *
 * ```js
 * const inputDepth = 2;
 * const inShape = [2, 2, 2, inputDepth];
 * const outputDepth = 2;
 * const fSize = 1;
 * const pad = 0;
 * const strides = 1;
 *
 * const x = tf.tensor4d( [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
 * 16], inShape);
 * const w = tf.tensor4d([-1, 1, -2, 0.5], [fSize, fSize, inputDepth,
 * outputDepth]);
 *
 * tf.fused.conv2d({ x, filter: w, strides, pad, dataFormat: 'NHWC',
 * dilations: [1, 1], bias: tf.scalar(5), activation: 'relu' }).print();
 * ```
 *
 * @param obj An object with the following properties:
 * @param x The input tensor, of rank 4 or rank 3, of shape
 *     `[batch, height, width, inChannels]`. If rank 3, batch of 1 is
 * assumed.
 * @param filter The filter, rank 4, of shape
 *     `[filterHeight, filterWidth, inDepth, outDepth]`.
 * @param strides The strides of the convolution: `[strideHeight,
 * strideWidth]`.
 * @param pad The type of padding algorithm.
 *   - `same` and stride 1: output will be of same size as input,
 *       regardless of filter size.
 *   - `valid` output will be smaller than input if filter is larger
 *       than 1x1.
 *   - For more info, see this guide:
 *     [https://www.tensorflow.org/api_docs/python/tf/nn/convolution](
 *          https://www.tensorflow.org/api_docs/python/tf/nn/convolution)
 * @param dataFormat An optional string from: "NHWC", "NCHW". Defaults to
 *     "NHWC". Specify the data format of the input and output data. With the
 *     default format "NHWC", the data is stored in the order of: [batch,
 *     height, width, channels]. Only "NHWC" is currently supported.
 * @param dilations The dilation rates: `[dilationHeight, dilationWidth]`
 *     in which we sample input values across the height and width dimensions
 *     in atrous convolution. Defaults to `[1, 1]`. If `dilations` is a single
 *     number, then `dilationHeight == dilationWidth`. If it is greater than
 *     1, then all values of `strides` must be 1.
 * @param dimRoundingMode A string from: 'ceil', 'round', 'floor'. If none is
 *     provided, it will default to truncate.
 * @param bias Tensor to be added to the result.
 * @param activation Name of activation kernel (defaults to `linear`) to be
 *     applied
 *      after biasAdd.
 * @param preluActivationWeights Tensor of prelu weights to be applied as part
 *     of a `prelu` activation, typically the same shape as `x`.
 * @param leakyreluAlpha Optional. Alpha to be applied as part of a `leakyrelu`
 *     activation.
 */
function fusedConv2d_({ x, filter, strides, pad, dataFormat = 'NHWC', dilations = [1, 1], dimRoundingMode, bias, activation = 'linear', preluActivationWeights, leakyreluAlpha }) {
    activation = activation || 'linear';
    if (shouldFuse(ENGINE.state.gradientDepth, activation) === false) {
        // TODO: Transpose bias and preluActivationWeights properly for NCHW
        // format before computation.
        util.assert(dataFormat === 'NHWC', () => `Error in fused conv2d: got dataFormat of ${dataFormat} but ` +
            `only NHWC is currently supported for the case of gradient depth ` +
            `is 0 and the activation is not linear.`);
        let result = unfusedConv2d(x, filter, strides, pad, dataFormat, dilations, dimRoundingMode);
        if (bias != null) {
            result = add(result, bias);
        }
        return applyActivation(result, activation, preluActivationWeights, leakyreluAlpha);
    }
    const $x = convertToTensor(x, 'x', 'conv2d', 'float32');
    const $filter = convertToTensor(filter, 'filter', 'conv2d', 'float32');
    let x4D = $x;
    let reshapedTo4D = false;
    if ($x.rank === 3) {
        reshapedTo4D = true;
        x4D = reshape($x, [1, $x.shape[0], $x.shape[1], $x.shape[2]]);
    }
    util.assert(x4D.rank === 4, () => `Error in fused conv2d: input must be rank 4, but got rank ` +
        `${x4D.rank}.`);
    util.assert($filter.rank === 4, () => `Error in fused conv2d: filter must be rank 4, but got rank ` +
        `${$filter.rank}.`);
    conv_util.checkPadOnDimRoundingMode('fused conv2d', pad, dimRoundingMode);
    const inputChannels = dataFormat === 'NHWC' ? x4D.shape[3] : x4D.shape[1];
    util.assert($filter.shape[2] === inputChannels, () => `Error in conv2d: depth of input (${inputChannels}) must match ` +
        `input depth for filter ${$filter.shape[2]}.`);
    util.assert(conv_util.eitherStridesOrDilationsAreOne(strides, dilations), () => 'Error in conv2D: Either strides or dilations must be 1. ' +
        `Got strides ${strides} and dilations '${dilations}'`);
    const convInfo = conv_util.computeConv2DInfo(x4D.shape, $filter.shape, strides, dilations, pad, dimRoundingMode);
    let $bias;
    if (bias != null) {
        $bias = convertToTensor(bias, 'bias', 'fused conv2d');
        [$bias] = makeTypesMatch($bias, $x);
        // According to TensorFlow, the bias is supposed be a 1-D tensor or a
        // scalar.
        if (dataFormat === 'NHWC') {
            broadcast_util.assertAndGetBroadcastShape(convInfo.outShape, $bias.shape);
        }
        else {
            util.assert($bias.shape.length <= 1, () => `Error in fused conv2d: only supports scalar or 1-D Tensor ` +
                `bias for NCHW format but got the bias of ` +
                `rank-${$bias.shape.length}.`);
            util.assert($bias.shape.length === 0 || $bias.shape[0] === convInfo.outChannels ||
                $bias.shape[0] === 1, () => `Error in fused conv2d: bias shape (${$bias.shape}) is not ` +
                `compatible with the number of output channels ` +
                `(${convInfo.outChannels})`);
        }
    }
    let $preluActivationWeights;
    if (preluActivationWeights != null) {
        // PReLU's activation weights could be a scalar, a 1-D tensor or a 3-D
        // tensor.
        const alphaShape = preluActivationWeights.shape;
        util.assert(alphaShape.length <= 1 || alphaShape.length === 3, () => `Error in fused conv2d: only supports scalar, 1-D Tensor or ` +
            `3-D Tensor PReLU activation weights but got a tensor of ` +
            `rank-${alphaShape.length}.`);
        if (alphaShape.length === 1) {
            // Whether the data format is NCHW or NHWC, the 1-D PReLU activation
            // weights tensor should be aligned with the output channels of conv2d
            // result.
            util.assert(alphaShape[0] === 1 || alphaShape[0] === convInfo.outChannels, () => `Error in fused conv2d: PReLU activation weights ` +
                `(${alphaShape}) is not compatible with the number of output ` +
                `channels (${convInfo.outChannels}).`);
        }
        else if (alphaShape.length === 3) {
            // Whether the data format is NCHW or NHWC, the PReLU activation weights
            // tensor should has the compatible shape with the result of conv2d.
            try {
                broadcast_util.assertAndGetBroadcastShape(alphaShape, convInfo.outShape);
            }
            catch (e) {
                const errMsg = `Error in fused conv2d: PReLU activation weights (${alphaShape}) ` +
                    `is not compatible with the output shape of the conv2d ` +
                    `(${convInfo.outShape}).`;
                throw Error(errMsg);
            }
        }
        $preluActivationWeights = convertToTensor(preluActivationWeights, 'prelu weights', 'fused conv2d');
    }
    const grad = (dy, saved) => {
        util.assert(dataFormat === 'NHWC', () => `Error in gradient of fused conv2D: got dataFormat of ${dataFormat} but only NHWC is currently supported.`);
        const [$filter, x4D, y, $bias] = saved;
        const dyActivation = getFusedDyActivation(dy, y, activation);
        util.assert(conv_util.tupleValuesAreOne(dilations), () => 'Error in gradient of fused conv2D: ' +
            `dilation rates greater than 1 ` +
            `are not yet supported in gradients. Got dilations '${dilations}'`);
        const xDer = conv2DBackpropInput(x4D.shape, dyActivation, $filter, strides, pad);
        const filterDer = conv2DBackpropFilter(x4D, dyActivation, $filter.shape, strides, pad);
        const der = [xDer, filterDer];
        if ($bias != null) {
            const biasDer = getFusedBiasGradient($bias, dyActivation);
            der.push(biasDer);
        }
        return der;
    };
    const inputs = {
        x: x4D,
        filter: $filter,
        bias: $bias,
        preluActivationWeights: $preluActivationWeights
    };
    const attrs = {
        strides,
        pad,
        dataFormat,
        dilations,
        dimRoundingMode,
        activation,
        leakyreluAlpha
    };
    // Depending on the the params passed in we will have different number of
    // inputs and thus a a different number of elements in the gradient.
    if (bias == null) {
        const customOp = customGrad((x4D, filter, save) => {
            let res = 
            // tslint:disable-next-line: no-unnecessary-type-assertion
            ENGINE.runKernel(FusedConv2D, inputs, attrs);
            save([filter, x4D, res]);
            if (reshapedTo4D) {
                // tslint:disable-next-line: no-unnecessary-type-assertion
                res = reshape(res, [res.shape[1], res.shape[2], res.shape[3]]);
            }
            return { value: res, gradFunc: grad };
        });
        return customOp(x4D, $filter);
    }
    else {
        const customOpWithBias = customGrad((x4D, filter, bias, save) => {
            let res = ENGINE.runKernel(FusedConv2D, inputs, attrs);
            save([filter, x4D, res, bias]);
            if (reshapedTo4D) {
                // tslint:disable-next-line: no-unnecessary-type-assertion
                res = reshape(res, [res.shape[1], res.shape[2], res.shape[3]]);
            }
            return { value: res, gradFunc: grad };
        });
        return customOpWithBias(x4D, $filter, $bias);
    }
}
export const conv2d = op({ fusedConv2d_ });
//# sourceMappingURL=data:application/json;base64,eyJ2ZXJzaW9uIjozLCJmaWxlIjoiY29udjJkLmpzIiwic291cmNlUm9vdCI6IiIsInNvdXJjZXMiOlsiLi4vLi4vLi4vLi4vLi4vLi4vLi4vdGZqcy1jb3JlL3NyYy9vcHMvZnVzZWQvY29udjJkLnRzIl0sIm5hbWVzIjpbXSwibWFwcGluZ3MiOiJBQUFBOzs7Ozs7Ozs7Ozs7Ozs7R0FlRztBQUVILE9BQU8sRUFBQyxNQUFNLEVBQUMsTUFBTSxjQUFjLENBQUM7QUFDcEMsT0FBTyxFQUFDLFVBQVUsRUFBQyxNQUFNLGlCQUFpQixDQUFDO0FBQzNDLE9BQU8sRUFBQyxXQUFXLEVBQXNDLE1BQU0sb0JBQW9CLENBQUM7QUFJcEYsT0FBTyxFQUFDLGNBQWMsRUFBQyxNQUFNLG1CQUFtQixDQUFDO0FBQ2pELE9BQU8sRUFBQyxlQUFlLEVBQUMsTUFBTSx1QkFBdUIsQ0FBQztBQUV0RCxPQUFPLEtBQUssSUFBSSxNQUFNLFlBQVksQ0FBQztBQUNuQyxPQUFPLEVBQUMsR0FBRyxFQUFDLE1BQU0sUUFBUSxDQUFDO0FBQzNCLE9BQU8sS0FBSyxjQUFjLE1BQU0sbUJBQW1CLENBQUM7QUFDcEQsT0FBTyxFQUFDLE1BQU0sSUFBSSxhQUFhLEVBQUMsTUFBTSxXQUFXLENBQUM7QUFDbEQsT0FBTyxFQUFDLG9CQUFvQixFQUFDLE1BQU0sMkJBQTJCLENBQUM7QUFDL0QsT0FBTyxFQUFDLG1CQUFtQixFQUFDLE1BQU0sMEJBQTBCLENBQUM7QUFDN0QsT0FBTyxLQUFLLFNBQVMsTUFBTSxjQUFjLENBQUM7QUFFMUMsT0FBTyxFQUFDLGVBQWUsRUFBRSxvQkFBb0IsRUFBRSxvQkFBb0IsRUFBRSxVQUFVLEVBQUMsTUFBTSxlQUFlLENBQUM7QUFDdEcsT0FBTyxFQUFDLEVBQUUsRUFBQyxNQUFNLGNBQWMsQ0FBQztBQUNoQyxPQUFPLEVBQUMsT0FBTyxFQUFDLE1BQU0sWUFBWSxDQUFDO0FBRW5DOzs7Ozs7Ozs7Ozs7Ozs7Ozs7Ozs7Ozs7Ozs7Ozs7Ozs7Ozs7Ozs7Ozs7Ozs7Ozs7Ozs7Ozs7OztHQXdERztBQUNILFNB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LENBQUMsR0FBYSxFQUFFLE1BQWdCLEVBQUUsSUFBWSxFQUFFLElBQWtCLEVBQUUsRUFBRTtZQUNwRSxJQUFJLEdBQUcsR0FBc0IsTUFBTSxDQUFDLFNBQVMsQ0FDekMsV0FBVyxFQUFFLE1BQThCLEVBQzNDLEtBQTJCLENBQUMsQ0FBQztZQUVqQyxJQUFJLENBQUMsQ0FBQyxNQUFNLEVBQUUsR0FBRyxFQUFFLEdBQUcsRUFBRSxJQUFJLENBQUMsQ0FBQyxDQUFDO1lBRS9CLElBQUksWUFBWSxFQUFFO2dCQUNoQiwwREFBMEQ7Z0JBQzFELEdBQUcsR0FBRyxPQUFPLENBQUMsR0FBRyxFQUFFLENBQUMsR0FBRyxDQUFDLEtBQUssQ0FBQyxDQUFDLENBQUMsRUFBRSxHQUFHLENBQUMsS0FBSyxDQUFDLENBQUMsQ0FBQyxFQUFFLEdBQUcsQ0FBQyxLQUFLLENBQUMsQ0FBQyxDQUFDLENBQUMsQ0FDakQsQ0FBQzthQUNkO1lBRUQsT0FBTyxFQUFDLEtBQUssRUFBRSxHQUFHLEVBQUUsUUFBUSxFQUFFLElBQUksRUFBQyxDQUFDO1FBQ3RDLENBQUMsQ0FBQyxDQUFDO1FBRVAsT0FBTyxnQkFBZ0IsQ0FBQyxHQUFHLEVBQUUsT0FBTyxFQUFFLEtBQUssQ0FBTSxDQUFDO0tBQ25EO0FBQ0gsQ0FBQztBQUNELE1BQU0sQ0FBQyxNQUFNLE1BQU0sR0FBRyxFQUFFLENBQUMsRUFBQyxZQUFZLEVBQUMsQ0FBQyxDQUFDIiwic291cmNlc0NvbnRlbnQiOlsiLyoqXG4gKiBAbGljZW5zZVxuICogQ29weXJpZ2h0IDIwMTkgR29vZ2xlIExMQy4gQWxsIFJpZ2h0cyBSZXNlcnZlZC5cbiAqIExpY2Vuc2VkIHVuZGVyIHRoZSBBcGFjaGUgTGljZW5zZSwgVmVyc2lvbiAyLjAgKHRoZSBcIkxpY2Vuc2VcIik7XG4gKiB5b3UgbWF5IG5vdCB1c2UgdGhpcyBmaWxlIGV4Y2VwdCBpbiBjb21wbGlhbmNlIHdpdGggdGhlIExpY2Vuc2UuXG4gKiBZb3UgbWF5IG9idGFpbiBhIGNvcHkgb2YgdGhlIExpY2Vuc2UgYXRcbiAqXG4gKiBodHRwOi8vd3d3LmFwYWNoZS5vcmcvbGljZW5zZXMvTElDRU5TRS0yLjBcbiAqXG4gKiBVbmxlc3MgcmVxdWlyZWQgYnkgYXBwbGljYWJsZSBsYXcgb3IgYWdyZWVkIHRvIGluIHdyaXRpbmcsIHNvZnR3YXJlXG4gKiBkaXN0cmlidXRlZCB1bmRlciB0aGUgTGljZW5zZSBpcyBkaXN0cmlidXRlZCBvbiBhbiBcIkFTIElTXCIgQkFTSVMsXG4gKiBXSVRIT1VUIFdBUlJBTlRJRVMgT1IgQ09ORElUSU9OUyBPRiBBTlkgS0lORCwgZWl0aGVyIGV4cHJlc3Mgb3IgaW1wbGllZC5cbiAqIFNlZSB0aGUgTGljZW5zZSBmb3IgdGhlIHNwZWNpZmljIGxhbmd1YWdlIGdvdmVybmluZyBwZXJtaXNzaW9ucyBhbmRcbiAqIGxpbWl0YXRpb25zIHVuZGVyIHRoZSBMaWNlbnNlLlxuICogPT09PT09PT09PT09PT09PT09PT09PT09PT09PT09PT09PT09PT09PT09PT09PT09PT09PT09PT09PT09PT09PT09PT09PT09PT09PT1cbiAqL1xuXG5pbXBvcnQge0VOR0lORX0gZnJvbSAnLi4vLi4vZW5naW5lJztcbmltcG9ydCB7Y3VzdG9tR3JhZH0gZnJvbSAnLi4vLi4vZ3JhZGllbnRzJztcbmltcG9ydCB7RnVzZWRDb252MkQsIEZ1c2VkQ29udjJEQXR0cnMsIEZ1c2VkQ29udjJESW5wdXRzfSBmcm9tICcuLi8uLi9rZXJuZWxfbmFtZXMnO1xuaW1wb3J0IHtOYW1lZEF0dHJNYXB9IGZyb20gJy4uLy4uL2tlcm5lbF9yZWdpc3RyeSc7XG5pbXBvcnQge1RlbnNvciwgVGVuc29yM0QsIFRlbnNvcjREfSBmcm9tICcuLi8uLi90ZW5zb3InO1xuaW1wb3J0IHtHcmFkU2F2ZUZ1bmMsIE5hbWVkVGVuc29yTWFwfSBmcm9tICcuLi8uLi90ZW5zb3JfdHlwZXMnO1xuaW1wb3J0IHttYWtlVHlwZXNNYXRjaH0gZnJvbSAnLi4vLi4vdGVuc29yX3V0aWwnO1xuaW1wb3J0IHtjb252ZXJ0VG9UZW5zb3J9IGZyb20gJy4uLy4uL3RlbnNvcl91dGlsX2Vudic7XG5pbXBvcnQge1RlbnNvckxpa2V9IGZyb20gJy4uLy4uL3R5cGVzJztcbmltcG9ydCAqIGFzIHV0aWwgZnJvbSAnLi4vLi4vdXRpbCc7XG5pbXBvcnQge2FkZH0gZnJvbSAnLi4vYWRkJztcbmltcG9ydCAqIGFzIGJyb2FkY2FzdF91dGlsIGZyb20gJy4uL2Jyb2FkY2FzdF91dGlsJztcbmltcG9ydCB7Y29udjJkIGFzIHVuZnVzZWRDb252MmR9IGZyb20gJy4uL2NvbnYyZCc7XG5pbXBvcnQge2NvbnYyREJhY2twcm9wRmlsdGVyfSBmcm9tICcuLi9jb252MmRfYmFja3Byb3BfZmlsdGVyJztcbmltcG9ydCB7Y29udjJEQmFja3Byb3BJbnB1dH0gZnJvbSAnLi4vY29udjJkX2JhY2twcm9wX2lucHV0JztcbmltcG9ydCAqIGFzIGNvbnZfdXRpbCBmcm9tICcuLi9jb252X3V0aWwnO1xuaW1wb3J0IHtBY3RpdmF0aW9ufSBmcm9tICcuLi9mdXNlZF90eXBlcyc7XG5pbXBvcnQge2FwcGx5QWN0aXZhdGlvbiwgZ2V0RnVzZWRCaWFzR3JhZGllbnQsIGdldEZ1c2VkRHlBY3RpdmF0aW9uLCBzaG91bGRGdXNlfSBmcm9tICcuLi9mdXNlZF91dGlsJztcbmltcG9ydCB7b3B9IGZyb20gJy4uL29wZXJhdGlvbic7XG5pbXBvcnQge3Jlc2hhcGV9IGZyb20gJy4uL3Jlc2hhcGUnO1xuXG4vKipcbiAqIENvbXB1dGVzIGEgMkQgY29udm9sdXRpb24gb3ZlciB0aGUgaW5wdXQgeCwgb3B0aW9uYWxseSBmdXNlZCB3aXRoIGFkZGluZyBhXG4gKiBiaWFzIGFuZCBhcHBseWluZyBhbiBhY3RpdmF0aW9uLlxuICpcbiAqIGBgYGpzXG4gKiBjb25zdCBpbnB1dERlcHRoID0gMjtcbiAqIGNvbnN0IGluU2hhcGUgPSBbMiwgMiwgMiwgaW5wdXREZXB0aF07XG4gKiBjb25zdCBvdXRwdXREZXB0aCA9IDI7XG4gKiBjb25zdCBmU2l6ZSA9IDE7XG4gKiBjb25zdCBwYWQgPSAwO1xuICogY29uc3Qgc3RyaWRlcyA9IDE7XG4gKlxuICogY29uc3QgeCA9IHRmLnRlbnNvcjRkKCBbMSwgMiwgMywgNCwgNSwgNiwgNywgOCwgOSwgMTAsIDExLCAxMiwgMTMsIDE0LCAxNSxcbiAqIDE2XSwgaW5TaGFwZSk7XG4gKiBjb25zdCB3ID0gdGYudGVuc29yNGQoWy0xLCAxLCAtMiwgMC41XSwgW2ZTaXplLCBmU2l6ZSwgaW5wdXREZXB0aCxcbiAqIG91dHB1dERlcHRoXSk7XG4gKlxuICogdGYuZnVzZWQuY29udjJkKHsgeCwgZmlsdGVyOiB3LCBzdHJpZGVzLCBwYWQsIGRhdGFGb3JtYXQ6ICdOSFdDJyxcbiAqIGRpbGF0aW9uczogWzEsIDFdLCBiaWFzOiB0Zi5zY2FsYXIoNSksIGFjdGl2YXRpb246ICdyZWx1JyB9KS5wcmludCgpO1xuICogYGBgXG4gKlxuICogQHBhcmFtIG9iaiBBbiBvYmplY3Qgd2l0aCB0aGUgZm9sbG93aW5nIHByb3BlcnRpZXM6XG4gKiBAcGFyYW0geCBUaGUgaW5wdXQgdGVuc29yLCBvZiByYW5rIDQgb3IgcmFuayAzLCBvZiBzaGFwZVxuICogICAgIGBbYmF0Y2gsIGhlaWdodCwgd2lkdGgsIGluQ2hhbm5lbHNdYC4gSWYgcmFuayAzLCBiYXRjaCBvZiAxIGlzXG4gKiBhc3N1bWVkLlxuICogQHBhcmFtIGZpbHRlciBUaGUgZmlsdGVyLCByYW5rIDQsIG9mIHNoYXBlXG4gKiAgICAgYFtmaWx0ZXJIZWlnaHQsIGZpbHRlcldpZHRoLCBpbkRlcHRoLCBvdXREZXB0aF1gLlxuICogQHBhcmFtIHN0cmlkZXMgVGhlIHN0cmlkZXMgb2YgdGhlIGNvbnZvbHV0aW9uOiBgW3N0cmlkZUhlaWdodCxcbiAqIHN0cmlkZVdpZHRoXWAuXG4gKiBAcGFyYW0gcGFkIFRoZSB0eXBlIG9mIHBhZGRpbmcgYWxnb3JpdGhtLlxuICogICAtIGBzYW1lYCBhbmQgc3RyaWRlIDE6IG91dHB1dCB3aWxsIGJlIG9mIHNhbWUgc2l6ZSBhcyBpbnB1dCxcbiAqICAgICAgIHJlZ2FyZGxlc3Mgb2YgZmlsdGVyIHNpemUuXG4gKiAgIC0gYHZhbGlkYCBvdXRwdXQgd2lsbCBiZSBzbWFsbGVyIHRoYW4gaW5wdXQgaWYgZmlsdGVyIGlzIGxhcmdlclxuICogICAgICAgdGhhbiAxeDEuXG4gKiAgIC0gRm9yIG1vcmUgaW5mbywgc2VlIHRoaXMgZ3VpZGU6XG4gKiAgICAgW2h0dHBzOi8vd3d3LnRlbnNvcmZsb3cub3JnL2FwaV9kb2NzL3B5dGhvbi90Zi9ubi9jb252b2x1dGlvbl0oXG4gKiAgICAgICAgICBodHRwczovL3d3dy50ZW5zb3JmbG93Lm9yZy9hcGlfZG9jcy9weXRob24vdGYvbm4vY29udm9sdXRpb24pXG4gKiBAcGFyYW0gZGF0YUZvcm1hdCBBbiBvcHRpb25hbCBzdHJpbmcgZnJvbTogXCJOSFdDXCIsIFwiTkNIV1wiLiBEZWZhdWx0cyB0b1xuICogICAgIFwiTkhXQ1wiLiBTcGVjaWZ5IHRoZSBkYXRhIGZvcm1hdCBvZiB0aGUgaW5wdXQgYW5kIG91dHB1dCBkYXRhLiBXaXRoIHRoZVxuICogICAgIGRlZmF1bHQgZm9ybWF0IFwiTkhXQ1wiLCB0aGUgZGF0YSBpcyBzdG9yZWQgaW4gdGhlIG9yZGVyIG9mOiBbYmF0Y2gsXG4gKiAgICAgaGVpZ2h0LCB3aWR0aCwgY2hhbm5lbHNdLiBPbmx5IFwiTkhXQ1wiIGlzIGN1cnJlbnRseSBzdXBwb3J0ZWQuXG4gKiBAcGFyYW0gZGlsYXRpb25zIFRoZSBkaWxhdGlvbiByYXRlczogYFtkaWxhdGlvbkhlaWdodCwgZGlsYXRpb25XaWR0aF1gXG4gKiAgICAgaW4gd2hpY2ggd2Ugc2FtcGxlIGlucHV0IHZhbHVlcyBhY3Jvc3MgdGhlIGhlaWdodCBhbmQgd2lkdGggZGltZW5zaW9uc1xuICogICAgIGluIGF0cm91cyBjb252b2x1dGlvbi4gRGVmYXVsdHMgdG8gYFsxLCAxXWAuIElmIGBkaWxhdGlvbnNgIGlzIGEgc2luZ2xlXG4gKiAgICAgbnVtYmVyLCB0aGVuIGBkaWxhdGlvbkhlaWdodCA9PSBkaWxhdGlvbldpZHRoYC4gSWYgaXQgaXMgZ3JlYXRlciB0aGFuXG4gKiAgICAgMSwgdGhlbiBhbGwgdmFsdWVzIG9mIGBzdHJpZGVzYCBtdXN0IGJlIDEuXG4gKiBAcGFyYW0gZGltUm91bmRpbmdNb2RlIEEgc3RyaW5nIGZyb206ICdjZWlsJywgJ3JvdW5kJywgJ2Zsb29yJy4gSWYgbm9uZSBpc1xuICogICAgIHByb3ZpZGVkLCBpdCB3aWxsIGRlZmF1bHQgdG8gdHJ1bmNhdGUuXG4gKiBAcGFyYW0gYmlhcyBUZW5zb3IgdG8gYmUgYWRkZWQgdG8gdGhlIHJlc3VsdC5cbiAqIEBwYXJhbSBhY3RpdmF0aW9uIE5hbWUgb2YgYWN0aXZhdGlvbiBrZXJuZWwgKGRlZmF1bHRzIHRvIGBsaW5lYXJgKSB0byBiZVxuICogICAgIGFwcGxpZWRcbiAqICAgICAgYWZ0ZXIgYmlhc0FkZC5cbiAqIEBwYXJhbSBwcmVsdUFjdGl2YXRpb25XZWlnaHRzIFRlbnNvciBvZiBwcmVsdSB3ZWlnaHRzIHRvIGJlIGFwcGxpZWQgYXMgcGFydFxuICogICAgIG9mIGEgYHByZWx1YCBhY3RpdmF0aW9uLCB0eXBpY2FsbHkgdGhlIHNhbWUgc2hhcGUgYXMgYHhgLlxuICogQHBhcmFtIGxlYWt5cmVsdUFscGhhIE9wdGlvbmFsLiBBbHBoYSB0byBiZSBhcHBsaWVkIGFzIHBhcnQgb2YgYSBgbGVha3lyZWx1YFxuICogICAgIGFjdGl2YXRpb24uXG4gKi9cbmZ1bmN0aW9uIGZ1c2VkQ29udjJkXzxUIGV4dGVuZHMgVGVuc29yM0R8VGVuc29yNEQ+KHtcbiAgeCxcbiAgZmlsdGVyLFxuICBzdHJpZGVzLFxuICBwYWQsXG4gIGRhdGFGb3JtYXQgPSAnTkhXQycsXG4gIGRpbGF0aW9ucyA9IFsxLCAxXSxcbiAgZGltUm91bmRpbmdNb2RlLFxuICBiaWFzLFxuICBhY3RpdmF0aW9uID0gJ2xpbmVhcicsXG4gIHByZWx1QWN0aXZhdGlvbldlaWdodHMsXG4gIGxlYWt5cmVsdUFscGhhXG59OiB7XG4gIHg6IFR8VGVuc29yTGlrZSxcbiAgZmlsdGVyOiBUZW5zb3I0RHxUZW5zb3JMaWtlLFxuICBzdHJpZGVzOiBbbnVtYmVyLCBudW1iZXJdfG51bWJlcixcbiAgcGFkOiAndmFsaWQnfCdzYW1lJ3xudW1iZXJ8Y29udl91dGlsLkV4cGxpY2l0UGFkZGluZyxcbiAgZGF0YUZvcm1hdD86ICdOSFdDJ3wnTkNIVycsXG4gIGRpbGF0aW9ucz86IFtudW1iZXIsIG51bWJlcl18bnVtYmVyLFxuICBkaW1Sb3VuZGluZ01vZGU/OiAnZmxvb3InfCdyb3VuZCd8J2NlaWwnLFxuICBiaWFzPzogVGVuc29yfFRlbnNvckxpa2UsXG4gIGFjdGl2YXRpb24/OiBBY3RpdmF0aW9uLFxuICBwcmVsdUFjdGl2YXRpb25XZWlnaHRzPzogVGVuc29yLFxuICBsZWFreXJlbHVBbHBoYT86IG51bWJlclxufSk6IFQge1xuICBhY3RpdmF0aW9uID0gYWN0aXZhdGlvbiB8fCAnbGluZWFyJztcblxuICBpZiAoc2hvdWxkRnVzZShFTkdJTkUuc3RhdGUuZ3JhZGllbnREZXB0aCwgYWN0aXZhdGlvbikgPT09IGZhbHNlKSB7XG4gICAgLy8gVE9ETzogVHJhbnNwb3NlIGJpYXMgYW5kIHByZWx1QWN0aXZhdGlvbldlaWdodHMgcHJvcGVybHkgZm9yIE5DSFdcbiAgICAvLyBmb3JtYXQgYmVmb3JlIGNvbXB1dGF0aW9uLlxuICAgIHV0aWwuYXNzZXJ0KFxuICAgICAgICBkYXRhRm9ybWF0ID09PSAnTkhXQycsXG4gICAgICAgICgpID0+IGBFcnJvciBpbiBmdXNlZCBjb252MmQ6IGdvdCBkYXRhRm9ybWF0IG9mICR7ZGF0YUZvcm1hdH0gYnV0IGAgK1xuICAgICAgICAgICAgYG9ubHkgTkhXQyBpcyBjdXJyZW50bHkgc3VwcG9ydGVkIGZvciB0aGUgY2FzZSBvZiBncmFkaWVudCBkZXB0aCBgICtcbiAgICAgICAgICAgIGBpcyAwIGFuZCB0aGUgYWN0aXZhdGlvbiBpcyBub3QgbGluZWFyLmApO1xuXG4gICAgbGV0IHJlc3VsdCA9IHVuZnVzZWRDb252MmQoXG4gICAgICAgIHgsIGZpbHRlciwgc3RyaWRlcywgcGFkLCBkYXRhRm9ybWF0LCBkaWxhdGlvbnMsIGRpbVJvdW5kaW5nTW9kZSk7XG4gICAgaWYgKGJpYXMgIT0gbnVsbCkge1xuICAgICAgcmVzdWx0ID0gYWRkKHJlc3VsdCwgYmlhcyk7XG4gICAgfVxuXG4gICAgcmV0dXJuIGFwcGx5QWN0aXZhdGlvbihcbiAgICAgICAgICAgICAgIHJlc3VsdCwgYWN0aXZhdGlvbiwgcHJlbHVBY3RpdmF0aW9uV2VpZ2h0cywgbGVha3lyZWx1QWxwaGEpIGFzIFQ7XG4gIH1cblxuICBjb25zdCAkeCA9IGNvbnZlcnRUb1RlbnNvcih4LCAneCcsICdjb252MmQnLCAnZmxvYXQzMicpO1xuICBjb25zdCAkZmlsdGVyID0gY29udmVydFRvVGVuc29yKGZpbHRlciwgJ2ZpbHRlcicsICdjb252MmQnLCAnZmxvYXQzMicpO1xuXG4gIGxldCB4NEQgPSAkeCBhcyBUZW5zb3I0RDtcbiAgbGV0IHJlc2hhcGVkVG80RCA9IGZhbHNlO1xuXG4gIGlmICgkeC5yYW5rID09PSAzKSB7XG4gICAgcmVzaGFwZWRUbzREID0gdHJ1ZTtcbiAgICB4NEQgPSByZXNoYXBlKCR4LCBbMSwgJHguc2hhcGVbMF0sICR4LnNoYXBlWzFdLCAkeC5zaGFwZVsyXV0pO1xuICB9XG4gIHV0aWwuYXNzZXJ0KFxuICAgICAgeDRELnJhbmsgPT09IDQsXG4gICAgICAoKSA9PiBgRXJyb3IgaW4gZnVzZWQgY29udjJkOiBpbnB1dCBtdXN0IGJlIHJhbmsgNCwgYnV0IGdvdCByYW5rIGAgK1xuICAgICAgICAgIGAke3g0RC5yYW5rfS5gKTtcbiAgdXRpbC5hc3NlcnQoXG4gICAgICAkZmlsdGVyLnJhbmsgPT09IDQsXG4gICAgICAoKSA9PiBgRXJyb3IgaW4gZnVzZWQgY29udjJkOiBmaWx0ZXIgbXVzdCBiZSByYW5rIDQsIGJ1dCBnb3QgcmFuayBgICtcbiAgICAgICAgICBgJHskZmlsdGVyLnJhbmt9LmApO1xuICBjb252X3V0aWwuY2hlY2tQYWRPbkRpbVJvdW5kaW5nTW9kZSgnZnVzZWQgY29udjJkJywgcGFkLCBkaW1Sb3VuZGluZ01vZGUpO1xuICBjb25zdCBpbnB1dENoYW5uZWxzID0gZGF0YUZvcm1hdCA9PT0gJ05IV0MnID8geDRELnNoYXBlWzNdIDogeDRELnNoYXBlWzFdO1xuICB1dGlsLmFzc2VydChcbiAgICAgICRmaWx0ZXIuc2hhcGVbMl0gPT09IGlucHV0Q2hhbm5lbHMsXG4gICAgICAoKSA9PiBgRXJyb3IgaW4gY29udjJkOiBkZXB0aCBvZiBpbnB1dCAoJHtpbnB1dENoYW5uZWxzfSkgbXVzdCBtYXRjaCBgICtcbiAgICAgICAgICBgaW5wdXQgZGVwdGggZm9yIGZpbHRlciAkeyRmaWx0ZXIuc2hhcGVbMl19LmApO1xuICB1dGlsLmFzc2VydChcbiAgICAgIGNvbnZfdXRpbC5laXRoZXJTdHJpZGVzT3JEaWxhdGlvbnNBcmVPbmUoc3RyaWRlcywgZGlsYXRpb25zKSxcbiAgICAgICgpID0+ICdFcnJvciBpbiBjb252MkQ6IEVpdGhlciBzdHJpZGVzIG9yIGRpbGF0aW9ucyBtdXN0IGJlIDEuICcgK1xuICAgICAgICAgIGBHb3Qgc3RyaWRlcyAke3N0cmlkZXN9IGFuZCBkaWxhdGlvbnMgJyR7ZGlsYXRpb25zfSdgKTtcblxuICBjb25zdCBjb252SW5mbyA9IGNvbnZfdXRpbC5jb21wdXRlQ29udjJESW5mbyhcbiAgICAgIHg0RC5zaGFwZSwgJGZpbHRlci5zaGFwZSwgc3RyaWRlcywgZGlsYXRpb25zLCBwYWQsIGRpbVJvdW5kaW5nTW9kZSk7XG5cbiAgbGV0ICRiaWFzOiBUZW5zb3I7XG4gIGlmIChiaWFzICE9IG51bGwpIHtcbiAgICAkYmlhcyA9IGNvbnZlcnRUb1RlbnNvcihiaWFzLCAnYmlhcycsICdmdXNlZCBjb252MmQnKTtcbiAgICBbJGJpYXNdID0gbWFrZVR5cGVzTWF0Y2goJGJpYXMsICR4KTtcblxuICAgIC8vIEFjY29yZGluZyB0byBUZW5zb3JGbG93LCB0aGUgYmlhcyBpcyBzdXBwb3NlZCBiZSBhIDEtRCB0ZW5zb3Igb3IgYVxuICAgIC8vIHNjYWxhci5cbiAgICBpZiAoZGF0YUZvcm1hdCA9PT0gJ05IV0MnKSB7XG4gICAgICBicm9hZGNhc3RfdXRpbC5hc3NlcnRBbmRHZXRCcm9hZGNhc3RTaGFwZShjb252SW5mby5vdXRTaGFwZSwgJGJpYXMuc2hhcGUpO1xuICAgIH0gZWxzZSB7XG4gICAgICB1dGlsLmFzc2VydChcbiAgICAgICAgICAkYmlhcy5zaGFwZS5sZW5ndGggPD0gMSxcbiAgICAgICAgICAoKSA9PiBgRXJyb3IgaW4gZnVzZWQgY29udjJkOiBvbmx5IHN1cHBvcnRzIHNjYWxhciBvciAxLUQgVGVuc29yIGAgK1xuICAgICAgICAgICAgICBgYmlhcyBmb3IgTkNIVyBmb3JtYXQgYnV0IGdvdCB0aGUgYmlhcyBvZiBgICtcbiAgICAgICAgICAgICAgYHJhbmstJHskYmlhcy5zaGFwZS5sZW5ndGh9LmApO1xuXG4gICAgICB1dGlsLmFzc2VydChcbiAgICAgICAgICAkYmlhcy5zaGFwZS5sZW5ndGggPT09IDAgfHwgJGJpYXMuc2hhcGVbMF0gPT09IGNvbnZJbmZvLm91dENoYW5uZWxzIHx8XG4gICAgICAgICAgICAgICRiaWFzLnNoYXBlWzBdID09PSAxLFxuICAgICAgICAgICgpID0+IGBFcnJvciBpbiBmdXNlZCBjb252MmQ6IGJpYXMgc2hhcGUgKCR7JGJpYXMuc2hhcGV9KSBpcyBub3QgYCArXG4gICAgICAgICAgICAgIGBjb21wYXRpYmxlIHdpdGggdGhlIG51bWJlciBvZiBvdXRwdXQgY2hhbm5lbHMgYCArXG4gICAgICAgICAgICAgIGAoJHtjb252SW5mby5vdXRDaGFubmVsc30pYCk7XG4gICAgfVxuICB9XG5cbiAgbGV0ICRwcmVsdUFjdGl2YXRpb25XZWlnaHRzOiBUZW5zb3I7XG4gIGlmIChwcmVsdUFjdGl2YXRpb25XZWlnaHRzICE9IG51bGwpIHtcbiAgICAvLyBQUmVMVSdzIGFjdGl2YXRpb24gd2VpZ2h0cyBjb3VsZCBiZSBhIHNjYWxhciwgYSAxLUQgdGVuc29yIG9yIGEgMy1EXG4gICAgLy8gdGVuc29yLlxuICAgIGNvbnN0IGFscGhhU2hhcGUgPSBwcmVsdUFjdGl2YXRpb25XZWlnaHRzLnNoYXBlO1xuICAgIHV0aWwuYXNzZXJ0KFxuICAgICAgICBhbHBoYVNoYXBlLmxlbmd0aCA8PSAxIHx8IGFscGhhU2hhcGUubGVuZ3RoID09PSAzLFxuICAgICAgICAoKSA9PiBgRXJyb3IgaW4gZnVzZWQgY29udjJkOiBvbmx5IHN1cHBvcnRzIHNjYWxhciwgMS1EIFRlbnNvciBvciBgICtcbiAgICAgICAgICAgIGAzLUQgVGVuc29yIFBSZUxVIGFjdGl2YXRpb24gd2VpZ2h0cyBidXQgZ290IGEgdGVuc29yIG9mIGAgK1xuICAgICAgICAgICAgYHJhbmstJHthbHBoYVNoYXBlLmxlbmd0aH0uYCk7XG5cbiAgICBpZiAoYWxwaGFTaGFwZS5sZW5ndGggPT09IDEpIHtcbiAgICAgIC8vIFdoZXRoZXIgdGhlIGRhdGEgZm9ybWF0IGlzIE5DSFcgb3IgTkhXQywgdGhlIDEtRCBQUmVMVSBhY3RpdmF0aW9uXG4gICAgICAvLyB3ZWlnaHRzIHRlbnNvciBzaG91bGQgYmUgYWxpZ25lZCB3aXRoIHRoZSBvdXRwdXQgY2hhbm5lbHMgb2YgY29udjJkXG4gICAgICAvLyByZXN1bHQuXG4gICAgICB1dGlsLmFzc2VydChcbiAgICAgICAgICBhbHBoYVNoYXBlWzBdID09PSAxIHx8IGFscGhhU2hhcGVbMF0gPT09IGNvbnZJbmZvLm91dENoYW5uZWxzLFxuICAgICAgICAgICgpID0+IGBFcnJvciBpbiBmdXNlZCBjb252MmQ6IFBSZUxVIGFjdGl2YXRpb24gd2VpZ2h0cyBgICtcbiAgICAgICAgICAgICAgYCgke2FscGhhU2hhcGV9KSBpcyBub3QgY29tcGF0aWJsZSB3aXRoIHRoZSBudW1iZXIgb2Ygb3V0cHV0IGAgK1xuICAgICAgICAgICAgICBgY2hhbm5lbHMgKCR7Y29udkluZm8ub3V0Q2hhbm5lbHN9KS5gKTtcbiAgICB9IGVsc2UgaWYgKGFscGhhU2hhcGUubGVuZ3RoID09PSAzKSB7XG4gICAgICAvLyBXaGV0aGVyIHRoZSBkYXRhIGZvcm1hdCBpcyBOQ0hXIG9yIE5IV0MsIHRoZSBQUmVMVSBhY3RpdmF0aW9uIHdlaWdodHNcbiAgICAgIC8vIHRlbnNvciBzaG91bGQgaGFzIHRoZSBjb21wYXRpYmxlIHNoYXBlIHdpdGggdGhlIHJlc3VsdCBvZiBjb252MmQuXG4gICAgICB0cnkge1xuICAgICAgICBicm9hZGNhc3RfdXRpbC5hc3NlcnRBbmRHZXRCcm9hZGNhc3RTaGFwZShcbiAgICAgICAgICAgIGFscGhhU2hhcGUsIGNvbnZJbmZvLm91dFNoYXBlKTtcbiAgICAgIH0gY2F0Y2ggKGUpIHtcbiAgICAgICAgY29uc3QgZXJyTXNnID1cbiAgICAgICAgICAgIGBFcnJvciBpbiBmdXNlZCBjb252MmQ6IFBSZUxVIGFjdGl2YXRpb24gd2VpZ2h0cyAoJHthbHBoYVNoYXBlfSkgYCArXG4gICAgICAgICAgICBgaXMgbm90IGNvbXBhdGlibGUgd2l0aCB0aGUgb3V0cHV0IHNoYXBlIG9mIHRoZSBjb252MmQgYCArXG4gICAgICAgICAgICBgKCR7Y29udkluZm8ub3V0U2hhcGV9KS5gO1xuICAgICAgICB0aHJvdyBFcnJvcihlcnJNc2cpO1xuICAgICAgfVxuICAgIH1cblxuICAgICRwcmVsdUFjdGl2YXRpb25XZWlnaHRzID0gY29udmVydFRvVGVuc29yKFxuICAgICAgICBwcmVsdUFjdGl2YXRpb25XZWlnaHRzLCAncHJlbHUgd2VpZ2h0cycsICdmdXNlZCBjb252MmQnKTtcbiAgfVxuXG4gIGNvbnN0IGdyYWQgPSAoZHk6IFRlbnNvcjRELCBzYXZlZDogVGVuc29yW10pID0+IHtcbiAgICB1dGlsLmFzc2VydChcbiAgICAgICAgZGF0YUZvcm1hdCA9PT0gJ05IV0MnLFxuICAgICAgICAoKSA9PiBgRXJyb3IgaW4gZ3JhZGllbnQgb2YgZnVzZWQgY29udjJEOiBnb3QgZGF0YUZvcm1hdCBvZiAke1xuICAgICAgICAgICAgZGF0YUZvcm1hdH0gYnV0IG9ubHkgTkhXQyBpcyBjdXJyZW50bHkgc3VwcG9ydGVkLmApO1xuXG4gICAgY29uc3QgWyRmaWx0ZXIsIHg0RCwgeSwgJGJpYXNdID1cbiAgICAgICAgc2F2ZWQgYXMgW1RlbnNvcjRELCBUZW5zb3I0RCwgVGVuc29yNEQsIFRlbnNvcl07XG5cbiAgICBjb25zdCBkeUFjdGl2YXRpb24gPSBnZXRGdXNlZER5QWN0aXZhdGlvbihkeSwgeSwgYWN0aXZhdGlvbikgYXMgVGVuc29yNEQ7XG5cbiAgICB1dGlsLmFzc2VydChcbiAgICAgICAgY29udl91dGlsLnR1cGxlVmFsdWVzQXJlT25lKGRpbGF0aW9ucyksXG4gICAgICAgICgpID0+ICdFcnJvciBpbiBncmFkaWVudCBvZiBmdXNlZCBjb252MkQ6ICcgK1xuICAgICAgICAgICAgYGRpbGF0aW9uIHJhdGVzIGdyZWF0ZXIgdGhhbiAxIGAgK1xuICAgICAgICAgICAgYGFyZSBub3QgeWV0IHN1cHBvcnRlZCBpbiBncmFkaWVudHMuIEdvdCBkaWxhdGlvbnMgJyR7ZGlsYXRpb25zfSdgKTtcblxuICAgIGNvbnN0IHhEZXIgPVxuICAgICAgICBjb252MkRCYWNrcHJvcElucHV0KHg0RC5zaGFwZSwgZHlBY3RpdmF0aW9uLCAkZmlsdGVyLCBzdHJpZGVzLCBwYWQpO1xuICAgIGNvbnN0IGZpbHRlckRlciA9XG4gICAgICAgIGNvbnYyREJhY2twcm9wRmlsdGVyKHg0RCwgZHlBY3RpdmF0aW9uLCAkZmlsdGVyLnNoYXBlLCBzdHJpZGVzLCBwYWQpO1xuICAgIGNvbnN0IGRlcjogVGVuc29yW10gPSBbeERlciwgZmlsdGVyRGVyXTtcblxuICAgIGlmICgkYmlhcyAhPSBudWxsKSB7XG4gICAgICBjb25zdCBiaWFzRGVyID0gZ2V0RnVzZWRCaWFzR3JhZGllbnQoJGJpYXMsIGR5QWN0aXZhdGlvbik7XG4gICAgICBkZXIucHVzaChiaWFzRGVyKTtcbiAgICB9XG4gICAgcmV0dXJuIGRlcjtcbiAgfTtcblxuICBjb25zdCBpbnB1dHM6IEZ1c2VkQ29udjJESW5wdXRzID0ge1xuICAgIHg6IHg0RCxcbiAgICBmaWx0ZXI6ICRmaWx0ZXIsXG4gICAgYmlhczogJGJpYXMsXG4gICAgcHJlbHVBY3RpdmF0aW9uV2VpZ2h0czogJHByZWx1QWN0aXZhdGlvbldlaWdodHNcbiAgfTtcblxuICBjb25zdCBhdHRyczogRnVzZWRDb252MkRBdHRycyA9IHtcbiAgICBzdHJpZGVzLFxuICAgIHBhZCxcbiAgICBkYXRhRm9ybWF0LFxuICAgIGRpbGF0aW9ucyxcbiAgICBkaW1Sb3VuZGluZ01vZGUsXG4gICAgYWN0aXZhdGlvbixcbiAgICBsZWFreXJlbHVBbHBoYVxuICB9O1xuXG4gIC8vIERlcGVuZGluZyBvbiB0aGUgdGhlIHBhcmFtcyBwYXNzZWQgaW4gd2Ugd2lsbCBoYXZlIGRpZmZlcmVudCBudW1iZXIgb2ZcbiAgLy8gaW5wdXRzIGFuZCB0aHVzIGEgYSBkaWZmZXJlbnQgbnVtYmVyIG9mIGVsZW1lbnRzIGluIHRoZSBncmFkaWVudC5cbiAgaWYgKGJpYXMgPT0gbnVsbCkge1xuICAgIGNvbnN0IGN1c3RvbU9wID1cbiAgICAgICAgY3VzdG9tR3JhZCgoeDREOiBUZW5zb3I0RCwgZmlsdGVyOiBUZW5zb3I0RCwgc2F2ZTogR3JhZFNhdmVGdW5jKSA9PiB7XG4gICAgICAgICAgbGV0IHJlczogVGVuc29yNER8VGVuc29yM0QgPVxuICAgICAgICAgICAgICAvLyB0c2xpbnQ6ZGlzYWJsZS1uZXh0LWxpbmU6IG5vLXVubmVjZXNzYXJ5LXR5cGUtYXNzZXJ0aW9uXG4gICAgICAgICAgICAgIEVOR0lORS5ydW5LZXJuZWwoXG4gICAgICAgICAgICAgICAgICBGdXNlZENvbnYyRCwgaW5wdXRzIGFzIHt9IGFzIE5hbWVkVGVuc29yTWFwLFxuICAgICAgICAgICAgICAgICAgYXR0cnMgYXMge30gYXMgTmFtZWRBdHRyTWFwKTtcblxuICAgICAgICAgIHNhdmUoW2ZpbHRlciwgeDRELCByZXNdKTtcblxuICAgICAgICAgIGlmIChyZXNoYXBlZFRvNEQpIHtcbiAgICAgICAgICAgIC8vIHRzbGludDpkaXNhYmxlLW5leHQtbGluZTogbm8tdW5uZWNlc3NhcnktdHlwZS1hc3NlcnRpb25cbiAgICAgICAgICAgIHJlcyA9IHJlc2hhcGUocmVzLCBbcmVzLnNoYXBlWzFdLCByZXMuc2hhcGVbMl0sIHJlcy5zaGFwZVszXV0pIGFzXG4gICAgICAgICAgICAgICAgVGVuc29yM0Q7XG4gICAgICAgICAgfVxuXG4gICAgICAgICAgcmV0dXJuIHt2YWx1ZTogcmVzLCBncmFkRnVuYzogZ3JhZH07XG4gICAgICAgIH0pO1xuICAgIHJldHVybiBjdXN0b21PcCh4NEQsICRmaWx0ZXIpIGFzIFQ7XG4gIH0gZWxzZSB7XG4gICAgY29uc3QgY3VzdG9tT3BXaXRoQmlhcyA9IGN1c3RvbUdyYWQoXG4gICAgICAgICh4NEQ6IFRlbnNvcjRELCBmaWx0ZXI6IFRlbnNvcjRELCBiaWFzOiBUZW5zb3IsIHNhdmU6IEdyYWRTYXZlRnVuYykgPT4ge1xuICAgICAgICAgIGxldCByZXM6IFRlbnNvcjREfFRlbnNvcjNEID0gRU5HSU5FLnJ1bktlcm5lbChcbiAgICAgICAgICAgICAgRnVzZWRDb252MkQsIGlucHV0cyBhcyB7fSBhcyBOYW1lZFRlbnNvck1hcCxcbiAgICAgICAgICAgICAgYXR0cnMgYXMge30gYXMgTmFtZWRBdHRyTWFwKTtcblxuICAgICAgICAgIHNhdmUoW2ZpbHRlciwgeDRELCByZXMsIGJpYXNdKTtcblxuICAgICAgICAgIGlmIChyZXNoYXBlZFRvNEQpIHtcbiAgICAgICAgICAgIC8vIHRzbGludDpkaXNhYmxlLW5leHQtbGluZTogbm8tdW5uZWNlc3NhcnktdHlwZS1hc3NlcnRpb25cbiAgICAgICAgICAgIHJlcyA9IHJlc2hhcGUocmVzLCBbcmVzLnNoYXBlWzFdLCByZXMuc2hhcGVbMl0sIHJlcy5zaGFwZVszXV0pIGFzXG4gICAgICAgICAgICAgICAgVGVuc29yM0Q7XG4gICAgICAgICAgfVxuXG4gICAgICAgICAgcmV0dXJuIHt2YWx1ZTogcmVzLCBncmFkRnVuYzogZ3JhZH07XG4gICAgICAgIH0pO1xuXG4gICAgcmV0dXJuIGN1c3RvbU9wV2l0aEJpYXMoeDRELCAkZmlsdGVyLCAkYmlhcykgYXMgVDtcbiAgfVxufVxuZXhwb3J0IGNvbnN0IGNvbnYyZCA9IG9wKHtmdXNlZENvbnYyZF99KTtcbiJdfQ==