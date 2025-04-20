% Leer grabación de prueba
[x_test, fs] = audioread('test.wav');
mfcc_test = mfcc(x_test, fs);

% Inicializar y comparar
distancias = zeros(1, length(comandos));
mfcc_refs = cell(1, length(comandos));
x_refs = cell(1, length(comandos));

for i = 1:length(comandos)
    [x_ref, ~] = audioread([comandos{i}, '.wav']);
    mfcc_refs{i} = mfcc(x_ref, fs);
    x_refs{i} = x_ref;
    distancias(i) = dtw(mfcc_test', mfcc_refs{i}');
end

[~, idx] = min(distancias); % índice del comando más parecido

% ================================
% GRAFICAR COMPARACIÓN VISUAL
% ================================
t_test = (0:length(x_test)-1)/fs;
t_ref = (0:length(x_refs{idx})-1)/fs;

figure('Name', 'Comparación de Comando de Voz', 'NumberTitle', 'off');

% Señal original - Prueba
subplot(2,2,1)
plot(t_test, x_test);
title('🔊 Señal de prueba (test.wav)');
xlabel('Tiempo (s)');
ylabel('Amplitud');

% Señal reconocida
subplot(2,2,2)
plot(t_ref, x_refs{idx});
title(['🔈 Señal reconocida: ', comandos{idx}, '.wav']);
xlabel('Tiempo (s)');
ylabel('Amplitud');

% MFCC de prueba
subplot(2,2,3)
imagesc(mfcc_test');
axis xy;
title('🧠 MFCC de prueba');
xlabel('Tiempo (marcos)');
ylabel('Coeficientes');

% MFCC del comando reconocido
subplot(2,2,4)
imagesc(mfcc_refs{idx}');
axis xy;
title(['🧠 MFCC de "', comandos{idx}, '"']);
xlabel('Tiempo (marcos)');
ylabel('Coeficientes');
