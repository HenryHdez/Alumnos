clear; clc; close all;

% ---------------------------
% Parámetros de simulación
% ---------------------------
N = 1024;                % Número de muestras
Fs = 800;                % Frecuencia de muestreo [Hz]
Ts = 1/Fs;               % Periodo de muestreo
t = (0:N-1)*Ts;          % Vector de tiempo

% ---------------------------
% Señal moduladora
% ---------------------------
Fmod = 10;                        % Frecuencia de mensaje [Hz]
Amod = 5;                         % Amplitud de la señal de mensaje
s_mod = Amod * sin(2*pi*Fmod*t);  % Señal de mensaje

% ---------------------------
% Portadora
% ---------------------------
Fpor = 150;              % Frecuencia de la portadora [Hz]
Apor = 5;                % Amplitud de portadora
ka = 1;                  % Índice de modulación

% ---------------------------
% Señal modulada AM
% ---------------------------
s_am = (1 + ka * s_mod) .* (Apor * cos(2*pi*Fpor*t));

% ---------------------------
% Filtro paso bajo
% ---------------------------
%Corte en la frecuencia moduladora
[num, den] = butter(5, Fmod*2/Fs); 
s_am_demod = amdemod(s_am, Fpor, Fs, 0, Apor, num, den);

% ---------------------------
% Transformada de Fourier
% ---------------------------
[S_mod_f, f] = Fourier(s_mod, Fs);
[S_am_f, ~] = Fourier(s_am, Fs);
[S_demod_f, ~] = Fourier(s_am_demod, Fs);

% ---------------------------
% Gráficas en el tiempo
% ---------------------------
figure(1);
subplot(3,1,1);
plot(t, s_mod, 'b'); grid on;
title('Señal moduladora (mensaje)');
xlabel('Tiempo [s]'); ylabel('Amplitud');

subplot(3,1,2);
plot(t, s_am, 'r'); grid on;
title('Señal modulada AM (con portadora)');
xlabel('Tiempo [s]'); ylabel('Amplitud');

subplot(3,1,3);
plot(t, s_am_demod, 'g'); grid on;
title('Señal demodulada');
xlabel('Tiempo [s]'); ylabel('Amplitud');

% ---------------------------
% Gráficas en el dominio de la frecuencia
% ---------------------------
figure(2);
subplot(3,1,1);
plot(f, S_mod_f, 'b'); grid on;
title('Espectro de la señal moduladora');
xlabel('Frecuencia [Hz]'); ylabel('Magnitud');

subplot(3,1,2);
plot(f, S_am_f, 'r'); grid on;
title('Espectro de la señal AM (modulada)');
xlabel('Frecuencia [Hz]'); ylabel('Magnitud');

subplot(3,1,3);
plot(f, S_demod_f, 'g'); grid on;
title('Espectro de la señal demodulada');
xlabel('Frecuencia [Hz]'); ylabel('Magnitud');

% ---------------------------
% Función auxiliar de Fourier
% ---------------------------
function [S_f, f] = Fourier(signal, Fs)
    N = length(signal);
    Y = fft(signal);
    Y = fftshift(Y);                  % Centrar en cero
    S_f = abs(Y) / N;                 % Magnitud normalizada
    f = linspace(-Fs/2, Fs/2, N);     % Eje de frecuencia
end
