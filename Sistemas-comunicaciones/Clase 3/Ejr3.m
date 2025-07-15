% FM con espectro
clc, clear, close all;

% Parámetros
N = 1024;           % Total de muestras
Fs = 20000;         % Frecuencia de muestreo [Hz]
Ts = 1 / Fs;        % Periodo de muestreo [s]
t = (0:N-1) * Ts;   % Vector de tiempo

Ac = 1;             % Amplitud de la portadora
fc = 100;           % Frecuencia de la portadora [Hz]
fm = 30;            % Frecuencia de la señal moduladora [Hz]
m = 1.5;            % Índice de modulación

% Señal moduladora
moduladora = sin(2*pi*fm*t);

% Señal modulada en FM
s = Ac .* cos(2*pi*fc*t + m .* moduladora);

% Graficar señal FM y moduladora
figure(1)
plot(t, s, 'b'); hold on;
plot(t, moduladora, 'r--');
title('Modulación FM y Señal Moduladora');
xlabel('Tiempo [s]'); ylabel('Amplitud');
legend('Señal FM', 'Moduladora');
grid on;

% Cálculo de la FFT
L = length(s);
S_f = fft(s);
S_f = abs(S_f/L);
S_f = S_f(1:L/2+1);
S_f(2:end-1) = 2*S_f(2:end-1);
f = Fs*(0:(L/2))/L;

figure(2)
plot(f, S_f, 'm');
title('Espectro de Frecuencia de la señal FM');
xlabel('Frecuencia [Hz]');
ylabel('Magnitud');
grid on;
