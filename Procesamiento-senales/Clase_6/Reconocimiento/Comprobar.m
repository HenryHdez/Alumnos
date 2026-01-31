% Leer la grabación de prueba desde archivo
[x_test, fs] = audioread('test.wav');

% Calcular los coeficientes cepstrales en las frecuencias de Mel (MFCC)
% MFCC transforma la señal de audio en una representación más compacta
% y robusta que imita cómo el oído humano percibe el sonido.
% Cada fila de 'mfcc_test' representa una característica (coeficiente),
% y cada columna representa un instante de tiempo.
mfcc_test = mfcc(x_test, fs);

% Inicializar un vector para guardar las distancias DTW
% entre el audio de prueba y cada comando base.
distancias = zeros(1, length(comandos));

% Recorrer todas las grabaciones base (ej: 'arriba.wav', 'abajo.wav', etc.)
for i = 1:length(comandos)
    % Leer el archivo de audio del comando i
    [x_ref, ~] = audioread([comandos{i}, '.wav']);

    % Calcular los MFCC del audio de referencia
    mfcc_ref = mfcc(x_ref, fs);

    % Comparar los MFCC del audio de prueba con los del comando base usando DTW
    % DTW (Dynamic Time Warping) alinea secuencias similares pero
    % que pueden estar desfasadas en el tiempo (dicho a diferente velocidad).
    % Se aplica la transposición porque DTW espera: filas = características, columnas = tiempo
    distancias(i) = dtw(mfcc_test', mfcc_ref');
end

% Buscar la posición del comando que tuvo la menor distancia (mayor similitud)
[~, idx] = min(distancias);

% Mostrar el nombre del comando reconocido
fprintf('Comando reconocido: %s\n', comandos{idx});
