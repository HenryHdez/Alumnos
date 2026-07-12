clc;
clear;
close all;

% 1. Parámetros de la señal

t = 0:0.001:1;           % Vector de tiempo
f = 5;                   % Frecuencia de la señal (Hz)
x = sin(2*pi*f*t);       % Señal senoidal

% 2. Nivel de SNR deseado
SNR_dB = 30;                             % Nivel de SNR en dB deseado
P_signal = mean(x.^2);                   % Potencia de la señal
P_signal_dB = 10 * log10(P_signal);      % Potencia de la señal en dB

% 3. Calcular potencia del ruido para lograr ese SNR
P_noise = P_signal / (10^(SNR_dB/10));   % Potencia en valor lineal
P_noise_dB = P_signal_dB - SNR_dB;       % Potencia del ruido en dB

% 4. Generar señal con ruido
n = sqrt(P_noise) * randn(size(t));      % Ruido blanco gaussiano
y = x + n;                               % Señal ruidosa

% 5. Estimación de SNR en dB
error = y - x;                       
P_error = mean(error.^2);         
SNR_estimado_dB = 10*log10(P_signal / P_error);
disp(['Potencia de la señal:      ', num2str(P_signal, '%.4f'), ' (', num2str(P_signal_dB, '%.2f'), ' dB)']);
disp(['Potencia del ruido:        ', num2str(P_noise, '%.4f'), ' (', num2str(P_noise_dB, '%.2f'), ' dB)']);
disp(['SNR diseñado:              ', num2str(SNR_dB), ' dB']);
disp(['SNR estimado (medido):     ', num2str(SNR_estimado_dB, '%.2f'), ' dB']);

figure;
plot(t, x, 'b', 'LineWidth', 1.5); hold on;
plot(t, y, 'r', 'LineWidth', 1);
legend('Señal original', 'Señal ruidosa');
xlabel('Tiempo (s)');
ylabel('Amplitud');
grid on;
