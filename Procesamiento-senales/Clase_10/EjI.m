% Configurar micrófono: 44.1kHz, 16 bits, 1 canal
recObj = audiorecorder(44100, 16, 1); 
disp('Hable ahora (2 segundos)...');
recordblocking(recObj, 2); % Grabar 2 segundos
audioData = getaudiodata(recObj); % Obtener datos de audio
disp('Grabación completa.');


% Crear un espectrograma
fs = 44100; % Frecuencia de muestreo
winLength = round(0.03 * fs); % Ventana de 30 ms
overlap = round(0.02 * fs); % Solapamiento de 20 ms
nfft = 512; % Número de FFT

[s, f, t, ps] = spectrogram(audioData, winLength, overlap, nfft, fs, 'yaxis');
spectrogramImage = log(abs(ps) + 1); % Escalado logarítmico para resaltar patrones

% Guardar el espectrograma como imagen
imshow(imresize(mat2gray(spectrogramImage), [224, 224])); % Redimensionar a 224x224 para GoogLeNet
imwrite(mat2gray(spectrogramImage), 'spectrogram.jpg');


net = googlenet; % Cargar modelo preentrenado GoogLeNet
inputSize = net.Layers(1).InputSize; % Tamaño de entrada: [224 224 3]

% Leer y procesar el espectrograma
img = imread('spectrogram.jpg');
img = imresize(img, inputSize(1:2)); % Asegurar tamaño correcto
img = cat(3, img, img, img); % Convertir a 3 canales (RGB)

% Clasificar la palabra hablada
label = classify(net, img);
disp(['Palabra reconocida: ', char(label)]);
