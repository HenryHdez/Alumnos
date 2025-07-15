clear, clc, close all;

%% Parámetros generales
N = 1024;            % Total de muestras
Fs = 800;            % Frecuencia de muestreo [Hz]
Ts = 1/Fs;           % Periodo de muestreo [s]
t = (0:N-1)*Ts;      % Vector temporal

%% Señal moduladora
Fmod = 10;           % Frecuencia de la señal moduladora [Hz]
Amod = 5;            % Amplitud de la señal moduladora
s_mod = Amod * sin(2*pi*Fmod*t);  % Señal de información

%% Parámetros de la portadora
Fpor = 150;          % Frecuencia de la portadora [Hz]

%% Modulación SSB (banda lateral superior)
s_mod_ssb = ssbmod(s_mod, Fpor, Fs, 0, 'upper');

%% Representación temporal
figure(1)
subplot(2,1,1)
plot(t, s_mod_ssb, 'b', 'LineWidth', 1.5);
xlabel('Tiempo [s]')
ylabel('Amplitud')
title('Modulación AM - SSB (Upper Sideband)')
grid on

%% Espectro en frecuencia
[fx, S_F] = Fourier(s_mod_ssb, Fs);

subplot(2,1,2)
plot(fx, S_F, 'r', 'LineWidth', 1.5);
xlabel('Frecuencia [Hz]')
ylabel('Amplitud')
title('Espectro de frecuencia - SSB (Upper)')
grid on

%% Función auxiliar de transformada de Fourier
function [f, P1] = Fourier(s, Fs)
    L = length(s);
    Y = fft(s);
    Y = Y / sqrt(L);
    P2 = abs(Y / L);
    P1 = P2(1:L/2);
    P1(2:end-1) = 2*P1(2:end-1);
    f = Fs*(0:(L/2 -1))/L;
end
