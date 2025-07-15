% FM
clc; clear; close all;

% Parámetros
N = 1024;              % Total de muestras
Fs = 1000;             % Frecuencia de muestreo [Hz]
Ts = 1/Fs;             % Periodo de muestreo [s]
t = (0:N-1)*Ts;        % Vector de tiempo

figure(1)

%% Señal moduladora
Fmod = 60;                        % Frecuencia de la señal moduladora [Hz]
Amod = 1;                         % Amplitud
s_mod = Amod * sin(2*pi*Fmod*t);  % Señal moduladora
subplot(2,2,1)
plot(t, s_mod)
title('Señal moduladora')
xlabel('tiempo'); ylabel('Amplitud')

%% Modulación FM
Fc = 200;              % Frecuencia de la portadora [Hz]
Fdev = 50;             % Desviación de frecuencia
s_mod_1 = fmmod(s_mod, Fc, Fs, Fdev); % Señal FM
subplot(2,2,2)
plot(t, s_mod_1)
title('Señal modulada')
xlabel('tiempo'); ylabel('Amplitud')

%% Espectro de frecuencias
[fx, s_f] = Fourier(s_mod_1, Fs);
subplot(2,2,3)
plot(fx, s_f)
grid on
title('Espectro de frecuencias')
xlabel('Frecuencia [Hz]'); ylabel('Amplitud')

%% Demodulación FM
sdemod = fmdemod(s_mod_1, Fc, Fs, Fdev);
subplot(2,2,4)
plot(t, sdemod)
title('Señal demodulada')
xlabel('tiempo'); ylabel('Amplitud')

function [f, P1] = Fourier(s, Fs)
    L = length(s);
    Y = fft(s);
    P2 = abs(Y/L);
    P1 = P2(1:floor(L/2)+1);
    P1(2:end-1) = 2*P1(2:end-1);
    f = Fs*(0:(L/2))/L;
end
