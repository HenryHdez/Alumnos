/**
 * @license
 * Copyright 2017 Google LLC. All Rights Reserved.
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
// Workaround for: https://github.com/bazelbuild/rules_nodejs/issues/1265
/// <reference types="@webgpu/types/dist" />
import { getGlobal } from './global_util';
import { tensorToString } from './tensor_format';
import * as util from './util';
import { computeStrides, toNestedArray } from './util';
/**
 * A mutable object, similar to `tf.Tensor`, that allows users to set values
 * at locations before converting to an immutable `tf.Tensor`.
 *
 * See `tf.buffer` for creating a tensor buffer.
 *
 * @doc {heading: 'Tensors', subheading: 'Classes'}
 */
export class TensorBuffer {
    constructor(shape, dtype, values) {
        this.dtype = dtype;
        this.shape = shape.slice();
        this.size = util.sizeFromShape(shape);
        if (values != null) {
            const n = values.length;
            util.assert(n === this.size, () => `Length of values '${n}' does not match the size ` +
                `inferred by the shape '${this.size}'.`);
        }
        if (dtype === 'complex64') {
            throw new Error(`complex64 dtype TensorBuffers are not supported. Please create ` +
                `a TensorBuffer for the real and imaginary parts separately and ` +
                `call tf.complex(real, imag).`);
        }
        this.values = values || util.getArrayFromDType(dtype, this.size);
        this.strides = computeStrides(shape);
    }
    /**
     * Sets a value in the buffer at a given location.
     *
     * @param value The value to set.
     * @param locs  The location indices.
     *
     * @doc {heading: 'Tensors', subheading: 'Creation'}
     */
    set(value, ...locs) {
        if (locs.length === 0) {
            locs = [0];
        }
        util.assert(locs.length === this.rank, () => `The number of provided coordinates (${locs.length}) must ` +
            `match the rank (${this.rank})`);
        const index = this.locToIndex(locs);
        this.values[index] = value;
    }
    /**
     * Returns the value in the buffer at the provided location.
     *
     * @param locs The location indices.
     *
     * @doc {heading: 'Tensors', subheading: 'Creation'}
     */
    get(...locs) {
        if (locs.length === 0) {
            locs = [0];
        }
        let i = 0;
        for (const loc of locs) {
            if (loc < 0 || loc >= this.shape[i]) {
                const msg = `Requested out of range element at ${locs}. ` +
                    `  Buffer shape=${this.shape}`;
                throw new Error(msg);
            }
            i++;
        }
        let index = locs[locs.length - 1];
        for (let i = 0; i < locs.length - 1; ++i) {
            index += this.strides[i] * locs[i];
        }
        return this.values[index];
    }
    locToIndex(locs) {
        if (this.rank === 0) {
            return 0;
        }
        else if (this.rank === 1) {
            return locs[0];
        }
        let index = locs[locs.length - 1];
        for (let i = 0; i < locs.length - 1; ++i) {
            index += this.strides[i] * locs[i];
        }
        return index;
    }
    indexToLoc(index) {
        if (this.rank === 0) {
            return [];
        }
        else if (this.rank === 1) {
            return [index];
        }
        const locs = new Array(this.shape.length);
        for (let i = 0; i < locs.length - 1; ++i) {
            locs[i] = Math.floor(index / this.strides[i]);
            index -= locs[i] * this.strides[i];
        }
        locs[locs.length - 1] = index;
        return locs;
    }
    get rank() {
        return this.shape.length;
    }
    /**
     * Creates an immutable `tf.Tensor` object from the buffer.
     *
     * @doc {heading: 'Tensors', subheading: 'Creation'}
     */
    toTensor() {
        return trackerFn().makeTensor(this.values, this.shape, this.dtype);
    }
}
// For tracking tensor creation and disposal.
let trackerFn = null;
// Used by chaining methods to call into ops.
let opHandler = null;
// Used to warn about deprecated methods.
let deprecationWarningFn = null;
// This here so that we can use this method on dev branches and keep the
// functionality at master.
// tslint:disable-next-line:no-unused-expression
[deprecationWarningFn];
/**
 * An external consumer can register itself as the tensor tracker. This way
 * the Tensor class can notify the tracker for every tensor created and
 * disposed.
 */
export function setTensorTracker(fn) {
    trackerFn = fn;
}
/**
 * An external consumer can register itself as the op handler. This way the
 * Tensor class can have chaining methods that call into ops via the op
 * handler.
 */
export function setOpHandler(handler) {
    opHandler = handler;
}
/**
 * Sets the deprecation warning function to be used by this file. This way the
 * Tensor class can be a leaf but still use the environment.
 */
export function setDeprecationWarningFn(fn) {
    deprecationWarningFn = fn;
}
/**
 * A `tf.Tensor` object represents an immutable, multidimensional array of
 * numbers that has a shape and a data type.
 *
 * For performance reasons, functions that create tensors do not necessarily
 * perform a copy of the data passed to them (e.g. if the data is passed as a
 * `Float32Array`), and changes to the data will change the tensor. This is not
 * a feature and is not supported. To avoid this behavior, use the tensor before
 * changing the input data or create a copy with `copy = tf.add(yourTensor, 0)`.
 *
 * See `tf.tensor` for details on how to create a `tf.Tensor`.
 *
 * @doc {heading: 'Tensors', subheading: 'Classes'}
 */
export class Tensor {
    constructor(shape, dtype, dataId, id) {
        /** Whether this tensor has been globally kept. */
        this.kept = false;
        this.isDisposedInternal = false;
        this.shape = shape.slice();
        this.dtype = dtype || 'float32';
        this.size = util.sizeFromShape(shape);
        this.strides = computeStrides(shape);
        this.dataId = dataId;
        this.id = id;
        this.rankType = (this.rank < 5 ? this.rank.toString() : 'higher');
    }
    get rank() {
        return this.shape.length;
    }
    /**
     * Returns a promise of `tf.TensorBuffer` that holds the underlying data.
     *
     * @doc {heading: 'Tensors', subheading: 'Classes'}
     */
    async buffer() {
        const vals = await this.data();
        return opHandler.buffer(this.shape, this.dtype, vals);
    }
    /**
     * Returns a `tf.TensorBuffer` that holds the underlying data.
     * @doc {heading: 'Tensors', subheading: 'Classes'}
     */
    bufferSync() {
        return opHandler.buffer(this.shape, this.dtype, this.dataSync());
    }
    /**
     * Returns the tensor data as a nested array. The transfer of data is done
     * asynchronously.
     *
     * @doc {heading: 'Tensors', subheading: 'Classes'}
     */
    async array() {
        const vals = await this.data();
        return toNestedArray(this.shape, vals, this.dtype === 'complex64');
    }
    /**
     * Returns the tensor data as a nested array. The transfer of data is done
     * synchronously.
     *
     * @doc {heading: 'Tensors', subheading: 'Classes'}
     */
    arraySync() {
        return toNestedArray(this.shape, this.dataSync(), this.dtype === 'complex64');
    }
    /**
     * Asynchronously downloads the values from the `tf.Tensor`. Returns a
     * promise of `TypedArray` that resolves when the computation has finished.
     *
     * @doc {heading: 'Tensors', subheading: 'Classes'}
     */
    async data() {
        this.throwIfDisposed();
        const data = trackerFn().read(this.dataId);
        if (this.dtype === 'string') {
            const bytes = await data;
            try {
                return bytes.map(b => util.decodeString(b));
            }
            catch (_a) {
                throw new Error('Failed to decode the string bytes into utf-8. ' +
                    'To get the original bytes, call tensor.bytes().');
            }
        }
        return data;
    }
    /**
     * Copy the tensor's data to a new GPU resource. Comparing to the `dataSync()`
     * and `data()`, this method prevents data from being downloaded to CPU.
     *
     * For WebGL backend, the data will be stored on a densely packed texture.
     * This means that the texture will use the RGBA channels to store value.
     *
     * For WebGPU backend, the data will be stored on a buffer. There is no
     * parameter, so can not use an user defined size to create the buffer.
     *
     * @param options:
     *     For WebGL,
     *         - customTexShape: Optional. If set, will use the user defined
     *     texture shape to create the texture.
     *
     * @returns For WebGL backend, a GPUData contains the new texture and
     *     its information.
     *     {
     *        tensorRef: The tensor that is associated with this texture,
     *        texture: WebGLTexture,
     *        texShape: [number, number] // [height, width]
     *     }
     *
     *     For WebGPU backend, a GPUData contains the new buffer and
     *     its information.
     *     {
     *        tensorRef: The tensor that is associated with this buffer,
     *        buffer: GPUBuffer,
     *        bufSize: number
     *     }
     *
     *     Remember to dispose the GPUData after it is used by
     *     `res.tensorRef.dispose()`.
     *
     * @doc {heading: 'Tensors', subheading: 'Classes'}
     */
    dataToGPU(options) {
        this.throwIfDisposed();
        return trackerFn().readToGPU(this.dataId, options);
    }
    /**
     * Synchronously downloads the values from the `tf.Tensor`. This blocks the
     * UI thread until the values are ready, which can cause performance issues.
     *
     * @doc {heading: 'Tensors', subheading: 'Classes'}
     */
    dataSync() {
        this.throwIfDisposed();
        const data = trackerFn().readSync(this.dataId);
        if (this.dtype === 'string') {
            try {
                return data.map(b => util.decodeString(b));
            }
            catch (_a) {
                throw new Error('Failed to decode the string bytes into utf-8. ' +
                    'To get the original bytes, call tensor.bytes().');
            }
        }
        return data;
    }
    /** Returns the underlying bytes of the tensor's data. */
    async bytes() {
        this.throwIfDisposed();
        const data = await trackerFn().read(this.dataId);
        if (this.dtype === 'string') {
            return data;
        }
        else {
            return new Uint8Array(data.buffer);
        }
    }
    /**
     * Disposes `tf.Tensor` from memory.
     *
     * @doc {heading: 'Tensors', subheading: 'Classes'}
     */
    dispose() {
        if (this.isDisposed) {
            return;
        }
        trackerFn().disposeTensor(this);
        this.isDisposedInternal = true;
    }
    get isDisposed() {
        return this.isDisposedInternal;
    }
    throwIfDisposed() {
        if (this.isDisposed) {
            throw new Error(`Tensor is disposed.`);
        }
    }
    /**
     * Prints the `tf.Tensor`. See `tf.print` for details.
     *
     * @param verbose Whether to print verbose information about the tensor,
     *    including dtype and size.
     *
     * @doc {heading: 'Tensors', subheading: 'Classes'}
     */
    print(verbose = false) {
        return opHandler.print(this, verbose);
    }
    /**
     * Returns a copy of the tensor. See `tf.clone` for details.
     * @doc {heading: 'Tensors', subheading: 'Classes'}
     */
    clone() {
        this.throwIfDisposed();
        return opHandler.clone(this);
    }
    /**
     * Returns a human-readable description of the tensor. Useful for logging.
     *
     * @doc {heading: 'Tensors', subheading: 'Classes'}
     */
    toString(verbose = false) {
        const vals = this.dataSync();
        return tensorToString(vals, this.shape, this.dtype, verbose);
    }
    cast(dtype) {
        this.throwIfDisposed();
        return opHandler.cast(this, dtype);
    }
    variable(trainable = true, name, dtype) {
        this.throwIfDisposed();
        return trackerFn().makeVariable(this, trainable, name, dtype);
    }
}
Object.defineProperty(Tensor, Symbol.hasInstance, {
    value: (instance) => {
        // Implementation note: we should use properties of the object that will be
        // defined before the constructor body has finished executing (methods).
        // This is because when this code is transpiled by babel, babel will call
        // classCallCheck before the constructor body is run.
        // See https://github.com/tensorflow/tfjs/issues/3384 for backstory.
        return !!instance && instance.data != null && instance.dataSync != null &&
            instance.throwIfDisposed != null;
    }
});
export function getGlobalTensorClass() {
    // Use getGlobal so that we can augment the Tensor class across package
    // boundaries becase the node resolution alg may result in different modules
    // being returned for this file depending on the path they are loaded from.
    return getGlobal('Tensor', () => {
        return Tensor;
    });
}
// Global side effect. Cache global reference to Tensor class
getGlobalTensorClass();
/**
 * A mutable `tf.Tensor`, useful for persisting state, e.g. for training.
 *
 * @doc {heading: 'Tensors', subheading: 'Classes'}
 */
export class Variable extends Tensor {
    constructor(initialValue, trainable, name, tensorId) {
        super(initialValue.shape, initialValue.dtype, initialValue.dataId, tensorId);
        this.trainable = trainable;
        this.name = name;
    }
    /**
     * Assign a new `tf.Tensor` to this variable. The new `tf.Tensor` must have
     * the same shape and dtype as the old `tf.Tensor`.
     *
     * @param newValue New tensor to be assigned to this variable.
     *
     * @doc {heading: 'Tensors', subheading: 'Classes'}
     */
    assign(newValue) {
        if (newValue.dtype !== this.dtype) {
            throw new Error(`dtype of the new value (${newValue.dtype}) and ` +
                `previous value (${this.dtype}) must match`);
        }
        if (!util.arraysEqual(newValue.shape, this.shape)) {
            throw new Error(`shape of the new value (${newValue.shape}) and ` +
                `previous value (${this.shape}) must match`);
        }
        trackerFn().disposeTensor(this);
        this.dataId = newValue.dataId;
        trackerFn().incRef(this, null /* backend */);
    }
    dispose() {
        trackerFn().disposeVariable(this);
        this.isDisposedInternal = true;
    }
}
Object.defineProperty(Variable, Symbol.hasInstance, {
    value: (instance) => {
        return instance instanceof Tensor && instance.assign != null &&
            instance.assign instanceof Function;
    }
});
//# sourceMappingURL=data:application/json;base64,eyJ2ZXJzaW9uIjozLCJmaWxlIjoidGVuc29yLmpzIiwic291cmNlUm9vdCI6IiIsInNvdXJjZXMiOlsiLi4vLi4vLi4vLi4vLi4vdGZqcy1jb3JlL3NyYy90ZW5zb3IudHMiXSwibmFtZXMiOltdLCJtYXBwaW5ncyI6IkFBQUE7Ozs7Ozs7Ozs7Ozs7OztHQWVHO0FBRUgseUVBQXlFO0FBQ3pFLDRDQUE0QztBQUU1QyxPQUFPLEVBQUMsU0FBUyxFQUFDLE1BQU0sZUFBZSxDQUFDO0FBQ3hDLE9BQU8sRUFBQyxjQUFjLEVBQUMsTUFBTSxpQkFBaUIsQ0FBQztBQUUvQyxPQUFPLEtBQUssSUFBSSxNQUFNLFFBQVEsQ0FBQztBQUMvQixPQUFPLEVBQUMsY0FBYyxFQUFFLGFBQWEsRUFBQyxNQUFNLFFBQVEsQ0FBQztBQVdyRDs7Ozs7OztHQU9HO0FBQ0gsTUFBTSxPQUFPLFlBQVk7SUFNdkIsWUFBWSxLQUFrQixFQUFTLEtBQVEsRUFBRSxNQUF1QjtRQUFqQyxVQUFLLEdBQUwsS0FBSyxDQUFHO1FBQzdDLElBQUksQ0FBQyxLQUFLLEdBQUcsS0FBSyxDQUFDLEtBQUssRUFBaUIsQ0FBQztRQUMxQyxJQUFJLENBQUMsSUFBSSxHQUFHLElBQUksQ0FBQyxhQUFhLENBQUMsS0FBSyxDQUFDLENBQUM7UUFFdEMsSUFBSSxNQUFNLElBQUksSUFBSSxFQUFFO1lBQ2xCLE1BQU0sQ0FBQyxHQUFHLE1BQU0sQ0FBQyxNQUFNLENBQUM7WUFDeEIsSUFBSSxDQUFDLE1BQU0sQ0FDUCxDQUFDLEtBQUssSUFBSSxDQUFDLElBQUksRUFDZixHQUFHLEVBQUUsQ0FBQyxxQkFBcUIsQ0FBQyw0QkFBNEI7Z0JBQ3BELDBCQUEwQixJQUFJLENBQUMsSUFBSSxJQUFJLENBQUMsQ0FBQztTQUNsRDtRQUNELElBQUksS0FBSyxLQUFLLFdBQVcsRUFBRTtZQUN6QixNQUFNLElBQUksS0FBSyxDQUNYLGlFQUFpRTtnQkFDakUsaUVBQWlFO2dCQUNqRSw4QkFBOEIsQ0FBQyxDQUFDO1NBQ3JDO1FBQ0QsSUFBSSxDQUFDLE1BQU0sR0FB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QVEsQ0FBQztJQUMxQyxDQUFDO0NBQ0YsQ0FBQyxDQUFDIiwic291cmNlc0NvbnRlbnQiOlsiLyoqXG4gKiBAbGljZW5zZVxuICogQ29weXJpZ2h0IDIwMTcgR29vZ2xlIExMQy4gQWxsIFJpZ2h0cyBSZXNlcnZlZC5cbiAqIExpY2Vuc2VkIHVuZGVyIHRoZSBBcGFjaGUgTGljZW5zZSwgVmVyc2lvbiAyLjAgKHRoZSBcIkxpY2Vuc2VcIik7XG4gKiB5b3UgbWF5IG5vdCB1c2UgdGhpcyBmaWxlIGV4Y2VwdCBpbiBjb21wbGlhbmNlIHdpdGggdGhlIExpY2Vuc2UuXG4gKiBZb3UgbWF5IG9idGFpbiBhIGNvcHkgb2YgdGhlIExpY2Vuc2UgYXRcbiAqXG4gKiBodHRwOi8vd3d3LmFwYWNoZS5vcmcvbGljZW5zZXMvTElDRU5TRS0yLjBcbiAqXG4gKiBVbmxlc3MgcmVxdWlyZWQgYnkgYXBwbGljYWJsZSBsYXcgb3IgYWdyZWVkIHRvIGluIHdyaXRpbmcsIHNvZnR3YXJlXG4gKiBkaXN0cmlidXRlZCB1bmRlciB0aGUgTGljZW5zZSBpcyBkaXN0cmlidXRlZCBvbiBhbiBcIkFTIElTXCIgQkFTSVMsXG4gKiBXSVRIT1VUIFdBUlJBTlRJRVMgT1IgQ09ORElUSU9OUyBPRiBBTlkgS0lORCwgZWl0aGVyIGV4cHJlc3Mgb3IgaW1wbGllZC5cbiAqIFNlZSB0aGUgTGljZW5zZSBmb3IgdGhlIHNwZWNpZmljIGxhbmd1YWdlIGdvdmVybmluZyBwZXJtaXNzaW9ucyBhbmRcbiAqIGxpbWl0YXRpb25zIHVuZGVyIHRoZSBMaWNlbnNlLlxuICogPT09PT09PT09PT09PT09PT09PT09PT09PT09PT09PT09PT09PT09PT09PT09PT09PT09PT09PT09PT09PT09PT09PT09PT09PT09PT1cbiAqL1xuXG4vLyBXb3JrYXJvdW5kIGZvcjogaHR0cHM6Ly9naXRodWIuY29tL2JhemVsYnVpbGQvcnVsZXNfbm9kZWpzL2lzc3Vlcy8xMjY1XG4vLy8gPHJlZmVyZW5jZSB0eXBlcz1cIkB3ZWJncHUvdHlwZXMvZGlzdFwiIC8+XG5cbmltcG9ydCB7Z2V0R2xvYmFsfSBmcm9tICcuL2dsb2JhbF91dGlsJztcbmltcG9ydCB7dGVuc29yVG9TdHJpbmd9IGZyb20gJy4vdGVuc29yX2Zvcm1hdCc7XG5pbXBvcnQge0FycmF5TWFwLCBCYWNrZW5kVmFsdWVzLCBEYXRhVHlwZSwgRGF0YVR5cGVNYXAsIERhdGFWYWx1ZXMsIE51bWVyaWNEYXRhVHlwZSwgUmFuaywgU2hhcGVNYXAsIFNpbmdsZVZhbHVlTWFwLCBUeXBlZEFycmF5fSBmcm9tICcuL3R5cGVzJztcbmltcG9ydCAqIGFzIHV0aWwgZnJvbSAnLi91dGlsJztcbmltcG9ydCB7Y29tcHV0ZVN0cmlkZXMsIHRvTmVzdGVkQXJyYXl9IGZyb20gJy4vdXRpbCc7XG5cbmV4cG9ydCBpbnRlcmZhY2UgVGVuc29yRGF0YTxEIGV4dGVuZHMgRGF0YVR5cGU+IHtcbiAgZGF0YUlkPzogRGF0YUlkO1xuICB2YWx1ZXM/OiBEYXRhVHlwZU1hcFtEXTtcbn1cblxuLy8gVGhpcyBpbnRlcmZhY2UgbWltaWNzIEtlcm5lbEJhY2tlbmQgKGluIGJhY2tlbmQudHMpLCB3aGljaCB3b3VsZCBjcmVhdGUgYVxuLy8gY2lyY3VsYXIgZGVwZW5kZW5jeSBpZiBpbXBvcnRlZC5cbmV4cG9ydCBpbnRlcmZhY2UgQmFja2VuZCB7fVxuXG4vKipcbiAqIEEgbXV0YWJsZSBvYmplY3QsIHNpbWlsYXIgdG8gYHRmLlRlbnNvcmAsIHRoYXQgYWxsb3dzIHVzZXJzIHRvIHNldCB2YWx1ZXNcbiAqIGF0IGxvY2F0aW9ucyBiZWZvcmUgY29udmVydGluZyB0byBhbiBpbW11dGFibGUgYHRmLlRlbnNvcmAuXG4gKlxuICogU2VlIGB0Zi5idWZmZXJgIGZvciBjcmVhdGluZyBhIHRlbnNvciBidWZmZXIuXG4gKlxuICogQGRvYyB7aGVhZGluZzogJ1RlbnNvcnMnLCBzdWJoZWFkaW5nOiAnQ2xhc3Nlcyd9XG4gKi9cbmV4cG9ydCBjbGFzcyBUZW5zb3JCdWZmZXI8UiBleHRlbmRzIFJhbmssIEQgZXh0ZW5kcyBEYXRhVHlwZSA9ICdmbG9hdDMyJz4ge1xuICBzaXplOiBudW1iZXI7XG4gIHNoYXBlOiBTaGFwZU1hcFtSXTtcbiAgc3RyaWRlczogbnVtYmVyW107XG4gIHZhbHVlczogRGF0YVR5cGVNYXBbRF07XG5cbiAgY29uc3RydWN0b3Ioc2hhcGU6IFNoYXBlTWFwW1JdLCBwdWJsaWMgZHR5cGU6IEQsIHZhbHVlcz86IERhdGFUeXBlTWFwW0RdKSB7XG4gICAgdGhpcy5zaGFwZSA9IHNoYXBlLnNsaWNlKCkgYXMgU2hhcGVNYXBbUl07XG4gICAgdGhpcy5zaXplID0gdXRpbC5zaXplRnJvbVNoYXBlKHNoYXBlKTtcblxuICAgIGlmICh2YWx1ZXMgIT0gbnVsbCkge1xuICAgICAgY29uc3QgbiA9IHZhbHVlcy5sZW5ndGg7XG4gICAgICB1dGlsLmFzc2VydChcbiAgICAgICAgICBuID09PSB0aGlzLnNpemUsXG4gICAgICAgICAgKCkgPT4gYExlbmd0aCBvZiB2YWx1ZXMgJyR7bn0nIGRvZXMgbm90IG1hdGNoIHRoZSBzaXplIGAgK1xuICAgICAgICAgICAgICBgaW5mZXJyZWQgYnkgdGhlIHNoYXBlICcke3RoaXMuc2l6ZX0nLmApO1xuICAgIH1cbiAgICBpZiAoZHR5cGUgPT09ICdjb21wbGV4NjQnKSB7XG4gICAgICB0aHJvdyBuZXcgRXJyb3IoXG4gICAgICAgICAgYGNvbXBsZXg2NCBkdHlwZSBUZW5zb3JCdWZmZXJzIGFyZSBub3Qgc3VwcG9ydGVkLiBQbGVhc2UgY3JlYXRlIGAgK1xuICAgICAgICAgIGBhIFRlbnNvckJ1ZmZlciBmb3IgdGhlIHJlYWwgYW5kIGltYWdpbmFyeSBwYXJ0cyBzZXBhcmF0ZWx5IGFuZCBgICtcbiAgICAgICAgICBgY2FsbCB0Zi5jb21wbGV4KHJlYWwsIGltYWcpLmApO1xuICAgIH1cbiAgICB0aGlzLnZhbHVlcyA9IHZhbHVlcyB8fCB1dGlsLmdldEFycmF5RnJvbURUeXBlKGR0eXBlLCB0aGlzLnNpemUpO1xuICAgIHRoaXMuc3RyaWRlcyA9IGNvbXB1dGVTdHJpZGVzKHNoYXBlKTtcbiAgfVxuXG4gIC8qKlxuICAgKiBTZXRzIGEgdmFsdWUgaW4gdGhlIGJ1ZmZlciBhdCBhIGdpdmVuIGxvY2F0aW9uLlxuICAgKlxuICAgKiBAcGFyYW0gdmFsdWUgVGhlIHZhbHVlIHRvIHNldC5cbiAgICogQHBhcmFtIGxvY3MgIFRoZSBsb2NhdGlvbiBpbmRpY2VzLlxuICAgKlxuICAgKiBAZG9jIHtoZWFkaW5nOiAnVGVuc29ycycsIHN1YmhlYWRpbmc6ICdDcmVhdGlvbid9XG4gICAqL1xuICBzZXQodmFsdWU6IFNpbmdsZVZhbHVlTWFwW0RdLCAuLi5sb2NzOiBudW1iZXJbXSk6IHZvaWQge1xuICAgIGlmIChsb2NzLmxlbmd0aCA9PT0gMCkge1xuICAgICAgbG9jcyA9IFswXTtcbiAgICB9XG4gICAgdXRpbC5hc3NlcnQoXG4gICAgICAgIGxvY3MubGVuZ3RoID09PSB0aGlzLnJhbmssXG4gICAgICAgICgpID0+IGBUaGUgbnVtYmVyIG9mIHByb3ZpZGVkIGNvb3JkaW5hdGVzICgke2xvY3MubGVuZ3RofSkgbXVzdCBgICtcbiAgICAgICAgICAgIGBtYXRjaCB0aGUgcmFuayAoJHt0aGlzLnJhbmt9KWApO1xuXG4gICAgY29uc3QgaW5kZXggPSB0aGlzLmxvY1RvSW5kZXgobG9jcyk7XG4gICAgdGhpcy52YWx1ZXNbaW5kZXhdID0gdmFsdWUgYXMgbnVtYmVyO1xuICB9XG5cbiAgLyoqXG4gICAqIFJldHVybnMgdGhlIHZhbHVlIGluIHRoZSBidWZmZXIgYXQgdGhlIHByb3ZpZGVkIGxvY2F0aW9uLlxuICAgKlxuICAgKiBAcGFyYW0gbG9jcyBUaGUgbG9jYXRpb24gaW5kaWNlcy5cbiAgICpcbiAgICogQGRvYyB7aGVhZGluZzogJ1RlbnNvcnMnLCBzdWJoZWFkaW5nOiAnQ3JlYXRpb24nfVxuICAgKi9cbiAgZ2V0KC4uLmxvY3M6IG51bWJlcltdKTogU2luZ2xlVmFsdWVNYXBbRF0ge1xuICAgIGlmIChsb2NzLmxlbmd0aCA9PT0gMCkge1xuICAgICAgbG9jcyA9IFswXTtcbiAgICB9XG4gICAgbGV0IGkgPSAwO1xuICAgIGZvciAoY29uc3QgbG9jIG9mIGxvY3MpIHtcbiAgICAgIGlmIChsb2MgPCAwIHx8IGxvYyA+PSB0aGlzLnNoYXBlW2ldKSB7XG4gICAgICAgIGNvbnN0IG1zZyA9IGBSZXF1ZXN0ZWQgb3V0IG9mIHJhbmdlIGVsZW1lbnQgYXQgJHtsb2NzfS4gYCArXG4gICAgICAgICAgICBgICBCdWZmZXIgc2hhcGU9JHt0aGlzLnNoYXBlfWA7XG4gICAgICAgIHRocm93IG5ldyBFcnJvcihtc2cpO1xuICAgICAgfVxuICAgICAgaSsrO1xuICAgIH1cbiAgICBsZXQgaW5kZXggPSBsb2NzW2xvY3MubGVuZ3RoIC0gMV07XG4gICAgZm9yIChsZXQgaSA9IDA7IGkgPCBsb2NzLmxlbmd0aCAtIDE7ICsraSkge1xuICAgICAgaW5kZXggKz0gdGhpcy5zdHJpZGVzW2ldICogbG9jc1tpXTtcbiAgICB9XG4gICAgcmV0dXJuIHRoaXMudmFsdWVzW2luZGV4XSBhcyBTaW5nbGVWYWx1ZU1hcFtEXTtcbiAgfVxuXG4gIGxvY1RvSW5kZXgobG9jczogbnVtYmVyW10pOiBudW1iZXIge1xuICAgIGlmICh0aGlzLnJhbmsgPT09IDApIHtcbiAgICAgIHJldHVybiAwO1xuICAgIH0gZWxzZSBpZiAodGhpcy5yYW5rID09PSAxKSB7XG4gICAgICByZXR1cm4gbG9jc1swXTtcbiAgICB9XG4gICAgbGV0IGluZGV4ID0gbG9jc1tsb2NzLmxlbmd0aCAtIDFdO1xuICAgIGZvciAobGV0IGkgPSAwOyBpIDwgbG9jcy5sZW5ndGggLSAxOyArK2kpIHtcbiAgICAgIGluZGV4ICs9IHRoaXMuc3RyaWRlc1tpXSAqIGxvY3NbaV07XG4gICAgfVxuICAgIHJldHVybiBpbmRleDtcbiAgfVxuXG4gIGluZGV4VG9Mb2MoaW5kZXg6IG51bWJlcik6IG51bWJlcltdIHtcbiAgICBpZiAodGhpcy5yYW5rID09PSAwKSB7XG4gICAgICByZXR1cm4gW107XG4gICAgfSBlbHNlIGlmICh0aGlzLnJhbmsgPT09IDEpIHtcbiAgICAgIHJldHVybiBbaW5kZXhdO1xuICAgIH1cbiAgICBjb25zdCBsb2NzOiBudW1iZXJbXSA9IG5ldyBBcnJheSh0aGlzLnNoYXBlLmxlbmd0aCk7XG4gICAgZm9yIChsZXQgaSA9IDA7IGkgPCBsb2NzLmxlbmd0aCAtIDE7ICsraSkge1xuICAgICAgbG9jc1tpXSA9IE1hdGguZmxvb3IoaW5kZXggLyB0aGlzLnN0cmlkZXNbaV0pO1xuICAgICAgaW5kZXggLT0gbG9jc1tpXSAqIHRoaXMuc3RyaWRlc1tpXTtcbiAgICB9XG4gICAgbG9jc1tsb2NzLmxlbmd0aCAtIDFdID0gaW5kZXg7XG4gICAgcmV0dXJuIGxvY3M7XG4gIH1cblxuICBnZXQgcmFuaygpIHtcbiAgICByZXR1cm4gdGhpcy5zaGFwZS5sZW5ndGg7XG4gIH1cblxuICAvKipcbiAgICogQ3JlYXRlcyBhbiBpbW11dGFibGUgYHRmLlRlbnNvcmAgb2JqZWN0IGZyb20gdGhlIGJ1ZmZlci5cbiAgICpcbiAgICogQGRvYyB7aGVhZGluZzogJ1RlbnNvcnMnLCBzdWJoZWFkaW5nOiAnQ3JlYXRpb24nfVxuICAgKi9cbiAgdG9UZW5zb3IoKTogVGVuc29yPFI+IHtcbiAgICByZXR1cm4gdHJhY2tlckZuKCkubWFrZVRlbnNvcih0aGlzLnZhbHVlcywgdGhpcy5zaGFwZSwgdGhpcy5kdHlwZSkgYXNcbiAgICAgICAgVGVuc29yPFI+O1xuICB9XG59XG5cbmV4cG9ydCBpbnRlcmZhY2UgRGF0YVRvR1BVV2ViR0xPcHRpb24ge1xuICBjdXN0b21UZXhTaGFwZT86IFtudW1iZXIsIG51bWJlcl07XG59XG5cbmV4cG9ydCB0eXBlIERhdGFUb0dQVU9wdGlvbnMgPSBEYXRhVG9HUFVXZWJHTE9wdGlvbjtcblxuZXhwb3J0IGludGVyZmFjZSBHUFVEYXRhIHtcbiAgdGVuc29yUmVmOiBUZW5zb3I7XG4gIHRleHR1cmU/OiBXZWJHTFRleHR1cmU7XG4gIGJ1ZmZlcj86IEdQVUJ1ZmZlcjtcbiAgdGV4U2hhcGU/OiBbbnVtYmVyLCBudW1iZXJdO1xuICBidWZTaXplPzogbnVtYmVyO1xufVxuXG5leHBvcnQgaW50ZXJmYWNlIFRlbnNvclRyYWNrZXIge1xuICBtYWtlVGVuc29yKFxuICAgICAgdmFsdWVzOiBEYXRhVmFsdWVzLCBzaGFwZTogbnVtYmVyW10sIGR0eXBlOiBEYXRhVHlwZSxcbiAgICAgIGJhY2tlbmQ/OiBCYWNrZW5kKTogVGVuc29yO1xuICBtYWtlVmFyaWFibGUoXG4gICAgICBpbml0aWFsVmFsdWU6IFRlbnNvciwgdHJhaW5hYmxlPzogYm9vbGVhbiwgbmFtZT86IHN0cmluZyxcbiAgICAgIGR0eXBlPzogRGF0YVR5cGUpOiBWYXJpYWJsZTtcbiAgaW5jUmVmKGE6IFRlbnNvciwgYmFja2VuZDogQmFja2VuZCk6IHZvaWQ7XG4gIGRpc3Bvc2VUZW5zb3IodDogVGVuc29yKTogdm9pZDtcbiAgZGlzcG9zZVZhcmlhYmxlKHY6IFZhcmlhYmxlKTogdm9pZDtcbiAgcmVhZChkYXRhSWQ6IERhdGFJZCk6IFByb21pc2U8QmFja2VuZFZhbHVlcz47XG4gIHJlYWRTeW5jKGRhdGFJZDogRGF0YUlkKTogQmFja2VuZFZhbHVlcztcbiAgcmVhZFRvR1BVKGRhdGFJZDogRGF0YUlkLCBvcHRpb25zPzogRGF0YVRvR1BVT3B0aW9ucyk6IEdQVURhdGE7XG59XG5cbi8qKlxuICogVGhlIFRlbnNvciBjbGFzcyBjYWxscyBpbnRvIHRoaXMgaGFuZGxlciB0byBkZWxlZ2F0ZSBjaGFpbmluZyBvcGVyYXRpb25zLlxuICovXG5leHBvcnQgaW50ZXJmYWNlIE9wSGFuZGxlciB7XG4gIGNhc3Q8VCBleHRlbmRzIFRlbnNvcj4oeDogVCwgZHR5cGU6IERhdGFUeXBlKTogVDtcbiAgYnVmZmVyPFIgZXh0ZW5kcyBSYW5rLCBEIGV4dGVuZHMgRGF0YVR5cGU+KFxuICAgICAgc2hhcGU6IFNoYXBlTWFwW1JdLCBkdHlwZTogRCxcbiAgICAgIHZhbHVlcz86IERhdGFUeXBlTWFwW0RdKTogVGVuc29yQnVmZmVyPFIsIEQ+O1xuICBwcmludDxUIGV4dGVuZHMgVGVuc29yPih4OiBULCB2ZXJib3NlOiBib29sZWFuKTogdm9pZDtcbiAgY2xvbmU8VCBleHRlbmRzIFRlbnNvcj4oeDogVCk6IFQ7XG4gIC8vIFRPRE8oeWFzc29nYmEpIGJyaW5nIHJlc2hhcGUgYmFjaz9cbn1cblxuLy8gRm9yIHRyYWNraW5nIHRlbnNvciBjcmVhdGlvbiBhbmQgZGlzcG9zYWwuXG5sZXQgdHJhY2tlckZuOiAoKSA9PiBUZW5zb3JUcmFja2VyID0gbnVsbDtcbi8vIFVzZWQgYnkgY2hhaW5pbmcgbWV0aG9kcyB0byBjYWxsIGludG8gb3BzLlxubGV0IG9wSGFuZGxlcjogT3BIYW5kbGVyID0gbnVsbDtcbi8vIFVzZWQgdG8gd2FybiBhYm91dCBkZXByZWNhdGVkIG1ldGhvZHMuXG5sZXQgZGVwcmVjYXRpb25XYXJuaW5nRm46IChtc2c6IHN0cmluZykgPT4gdm9pZCA9IG51bGw7XG4vLyBUaGlzIGhlcmUgc28gdGhhdCB3ZSBjYW4gdXNlIHRoaXMgbWV0aG9kIG9uIGRldiBicmFuY2hlcyBhbmQga2VlcCB0aGVcbi8vIGZ1bmN0aW9uYWxpdHkgYXQgbWFzdGVyLlxuLy8gdHNsaW50OmRpc2FibGUtbmV4dC1saW5lOm5vLXVudXNlZC1leHByZXNzaW9uXG5bZGVwcmVjYXRpb25XYXJuaW5nRm5dO1xuXG4vKipcbiAqIEFuIGV4dGVybmFsIGNvbnN1bWVyIGNhbiByZWdpc3RlciBpdHNlbGYgYXMgdGhlIHRlbnNvciB0cmFja2VyLiBUaGlzIHdheVxuICogdGhlIFRlbnNvciBjbGFzcyBjYW4gbm90aWZ5IHRoZSB0cmFja2VyIGZvciBldmVyeSB0ZW5zb3IgY3JlYXRlZCBhbmRcbiAqIGRpc3Bvc2VkLlxuICovXG5leHBvcnQgZnVuY3Rpb24gc2V0VGVuc29yVHJhY2tlcihmbjogKCkgPT4gVGVuc29yVHJhY2tlcikge1xuICB0cmFja2VyRm4gPSBmbjtcbn1cblxuLyoqXG4gKiBBbiBleHRlcm5hbCBjb25zdW1lciBjYW4gcmVnaXN0ZXIgaXRzZWxmIGFzIHRoZSBvcCBoYW5kbGVyLiBUaGlzIHdheSB0aGVcbiAqIFRlbnNvciBjbGFzcyBjYW4gaGF2ZSBjaGFpbmluZyBtZXRob2RzIHRoYXQgY2FsbCBpbnRvIG9wcyB2aWEgdGhlIG9wXG4gKiBoYW5kbGVyLlxuICovXG5leHBvcnQgZnVuY3Rpb24gc2V0T3BIYW5kbGVyKGhhbmRsZXI6IE9wSGFuZGxlcikge1xuICBvcEhhbmRsZXIgPSBoYW5kbGVyO1xufVxuXG4vKipcbiAqIFNldHMgdGhlIGRlcHJlY2F0aW9uIHdhcm5pbmcgZnVuY3Rpb24gdG8gYmUgdXNlZCBieSB0aGlzIGZpbGUuIFRoaXMgd2F5IHRoZVxuICogVGVuc29yIGNsYXNzIGNhbiBiZSBhIGxlYWYgYnV0IHN0aWxsIHVzZSB0aGUgZW52aXJvbm1lbnQuXG4gKi9cbmV4cG9ydCBmdW5jdGlvbiBzZXREZXByZWNhdGlvbldhcm5pbmdGbihmbjogKG1zZzogc3RyaW5nKSA9PiB2b2lkKSB7XG4gIGRlcHJlY2F0aW9uV2FybmluZ0ZuID0gZm47XG59XG5cbi8qKlxuICogV2Ugd3JhcCBkYXRhIGlkIHNpbmNlIHdlIHVzZSB3ZWFrIG1hcCB0byBhdm9pZCBtZW1vcnkgbGVha3MuXG4gKiBTaW5jZSB3ZSBoYXZlIG91ciBvd24gbWVtb3J5IG1hbmFnZW1lbnQsIHdlIGhhdmUgYSByZWZlcmVuY2UgY291bnRlclxuICogbWFwcGluZyBhIHRlbnNvciB0byBpdHMgZGF0YSwgc28gdGhlcmUgaXMgYWx3YXlzIGEgcG9pbnRlciAoZXZlbiBpZiB0aGF0XG4gKiBkYXRhIGlzIG90aGVyd2lzZSBnYXJiYWdlIGNvbGxlY3RhYmxlKS5cbiAqIFNlZSBodHRwczovL2RldmVsb3Blci5tb3ppbGxhLm9yZy9lbi1VUy9kb2NzL1dlYi9KYXZhU2NyaXB0L1JlZmVyZW5jZS9cbiAqIEdsb2JhbF9PYmplY3RzL1dlYWtNYXBcbiAqL1xuZXhwb3J0IHR5cGUgRGF0YUlkID0gb2JqZWN0OyAgLy8gb2JqZWN0IGluc3RlYWQgb2Yge30gdG8gZm9yY2Ugbm9uLXByaW1pdGl2ZS5cblxuLy8gRGVjbGFyZSB0aGlzIG5hbWVzcGFjZSB0byBtYWtlIFRlbnNvciBjbGFzcyBhdWdtZW50YXRpb24gd29yayBpbiBnb29nbGUzLlxuZXhwb3J0IGRlY2xhcmUgbmFtZXNwYWNlIFRlbnNvciB7fVxuLyoqXG4gKiBBIGB0Zi5UZW5zb3JgIG9iamVjdCByZXByZXNlbnRzIGFuIGltbXV0YWJsZSwgbXVsdGlkaW1lbnNpb25hbCBhcnJheSBvZlxuICogbnVtYmVycyB0aGF0IGhhcyBhIHNoYXBlIGFuZCBhIGRhdGEgdHlwZS5cbiAqXG4gKiBGb3IgcGVyZm9ybWFuY2UgcmVhc29ucywgZnVuY3Rpb25zIHRoYXQgY3JlYXRlIHRlbnNvcnMgZG8gbm90IG5lY2Vzc2FyaWx5XG4gKiBwZXJmb3JtIGEgY29weSBvZiB0aGUgZGF0YSBwYXNzZWQgdG8gdGhlbSAoZS5nLiBpZiB0aGUgZGF0YSBpcyBwYXNzZWQgYXMgYVxuICogYEZsb2F0MzJBcnJheWApLCBhbmQgY2hhbmdlcyB0byB0aGUgZGF0YSB3aWxsIGNoYW5nZSB0aGUgdGVuc29yLiBUaGlzIGlzIG5vdFxuICogYSBmZWF0dXJlIGFuZCBpcyBub3Qgc3VwcG9ydGVkLiBUbyBhdm9pZCB0aGlzIGJlaGF2aW9yLCB1c2UgdGhlIHRlbnNvciBiZWZvcmVcbiAqIGNoYW5naW5nIHRoZSBpbnB1dCBkYXRhIG9yIGNyZWF0ZSBhIGNvcHkgd2l0aCBgY29weSA9IHRmLmFkZCh5b3VyVGVuc29yLCAwKWAuXG4gKlxuICogU2VlIGB0Zi50ZW5zb3JgIGZvciBkZXRhaWxzIG9uIGhvdyB0byBjcmVhdGUgYSBgdGYuVGVuc29yYC5cbiAqXG4gKiBAZG9jIHtoZWFkaW5nOiAnVGVuc29ycycsIHN1YmhlYWRpbmc6ICdDbGFzc2VzJ31cbiAqL1xuZXhwb3J0IGNsYXNzIFRlbnNvcjxSIGV4dGVuZHMgUmFuayA9IFJhbms+IHtcbiAgLyoqIFVuaXF1ZSBpZCBvZiB0aGlzIHRlbnNvci4gKi9cbiAgcmVhZG9ubHkgaWQ6IG51bWJlcjtcbiAgLyoqXG4gICAqIElkIG9mIHRoZSBidWNrZXQgaG9sZGluZyB0aGUgZGF0YSBmb3IgdGhpcyB0ZW5zb3IuIE11bHRpcGxlIGFycmF5cyBjYW5cbiAgICogcG9pbnQgdG8gdGhlIHNhbWUgYnVja2V0IChlLmcuIHdoZW4gY2FsbGluZyBhcnJheS5yZXNoYXBlKCkpLlxuICAgKi9cbiAgZGF0YUlkOiBEYXRhSWQ7XG4gIC8qKiBUaGUgc2hhcGUgb2YgdGhlIHRlbnNvci4gKi9cbiAgcmVhZG9ubHkgc2hhcGU6IFNoYXBlTWFwW1JdO1xuICAvKiogTnVtYmVyIG9mIGVsZW1lbnRzIGluIHRoZSB0ZW5zb3IuICovXG4gIHJlYWRvbmx5IHNpemU6IG51bWJlcjtcbiAgLyoqIFRoZSBkYXRhIHR5cGUgZm9yIHRoZSBhcnJheS4gKi9cbiAgcmVhZG9ubHkgZHR5cGU6IERhdGFUeXBlO1xuICAvKiogVGhlIHJhbmsgdHlwZSBmb3IgdGhlIGFycmF5IChzZWUgYFJhbmtgIGVudW0pLiAqL1xuICByZWFkb25seSByYW5rVHlwZTogUjtcblxuICAvKiogV2hldGhlciB0aGlzIHRlbnNvciBoYXMgYmVlbiBnbG9iYWxseSBrZXB0LiAqL1xuICBrZXB0ID0gZmFsc2U7XG4gIC8qKiBUaGUgaWQgb2YgdGhlIHNjb3BlIHRoaXMgdGVuc29yIGlzIGJlaW5nIHRyYWNrZWQgaW4uICovXG4gIHNjb3BlSWQ6IG51bWJlcjtcblxuICAvKipcbiAgICogTnVtYmVyIG9mIGVsZW1lbnRzIHRvIHNraXAgaW4gZWFjaCBkaW1lbnNpb24gd2hlbiBpbmRleGluZy4gU2VlXG4gICAqIGh0dHBzOi8vZG9jcy5zY2lweS5vcmcvZG9jL251bXB5L3JlZmVyZW5jZS9nZW5lcmF0ZWQvXFxcbiAgICogbnVtcHkubmRhcnJheS5zdHJpZGVzLmh0bWxcbiAgICovXG4gIHJlYWRvbmx5IHN0cmlkZXM6IG51bWJlcltdO1xuXG4gIGNvbnN0cnVjdG9yKHNoYXBlOiBTaGFwZU1hcFtSXSwgZHR5cGU6IERhdGFUeXBlLCBkYXRhSWQ6IERhdGFJZCwgaWQ6IG51bWJlcikge1xuICAgIHRoaXMuc2hhcGUgPSBzaGFwZS5zbGljZSgpIGFzIFNoYXBlTWFwW1JdO1xuICAgIHRoaXMuZHR5cGUgPSBkdHlwZSB8fCAnZmxvYXQzMic7XG4gICAgdGhpcy5zaXplID0gdXRpbC5zaXplRnJvbVNoYXBlKHNoYXBlKTtcbiAgICB0aGlzLnN0cmlkZXMgPSBjb21wdXRlU3RyaWRlcyhzaGFwZSk7XG4gICAgdGhpcy5kYXRhSWQgPSBkYXRhSWQ7XG4gICAgdGhpcy5pZCA9IGlkO1xuICAgIHRoaXMucmFua1R5cGUgPSAodGhpcy5yYW5rIDwgNSA/IHRoaXMucmFuay50b1N0cmluZygpIDogJ2hpZ2hlcicpIGFzIFI7XG4gIH1cblxuICBnZXQgcmFuaygpOiBudW1iZXIge1xuICAgIHJldHVybiB0aGlzLnNoYXBlLmxlbmd0aDtcbiAgfVxuXG4gIC8qKlxuICAgKiBSZXR1cm5zIGEgcHJvbWlzZSBvZiBgdGYuVGVuc29yQnVmZmVyYCB0aGF0IGhvbGRzIHRoZSB1bmRlcmx5aW5nIGRhdGEuXG4gICAqXG4gICAqIEBkb2Mge2hlYWRpbmc6ICdUZW5zb3JzJywgc3ViaGVhZGluZzogJ0NsYXNzZXMnfVxuICAgKi9cbiAgYXN5bmMgYnVmZmVyPEQgZXh0ZW5kcyBEYXRhVHlwZSA9ICdmbG9hdDMyJz4oKTogUHJvbWlzZTxUZW5zb3JCdWZmZXI8UiwgRD4+IHtcbiAgICBjb25zdCB2YWxzID0gYXdhaXQgdGhpcy5kYXRhPEQ+KCk7XG4gICAgcmV0dXJuIG9wSGFuZGxlci5idWZmZXIodGhpcy5zaGFwZSwgdGhpcy5kdHlwZSBhcyBELCB2YWxzKTtcbiAgfVxuXG4gIC8qKlxuICAgKiBSZXR1cm5zIGEgYHRmLlRlbnNvckJ1ZmZlcmAgdGhhdCBob2xkcyB0aGUgdW5kZXJseWluZyBkYXRhLlxuICAgKiBAZG9jIHtoZWFkaW5nOiAnVGVuc29ycycsIHN1YmhlYWRpbmc6ICdDbGFzc2VzJ31cbiAgICovXG4gIGJ1ZmZlclN5bmM8RCBleHRlbmRzIERhdGFUeXBlID0gJ2Zsb2F0MzInPigpOiBUZW5zb3JCdWZmZXI8UiwgRD4ge1xuICAgIHJldHVybiBvcEhhbmRsZXIuYnVmZmVyKHRoaXMuc2hhcGUsIHRoaXMuZHR5cGUgYXMgRCwgdGhpcy5kYXRhU3luYygpKTtcbiAgfVxuXG4gIC8qKlxuICAgKiBSZXR1cm5zIHRoZSB0ZW5zb3IgZGF0YSBhcyBhIG5lc3RlZCBhcnJheS4gVGhlIHRyYW5zZmVyIG9mIGRhdGEgaXMgZG9uZVxuICAgKiBhc3luY2hyb25vdXNseS5cbiAgICpcbiAgICogQGRvYyB7aGVhZGluZzogJ1RlbnNvcnMnLCBzdWJoZWFkaW5nOiAnQ2xhc3Nlcyd9XG4gICAqL1xuICBhc3luYyBhcnJheSgpOiBQcm9taXNlPEFycmF5TWFwW1JdPiB7XG4gICAgY29uc3QgdmFscyA9IGF3YWl0IHRoaXMuZGF0YSgpO1xuICAgIHJldHVybiB0b05lc3RlZEFycmF5KHRoaXMuc2hhcGUsIHZhbHMsIHRoaXMuZHR5cGUgPT09ICdjb21wbGV4NjQnKSBhc1xuICAgICAgICBBcnJheU1hcFtSXTtcbiAgfVxuXG4gIC8qKlxuICAgKiBSZXR1cm5zIHRoZSB0ZW5zb3IgZGF0YSBhcyBhIG5lc3RlZCBhcnJheS4gVGhlIHRyYW5zZmVyIG9mIGRhdGEgaXMgZG9uZVxuICAgKiBzeW5jaHJvbm91c2x5LlxuICAgKlxuICAgKiBAZG9jIHtoZWFkaW5nOiAnVGVuc29ycycsIHN1YmhlYWRpbmc6ICdDbGFzc2VzJ31cbiAgICovXG4gIGFycmF5U3luYygpOiBBcnJheU1hcFtSXSB7XG4gICAgcmV0dXJuIHRvTmVzdGVkQXJyYXkoXG4gICAgICAgICAgICAgICB0aGlzLnNoYXBlLCB0aGlzLmRhdGFTeW5jKCksIHRoaXMuZHR5cGUgPT09ICdjb21wbGV4NjQnKSBhc1xuICAgICAgICBBcnJheU1hcFtSXTtcbiAgfVxuXG4gIC8qKlxuICAgKiBBc3luY2hyb25vdXNseSBkb3dubG9hZHMgdGhlIHZhbHVlcyBmcm9tIHRoZSBgdGYuVGVuc29yYC4gUmV0dXJucyBhXG4gICAqIHByb21pc2Ugb2YgYFR5cGVkQXJyYXlgIHRoYXQgcmVzb2x2ZXMgd2hlbiB0aGUgY29tcHV0YXRpb24gaGFzIGZpbmlzaGVkLlxuICAgKlxuICAgKiBAZG9jIHtoZWFkaW5nOiAnVGVuc29ycycsIHN1YmhlYWRpbmc6ICdDbGFzc2VzJ31cbiAgICovXG4gIGFzeW5jIGRhdGE8RCBleHRlbmRzIERhdGFUeXBlID0gTnVtZXJpY0RhdGFUeXBlPigpOiBQcm9taXNlPERhdGFUeXBlTWFwW0RdPiB7XG4gICAgdGhpcy50aHJvd0lmRGlzcG9zZWQoKTtcbiAgICBjb25zdCBkYXRhID0gdHJhY2tlckZuKCkucmVhZCh0aGlzLmRhdGFJZCk7XG4gICAgaWYgKHRoaXMuZHR5cGUgPT09ICdzdHJpbmcnKSB7XG4gICAgICBjb25zdCBieXRlcyA9IGF3YWl0IGRhdGEgYXMgVWludDhBcnJheVtdO1xuICAgICAgdHJ5IHtcbiAgICAgICAgcmV0dXJuIGJ5dGVzLm1hcChiID0+IHV0aWwuZGVjb2RlU3RyaW5nKGIpKSBhcyBEYXRhVHlwZU1hcFtEXTtcbiAgICAgIH0gY2F0Y2gge1xuICAgICAgICB0aHJvdyBuZXcgRXJyb3IoXG4gICAgICAgICAgICAnRmFpbGVkIHRvIGRlY29kZSB0aGUgc3RyaW5nIGJ5dGVzIGludG8gdXRmLTguICcgK1xuICAgICAgICAgICAgJ1RvIGdldCB0aGUgb3JpZ2luYWwgYnl0ZXMsIGNhbGwgdGVuc29yLmJ5dGVzKCkuJyk7XG4gICAgICB9XG4gICAgfVxuICAgIHJldHVybiBkYXRhIGFzIFByb21pc2U8RGF0YVR5cGVNYXBbRF0+O1xuICB9XG5cbiAgLyoqXG4gICAqIENvcHkgdGhlIHRlbnNvcidzIGRhdGEgdG8gYSBuZXcgR1BVIHJlc291cmNlLiBDb21wYXJpbmcgdG8gdGhlIGBkYXRhU3luYygpYFxuICAgKiBhbmQgYGRhdGEoKWAsIHRoaXMgbWV0aG9kIHByZXZlbnRzIGRhdGEgZnJvbSBiZWluZyBkb3dubG9hZGVkIHRvIENQVS5cbiAgICpcbiAgICogRm9yIFdlYkdMIGJhY2tlbmQsIHRoZSBkYXRhIHdpbGwgYmUgc3RvcmVkIG9uIGEgZGVuc2VseSBwYWNrZWQgdGV4dHVyZS5cbiAgICogVGhpcyBtZWFucyB0aGF0IHRoZSB0ZXh0dXJlIHdpbGwgdXNlIHRoZSBSR0JBIGNoYW5uZWxzIHRvIHN0b3JlIHZhbHVlLlxuICAgKlxuICAgKiBGb3IgV2ViR1BVIGJhY2tlbmQsIHRoZSBkYXRhIHdpbGwgYmUgc3RvcmVkIG9uIGEgYnVmZmVyLiBUaGVyZSBpcyBub1xuICAgKiBwYXJhbWV0ZXIsIHNvIGNhbiBub3QgdXNlIGFuIHVzZXIgZGVmaW5lZCBzaXplIHRvIGNyZWF0ZSB0aGUgYnVmZmVyLlxuICAgKlxuICAgKiBAcGFyYW0gb3B0aW9uczpcbiAgICogICAgIEZvciBXZWJHTCxcbiAgICogICAgICAgICAtIGN1c3RvbVRleFNoYXBlOiBPcHRpb25hbC4gSWYgc2V0LCB3aWxsIHVzZSB0aGUgdXNlciBkZWZpbmVkXG4gICAqICAgICB0ZXh0dXJlIHNoYXBlIHRvIGNyZWF0ZSB0aGUgdGV4dHVyZS5cbiAgICpcbiAgICogQHJldHVybnMgRm9yIFdlYkdMIGJhY2tlbmQsIGEgR1BVRGF0YSBjb250YWlucyB0aGUgbmV3IHRleHR1cmUgYW5kXG4gICAqICAgICBpdHMgaW5mb3JtYXRpb24uXG4gICAqICAgICB7XG4gICAqICAgICAgICB0ZW5zb3JSZWY6IFRoZSB0ZW5zb3IgdGhhdCBpcyBhc3NvY2lhdGVkIHdpdGggdGhpcyB0ZXh0dXJlLFxuICAgKiAgICAgICAgdGV4dHVyZTogV2ViR0xUZXh0dXJlLFxuICAgKiAgICAgICAgdGV4U2hhcGU6IFtudW1iZXIsIG51bWJlcl0gLy8gW2hlaWdodCwgd2lkdGhdXG4gICAqICAgICB9XG4gICAqXG4gICAqICAgICBGb3IgV2ViR1BVIGJhY2tlbmQsIGEgR1BVRGF0YSBjb250YWlucyB0aGUgbmV3IGJ1ZmZlciBhbmRcbiAgICogICAgIGl0cyBpbmZvcm1hdGlvbi5cbiAgICogICAgIHtcbiAgICogICAgICAgIHRlbnNvclJlZjogVGhlIHRlbnNvciB0aGF0IGlzIGFzc29jaWF0ZWQgd2l0aCB0aGlzIGJ1ZmZlcixcbiAgICogICAgICAgIGJ1ZmZlcjogR1BVQnVmZmVyLFxuICAgKiAgICAgICAgYnVmU2l6ZTogbnVtYmVyXG4gICAqICAgICB9XG4gICAqXG4gICAqICAgICBSZW1lbWJlciB0byBkaXNwb3NlIHRoZSBHUFVEYXRhIGFmdGVyIGl0IGlzIHVzZWQgYnlcbiAgICogICAgIGByZXMudGVuc29yUmVmLmRpc3Bvc2UoKWAuXG4gICAqXG4gICAqIEBkb2Mge2hlYWRpbmc6ICdUZW5zb3JzJywgc3ViaGVhZGluZzogJ0NsYXNzZXMnfVxuICAgKi9cbiAgZGF0YVRvR1BVKG9wdGlvbnM/OiBEYXRhVG9HUFVPcHRpb25zKTogR1BVRGF0YSB7XG4gICAgdGhpcy50aHJvd0lmRGlzcG9zZWQoKTtcbiAgICByZXR1cm4gdHJhY2tlckZuKCkucmVhZFRvR1BVKHRoaXMuZGF0YUlkLCBvcHRpb25zKTtcbiAgfVxuXG4gIC8qKlxuICAgKiBTeW5jaHJvbm91c2x5IGRvd25sb2FkcyB0aGUgdmFsdWVzIGZyb20gdGhlIGB0Zi5UZW5zb3JgLiBUaGlzIGJsb2NrcyB0aGVcbiAgICogVUkgdGhyZWFkIHVudGlsIHRoZSB2YWx1ZXMgYXJlIHJlYWR5LCB3aGljaCBjYW4gY2F1c2UgcGVyZm9ybWFuY2UgaXNzdWVzLlxuICAgKlxuICAgKiBAZG9jIHtoZWFkaW5nOiAnVGVuc29ycycsIHN1YmhlYWRpbmc6ICdDbGFzc2VzJ31cbiAgICovXG4gIGRhdGFTeW5jPEQgZXh0ZW5kcyBEYXRhVHlwZSA9IE51bWVyaWNEYXRhVHlwZT4oKTogRGF0YVR5cGVNYXBbRF0ge1xuICAgIHRoaXMudGhyb3dJZkRpc3Bvc2VkKCk7XG4gICAgY29uc3QgZGF0YSA9IHRyYWNrZXJGbigpLnJlYWRTeW5jKHRoaXMuZGF0YUlkKTtcbiAgICBpZiAodGhpcy5kdHlwZSA9PT0gJ3N0cmluZycpIHtcbiAgICAgIHRyeSB7XG4gICAgICAgIHJldHVybiAoZGF0YSBhcyBVaW50OEFycmF5W10pLm1hcChiID0+IHV0aWwuZGVjb2RlU3RyaW5nKGIpKSBhc1xuICAgICAgICAgICAgRGF0YVR5cGVNYXBbRF07XG4gICAgICB9IGNhdGNoIHtcbiAgICAgICAgdGhyb3cgbmV3IEVycm9yKFxuICAgICAgICAgICAgJ0ZhaWxlZCB0byBkZWNvZGUgdGhlIHN0cmluZyBieXRlcyBpbnRvIHV0Zi04LiAnICtcbiAgICAgICAgICAgICdUbyBnZXQgdGhlIG9yaWdpbmFsIGJ5dGVzLCBjYWxsIHRlbnNvci5ieXRlcygpLicpO1xuICAgICAgfVxuICAgIH1cbiAgICByZXR1cm4gZGF0YSBhcyBEYXRhVHlwZU1hcFtEXTtcbiAgfVxuXG4gIC8qKiBSZXR1cm5zIHRoZSB1bmRlcmx5aW5nIGJ5dGVzIG9mIHRoZSB0ZW5zb3IncyBkYXRhLiAqL1xuICBhc3luYyBieXRlcygpOiBQcm9taXNlPFVpbnQ4QXJyYXlbXXxVaW50OEFycmF5PiB7XG4gICAgdGhpcy50aHJvd0lmRGlzcG9zZWQoKTtcbiAgICBjb25zdCBkYXRhID0gYXdhaXQgdHJhY2tlckZuKCkucmVhZCh0aGlzLmRhdGFJZCk7XG4gICAgaWYgKHRoaXMuZHR5cGUgPT09ICdzdHJpbmcnKSB7XG4gICAgICByZXR1cm4gZGF0YSBhcyBVaW50OEFycmF5W107XG4gICAgfSBlbHNlIHtcbiAgICAgIHJldHVybiBuZXcgVWludDhBcnJheSgoZGF0YSBhcyBUeXBlZEFycmF5KS5idWZmZXIpO1xuICAgIH1cbiAgfVxuXG4gIC8qKlxuICAgKiBEaXNwb3NlcyBgdGYuVGVuc29yYCBmcm9tIG1lbW9yeS5cbiAgICpcbiAgICogQGRvYyB7aGVhZGluZzogJ1RlbnNvcnMnLCBzdWJoZWFkaW5nOiAnQ2xhc3Nlcyd9XG4gICAqL1xuICBkaXNwb3NlKCk6IHZvaWQge1xuICAgIGlmICh0aGlzLmlzRGlzcG9zZWQpIHtcbiAgICAgIHJldHVybjtcbiAgICB9XG4gICAgdHJhY2tlckZuKCkuZGlzcG9zZVRlbnNvcih0aGlzKTtcbiAgICB0aGlzLmlzRGlzcG9zZWRJbnRlcm5hbCA9IHRydWU7XG4gIH1cblxuICBwcm90ZWN0ZWQgaXNEaXNwb3NlZEludGVybmFsID0gZmFsc2U7XG4gIGdldCBpc0Rpc3Bvc2VkKCk6IGJvb2xlYW4ge1xuICAgIHJldHVybiB0aGlzLmlzRGlzcG9zZWRJbnRlcm5hbDtcbiAgfVxuXG4gIHRocm93SWZEaXNwb3NlZCgpIHtcbiAgICBpZiAodGhpcy5pc0Rpc3Bvc2VkKSB7XG4gICAgICB0aHJvdyBuZXcgRXJyb3IoYFRlbnNvciBpcyBkaXNwb3NlZC5gKTtcbiAgICB9XG4gIH1cblxuICAvKipcbiAgICogUHJpbnRzIHRoZSBgdGYuVGVuc29yYC4gU2VlIGB0Zi5wcmludGAgZm9yIGRldGFpbHMuXG4gICAqXG4gICAqIEBwYXJhbSB2ZXJib3NlIFdoZXRoZXIgdG8gcHJpbnQgdmVyYm9zZSBpbmZvcm1hdGlvbiBhYm91dCB0aGUgdGVuc29yLFxuICAgKiAgICBpbmNsdWRpbmcgZHR5cGUgYW5kIHNpemUuXG4gICAqXG4gICAqIEBkb2Mge2hlYWRpbmc6ICdUZW5zb3JzJywgc3ViaGVhZGluZzogJ0NsYXNzZXMnfVxuICAgKi9cbiAgcHJpbnQodmVyYm9zZSA9IGZhbHNlKTogdm9pZCB7XG4gICAgcmV0dXJuIG9wSGFuZGxlci5wcmludCh0aGlzLCB2ZXJib3NlKTtcbiAgfVxuXG4gIC8qKlxuICAgKiBSZXR1cm5zIGEgY29weSBvZiB0aGUgdGVuc29yLiBTZWUgYHRmLmNsb25lYCBmb3IgZGV0YWlscy5cbiAgICogQGRvYyB7aGVhZGluZzogJ1RlbnNvcnMnLCBzdWJoZWFkaW5nOiAnQ2xhc3Nlcyd9XG4gICAqL1xuICBjbG9uZTxUIGV4dGVuZHMgVGVuc29yPih0aGlzOiBUKTogVCB7XG4gICAgdGhpcy50aHJvd0lmRGlzcG9zZWQoKTtcbiAgICByZXR1cm4gb3BIYW5kbGVyLmNsb25lKHRoaXMpO1xuICB9XG5cbiAgLyoqXG4gICAqIFJldHVybnMgYSBodW1hbi1yZWFkYWJsZSBkZXNjcmlwdGlvbiBvZiB0aGUgdGVuc29yLiBVc2VmdWwgZm9yIGxvZ2dpbmcuXG4gICAqXG4gICAqIEBkb2Mge2hlYWRpbmc6ICdUZW5zb3JzJywgc3ViaGVhZGluZzogJ0NsYXNzZXMnfVxuICAgKi9cbiAgdG9TdHJpbmcodmVyYm9zZSA9IGZhbHNlKTogc3RyaW5nIHtcbiAgICBjb25zdCB2YWxzID0gdGhpcy5kYXRhU3luYygpO1xuICAgIHJldHVybiB0ZW5zb3JUb1N0cmluZyh2YWxzLCB0aGlzLnNoYXBlLCB0aGlzLmR0eXBlLCB2ZXJib3NlKTtcbiAgfVxuXG4gIGNhc3Q8VCBleHRlbmRzIHRoaXM+KGR0eXBlOiBEYXRhVHlwZSk6IFQge1xuICAgIHRoaXMudGhyb3dJZkRpc3Bvc2VkKCk7XG4gICAgcmV0dXJuIG9wSGFuZGxlci5jYXN0KHRoaXMgYXMgVCwgZHR5cGUpO1xuICB9XG4gIHZhcmlhYmxlKHRyYWluYWJsZSA9IHRydWUsIG5hbWU/OiBzdHJpbmcsIGR0eXBlPzogRGF0YVR5cGUpOiBWYXJpYWJsZTxSPiB7XG4gICAgdGhpcy50aHJvd0lmRGlzcG9zZWQoKTtcbiAgICByZXR1cm4gdHJhY2tlckZuKCkubWFrZVZhcmlhYmxlKHRoaXMsIHRyYWluYWJsZSwgbmFtZSwgZHR5cGUpIGFzXG4gICAgICAgIFZhcmlhYmxlPFI+O1xuICB9XG59XG5cbk9iamVjdC5kZWZpbmVQcm9wZXJ0eShUZW5zb3IsIFN5bWJvbC5oYXNJbnN0YW5jZSwge1xuICB2YWx1ZTogKGluc3RhbmNlOiBUZW5zb3IpID0+IHtcbiAgICAvLyBJbXBsZW1lbnRhdGlvbiBub3RlOiB3ZSBzaG91bGQgdXNlIHByb3BlcnRpZXMgb2YgdGhlIG9iamVjdCB0aGF0IHdpbGwgYmVcbiAgICAvLyBkZWZpbmVkIGJlZm9yZSB0aGUgY29uc3RydWN0b3IgYm9keSBoYXMgZmluaXNoZWQgZXhlY3V0aW5nIChtZXRob2RzKS5cbiAgICAvLyBUaGlzIGlzIGJlY2F1c2Ugd2hlbiB0aGlzIGNvZGUgaXMgdHJhbnNwaWxlZCBieSBiYWJlbCwgYmFiZWwgd2lsbCBjYWxsXG4gICAgLy8gY2xhc3NDYWxsQ2hlY2sgYmVmb3JlIHRoZSBjb25zdHJ1Y3RvciBib2R5IGlzIHJ1bi5cbiAgICAvLyBTZWUgaHR0cHM6Ly9naXRodWIuY29tL3RlbnNvcmZsb3cvdGZqcy9pc3N1ZXMvMzM4NCBmb3IgYmFja3N0b3J5LlxuICAgIHJldHVybiAhIWluc3RhbmNlICYmIGluc3RhbmNlLmRhdGEgIT0gbnVsbCAmJiBpbnN0YW5jZS5kYXRhU3luYyAhPSBudWxsICYmXG4gICAgICAgIGluc3RhbmNlLnRocm93SWZEaXNwb3NlZCAhPSBudWxsO1xuICB9XG59KTtcblxuZXhwb3J0IGZ1bmN0aW9uIGdldEdsb2JhbFRlbnNvckNsYXNzKCkge1xuICAvLyBVc2UgZ2V0R2xvYmFsIHNvIHRoYXQgd2UgY2FuIGF1Z21lbnQgdGhlIFRlbnNvciBjbGFzcyBhY3Jvc3MgcGFja2FnZVxuICAvLyBib3VuZGFyaWVzIGJlY2FzZSB0aGUgbm9kZSByZXNvbHV0aW9uIGFsZyBtYXkgcmVzdWx0IGluIGRpZmZlcmVudCBtb2R1bGVzXG4gIC8vIGJlaW5nIHJldHVybmVkIGZvciB0aGlzIGZpbGUgZGVwZW5kaW5nIG9uIHRoZSBwYXRoIHRoZXkgYXJlIGxvYWRlZCBmcm9tLlxuICByZXR1cm4gZ2V0R2xvYmFsKCdUZW5zb3InLCAoKSA9PiB7XG4gICAgcmV0dXJuIFRlbnNvcjtcbiAgfSk7XG59XG5cbi8vIEdsb2JhbCBzaWRlIGVmZmVjdC4gQ2FjaGUgZ2xvYmFsIHJlZmVyZW5jZSB0byBUZW5zb3IgY2xhc3NcbmdldEdsb2JhbFRlbnNvckNsYXNzKCk7XG5cbmV4cG9ydCBpbnRlcmZhY2UgTnVtZXJpY1RlbnNvcjxSIGV4dGVuZHMgUmFuayA9IFJhbms+IGV4dGVuZHMgVGVuc29yPFI+IHtcbiAgZHR5cGU6IE51bWVyaWNEYXRhVHlwZTtcbiAgZGF0YVN5bmM8RCBleHRlbmRzIERhdGFUeXBlID0gTnVtZXJpY0RhdGFUeXBlPigpOiBEYXRhVHlwZU1hcFtEXTtcbiAgZGF0YTxEIGV4dGVuZHMgRGF0YVR5cGUgPSBOdW1lcmljRGF0YVR5cGU+KCk6IFByb21pc2U8RGF0YVR5cGVNYXBbRF0+O1xuICBkYXRhVG9HUFUob3B0aW9ucz86IERhdGFUb0dQVU9wdGlvbnMpOiBHUFVEYXRhO1xufVxuXG5leHBvcnQgaW50ZXJmYWNlIFN0cmluZ1RlbnNvcjxSIGV4dGVuZHMgUmFuayA9IFJhbms+IGV4dGVuZHMgVGVuc29yPFI+IHtcbiAgZHR5cGU6ICdzdHJpbmcnO1xuICBkYXRhU3luYzxEIGV4dGVuZHMgRGF0YVR5cGUgPSAnc3RyaW5nJz4oKTogRGF0YVR5cGVNYXBbRF07XG4gIGRhdGE8RCBleHRlbmRzIERhdGFUeXBlID0gJ3N0cmluZyc+KCk6IFByb21pc2U8RGF0YVR5cGVNYXBbRF0+O1xufVxuXG4vKiogQGRvY2xpbmsgVGVuc29yICovXG5leHBvcnQgdHlwZSBTY2FsYXIgPSBUZW5zb3I8UmFuay5SMD47XG4vKiogQGRvY2xpbmsgVGVuc29yICovXG5leHBvcnQgdHlwZSBUZW5zb3IxRCA9IFRlbnNvcjxSYW5rLlIxPjtcbi8qKiBAZG9jbGluayBUZW5zb3IgKi9cbmV4cG9ydCB0eXBlIFRlbnNvcjJEID0gVGVuc29yPFJhbmsuUjI+O1xuLyoqIEBkb2NsaW5rIFRlbnNvciAqL1xuZXhwb3J0IHR5cGUgVGVuc29yM0QgPSBUZW5zb3I8UmFuay5SMz47XG4vKiogQGRvY2xpbmsgVGVuc29yICovXG5leHBvcnQgdHlwZSBUZW5zb3I0RCA9IFRlbnNvcjxSYW5rLlI0Pjtcbi8qKiBAZG9jbGluayBUZW5zb3IgKi9cbmV4cG9ydCB0eXBlIFRlbnNvcjVEID0gVGVuc29yPFJhbmsuUjU+O1xuLyoqIEBkb2NsaW5rIFRlbnNvciAqL1xuZXhwb3J0IHR5cGUgVGVuc29yNkQgPSBUZW5zb3I8UmFuay5SNj47XG5cbi8qKlxuICogQSBtdXRhYmxlIGB0Zi5UZW5zb3JgLCB1c2VmdWwgZm9yIHBlcnNpc3Rpbmcgc3RhdGUsIGUuZy4gZm9yIHRyYWluaW5nLlxuICpcbiAqIEBkb2Mge2hlYWRpbmc6ICdUZW5zb3JzJywgc3ViaGVhZGluZzogJ0NsYXNzZXMnfVxuICovXG5leHBvcnQgY2xhc3MgVmFyaWFibGU8UiBleHRlbmRzIFJhbmsgPSBSYW5rPiBleHRlbmRzIFRlbnNvcjxSPiB7XG4gIG5hbWU6IHN0cmluZztcblxuICBjb25zdHJ1Y3RvcihcbiAgICAgIGluaXRpYWxWYWx1ZTogVGVuc29yPFI+LCBwdWJsaWMgdHJhaW5hYmxlOiBib29sZWFuLCBuYW1lOiBzdHJpbmcsXG4gICAgICB0ZW5zb3JJZDogbnVtYmVyKSB7XG4gICAgc3VwZXIoXG4gICAgICAgIGluaXRpYWxWYWx1ZS5zaGFwZSwgaW5pdGlhbFZhbHVlLmR0eXBlLCBpbml0aWFsVmFsdWUuZGF0YUlkLCB0ZW5zb3JJZCk7XG4gICAgdGhpcy5uYW1lID0gbmFtZTtcbiAgfVxuXG4gIC8qKlxuICAgKiBBc3NpZ24gYSBuZXcgYHRmLlRlbnNvcmAgdG8gdGhpcyB2YXJpYWJsZS4gVGhlIG5ldyBgdGYuVGVuc29yYCBtdXN0IGhhdmVcbiAgICogdGhlIHNhbWUgc2hhcGUgYW5kIGR0eXBlIGFzIHRoZSBvbGQgYHRmLlRlbnNvcmAuXG4gICAqXG4gICAqIEBwYXJhbSBuZXdWYWx1ZSBOZXcgdGVuc29yIHRvIGJlIGFzc2lnbmVkIHRvIHRoaXMgdmFyaWFibGUuXG4gICAqXG4gICAqIEBkb2Mge2hlYWRpbmc6ICdUZW5zb3JzJywgc3ViaGVhZGluZzogJ0NsYXNzZXMnfVxuICAgKi9cbiAgYXNzaWduKG5ld1ZhbHVlOiBUZW5zb3I8Uj4pOiB2b2lkIHtcbiAgICBpZiAobmV3VmFsdWUuZHR5cGUgIT09IHRoaXMuZHR5cGUpIHtcbiAgICAgIHRocm93IG5ldyBFcnJvcihcbiAgICAgICAgICBgZHR5cGUgb2YgdGhlIG5ldyB2YWx1ZSAoJHtuZXdWYWx1ZS5kdHlwZX0pIGFuZCBgICtcbiAgICAgICAgICBgcHJldmlvdXMgdmFsdWUgKCR7dGhpcy5kdHlwZX0pIG11c3QgbWF0Y2hgKTtcbiAgICB9XG4gICAgaWYgKCF1dGlsLmFycmF5c0VxdWFsKG5ld1ZhbHVlLnNoYXBlLCB0aGlzLnNoYXBlKSkge1xuICAgICAgdGhyb3cgbmV3IEVycm9yKFxuICAgICAgICAgIGBzaGFwZSBvZiB0aGUgbmV3IHZhbHVlICgke25ld1ZhbHVlLnNoYXBlfSkgYW5kIGAgK1xuICAgICAgICAgIGBwcmV2aW91cyB2YWx1ZSAoJHt0aGlzLnNoYXBlfSkgbXVzdCBtYXRjaGApO1xuICAgIH1cbiAgICB0cmFja2VyRm4oKS5kaXNwb3NlVGVuc29yKHRoaXMpO1xuICAgIHRoaXMuZGF0YUlkID0gbmV3VmFsdWUuZGF0YUlkO1xuICAgIHRyYWNrZXJGbigpLmluY1JlZih0aGlzLCBudWxsIC8qIGJhY2tlbmQgKi8pO1xuICB9XG5cbiAgZGlzcG9zZSgpOiB2b2lkIHtcbiAgICB0cmFja2VyRm4oKS5kaXNwb3NlVmFyaWFibGUodGhpcyk7XG4gICAgdGhpcy5pc0Rpc3Bvc2VkSW50ZXJuYWwgPSB0cnVlO1xuICB9XG59XG5cbk9iamVjdC5kZWZpbmVQcm9wZXJ0eShWYXJpYWJsZSwgU3ltYm9sLmhhc0luc3RhbmNlLCB7XG4gIHZhbHVlOiAoaW5zdGFuY2U6IFZhcmlhYmxlKSA9PiB7XG4gICAgcmV0dXJuIGluc3RhbmNlIGluc3RhbmNlb2YgVGVuc29yICYmIGluc3RhbmNlLmFzc2lnbiAhPSBudWxsICYmXG4gICAgICAgIGluc3RhbmNlLmFzc2lnbiBpbnN0YW5jZW9mIEZ1bmN0aW9uO1xuICB9XG59KTtcbiJdfQ==