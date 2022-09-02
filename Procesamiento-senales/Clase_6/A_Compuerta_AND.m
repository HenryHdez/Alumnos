clc
clear
% Crear una red neuronal de una entrada y una salida
red = network;
red.numInputs = 1;
red.numLayers = 2;
% Una forma alterna de crear la red es la siguiente
red = network(1,2);
% Cree la red neuronal y vea sus propiedades
% Este ejemplo muestra como:
%-Crear una entrada y dos capas
% This example shows how to create a one-input, two-layer, feedforward network. Only the first layer has a bias. An input weight connects to layer 1 from input 1. A layer weight connects to layer 2 from layer 1. Layer 2 is a network output and has a target.
% net = network(numInputs,numLayers,biasConnect,inputConnect,layerConnect,outputConnect) 
red = network(2,2,[1;0;0;0],[1; 0],[0 0; 1 0; 0 1; 1 1],[0 0 0 1]);
% You can view the network subobjects with the following code.

% red.inputs{1}
% red.layers{1}, red.layers{2}
% red.biases{1}
% red.inputWeights{1,1}, red.layerWeights{2,1}
% red.outputs{2}
% %You can alter the properties of any of the network subobjects. This code changes the transfer functions of both layers:
% 
% red.layers{1}.transferFcn = 'tansig';
% red.layers{2}.transferFcn = 'logsig';
% %You can view the weights for the connection from the first input to the first layer as follows. The weights for a connection from an input to a layer are stored in net.IW. If the values are not yet set, these result is empty.
% 
% 
% red.IW{1,1}
% %You can view the weights for the connection from the first layer to the second layer as follows. Weights for a connection from a layer to a layer are stored in net.LW. Again, if the values are not yet set, the result is empty.
% 
% red.LW{2,1}
% %You can view the bias values for the first layer as follows.
% 
% red.b{1}
% %To change the number of elements in input 1 to 2, set each element%s range:
% 
% red.inputs{1}.range = [0 1; -1 1];
% %To simulate the network for a two-element input vector, the code might look like this:

p = [0.5; -0.1];
y = sim(red,p)