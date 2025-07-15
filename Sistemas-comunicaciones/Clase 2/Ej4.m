% Pulso rectangular
T = 1; fs = 1000; t = -2:1/fs:2;
x = double(abs(t) <= T/2);

% Espectro
N = length(t);
X = fftshift(fft(x, 2048));
f = linspace(-fs/2, fs/2, length(X));

% Magnitud normalizada
X_mag = abs(X) / max(abs(X));

% Graficar
plot(f, X_mag, 'LineWidth', 2); grid on;
xlabel('Frecuencia (Hz)');
ylabel('|X(f)| / max');
title('Espectro de un pulso rectangular');

% Línea -3 dB
hold on;
yline(0.707, '--r', '-3 dB');
