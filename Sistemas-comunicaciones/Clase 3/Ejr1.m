clc; clear; close all;

% Parámetros generales
N = 2048;
Fs = 1200;
Ts = 1/Fs;
t = (0:N-1)*Ts;
fp = 100;                           % Frecuencia portadora
fm = 10;                            % Frecuencia mensaje
m = sin(2*pi*fm*t);                 % Señal moduladora
f = linspace(-Fs/2, Fs/2, N);       % Eje de frecuencia
Ac = 1;                             % Amplitud de portadora

% Índices de modulación
ka_vals = [0.5, 1, 1.5];
labels = {'k_a < 1 (submodulación)', ...
    'k_a = 1 (crítica)', 'k_a > 1 (sobremodulación)'};

% -----------------------------
% Figura 1: Señales en el tiempo con envolvente
% -----------------------------
figure;
for k = 1:3
    ka = ka_vals(k);
    p = cos(2*pi*fp*t);
    s = Ac * (1 + ka * m) .* p;      
    envolvente_pos = Ac * (1 + ka * m);
    envolvente_neg = -envolvente_pos;

    subplot(3,1,k);
    plot(t, s, 'b', 'LineWidth', 1.5); hold on;
    plot(t, envolvente_pos, 'r--', 'LineWidth', 1.2); 
    plot(t, envolvente_neg, 'r--', 'LineWidth', 1.2);
    title(['Señal AM y envolvente - ', labels{k}]);
    xlabel('Tiempo [s]');
    ylabel('Amplitud');
    grid on;
    xlim([0 0.1]);
    legend('Señal AM','Envolvente');
end
sgtitle('Comparación temporal con envolventes (según k_a)');

% -----------------------------
% Figura 2: Espectros
% -----------------------------
figure;
for k = 1:3
    ka = ka_vals(k);
    s = Ac * (1 + ka * m) .* cos(2*pi*fp*t);
    % Magnitud del espectro
    S = fftshift(abs(fft(s))/N);  

    subplot(3,1,k);
    plot(f, S, 'LineWidth', 1.5);
    title(['Espectro |S(f)| - ', labels{k}]);
    xlabel('Frecuencia [Hz]');
    ylabel('Magnitud');
    grid on;
    xlim([fp - 4*fm, fp + 4*fm]);
end
sgtitle('Transformada de Fourier para distintas modulaciones k_a');
