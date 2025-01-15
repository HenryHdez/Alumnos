net = googlenet; % Cargar modelo preentrenado
[audioIn, fs] = audioread('comando.wav'); % Leer audio
prediction = classify(net, audioIn);
disp(['Palabra reconocida: ', char(prediction)]);