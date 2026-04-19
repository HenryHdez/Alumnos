clc;
clear;
close all;

%% 1. Cargar imágenes desde carpetas
imds = imageDatastore('dataset', ...
    'IncludeSubfolders', true, ...
    'LabelSource', 'foldernames');

%% 2. Mostrar cantidad de imágenes por clase
disp('Cantidad total de imágenes por clase:');
disp(countEachLabel(imds));

%% 3. Dividir en entrenamiento y prueba
[imdsTrain, imdsTest] = splitEachLabel(imds, 0.7, 'randomized');

disp('Cantidad de entrenamiento por clase:');
disp(countEachLabel(imdsTrain));

disp('Cantidad de prueba por clase:');
disp(countEachLabel(imdsTest));

%% 4. Tamaño de entrada
tament = [64 64 3];

%% 5. Crear datastores aumentados y normalizar canales
augTrain = augmentedImageDatastore(tament, imdsTrain, ...
    'ColorPreprocessing', 'gray2rgb');

augTest = augmentedImageDatastore(tament, imdsTest, ...
    'ColorPreprocessing', 'gray2rgb');

%% 6. Definir red neuronal
layers = [
    imageInputLayer(tament)
    % Extraer caracteristicas locales de la imagen
    % Tamaño del filtro
    % Cantidad de filtros
    % Imagen de salida = entrada
    convolution2dLayer(3, 8, 'Padding', 'same')
    %Acelera la tasa de aprendizaje
    batchNormalizationLayer
    % Función de activación
    % leakyReluLayer(0.01), sigmoidLayer, reluLayer, tanhLayer
    leakyReluLayer(0.01)
    %Reduce la dimensionalidad a 2*2
    maxPooling2dLayer(2, 'Stride', 2)

    convolution2dLayer(3, 16, 'Padding', 'same')
    batchNormalizationLayer
    reluLayer
    maxPooling2dLayer(2, 'Stride', 2)

    convolution2dLayer(3, 32, 'Padding', 'same')
    batchNormalizationLayer
    reluLayer
    
    % Es la capa que recibe la info de las anteriores
    fullyConnectedLayer(3)
    softmaxLayer
    % Compara la predicción y la etiqueta real "Función de perdida"
    % regressionLayer, binaryCrossEntropyLayer, classificationLayer
    classificationLayer
];

%% 7. Opciones de entrenamiento
opciones = trainingOptions('adam', ...
    'MaxEpochs', 10, ...
    'Plots', 'training-progress');

%% 8. Entrenar la red
net = trainNetwork(augTrain, layers, opciones);

%% 9. Evaluar con datos de prueba
YPred = classify(net, augTest);
YTest = imdsTest.Labels;

accuracy = mean(YPred == YTest);
fprintf('Exactitud del clasificador: %.2f%%\n', accuracy*100);

%% 10. Mostrar matriz de confusión
figure;
confusionchart(YTest, YPred);
title('Matriz de confusión');

%% 11. Probar una imagen nueva
[archivo, ruta] = uigetfile({'*.jpg;*.png;*.jpeg;*.bmp', 'Archivos de imagen'});
img = imread(fullfile(ruta, archivo));
if size(img,3) == 1
    img = cat(3, img, img, img);
end
imgResize = imresize(img, [64 64]);
etiqueta = classify(net, imgResize);
disp(["Clase detectada", char(etiqueta)]);
