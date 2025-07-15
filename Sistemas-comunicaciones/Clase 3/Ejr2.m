clear, clc, close all;

%% Parámetros generales
N = 1024;           % Número de muestras
Fs = 800;           % Frecuencia de muestreo [Hz]
Ts = 1/Fs;          % Periodo de muestreo [s]
t = (0:N-1)*Ts;     % Vector de tiempo

%% Señal moduladora
Fmod = 10;          % Frecuencia de la señal moduladora [Hz]
Amod = 5;           % Amplitud de la señal moduladora
s_mod = Amod * sin(2*pi*Fmod*t); % Señal moduladora

%% Señal portadora
Fpor = 150;         % Frecuencia de la portadora [Hz]
Apor = Amod;        % Amplitud portadora (puede ajustarse)
s_por = Apor * cos(2*pi*Fpor*t); % Portadora

%% AM - Modulación DSB-SC (sin portadora)
s_am_dsbsc = ammod(s_mod, Fpor, Fs, 0, Apor);

%% AM - Modulación SSB (Upper sideband)
s_am_ssb = ssbmod(s_mod, Fpor, Fs, 0, 'upper');

%% Gráficas en el dominio del tiempo
figure('Name', 'Comparación Temporal AM (DSB-SC vs SSB)', 'NumberTitle', 'off')

subplot(2,1,1)
plot(t, s_am_dsbsc, 'b')
xlabel('Tiempo [s]'); ylabel('Amplitud')
title('AM DSB-SC (dominio del tiempo)')
grid on

subplot(2,1,2)
plot(t, s_am_ssb, 'r')
xlabel('Tiempo [s]'); ylabel('Amplitud')
title('AM SSB (banda superior) - dominio del tiempo')
grid on

%% Gráficas en el dominio de la frecuencia
[fx1, S1] = Fourier(s_am_dsbsc, Fs);
[fx2, S2] = Fourier(s_am_ssb, Fs);

figure('Name', 'Comparación Espectral AM', 'NumberTitle', 'off')

subplot(2,1,1)
plot(fx1, S1, 'b')
xlabel('Frecuencia [Hz]'); ylabel('Amplitud')
title('Espectro AM DSB-SC')
grid on

subplot(2,1,2)
plot(fx2, S2, 'r')
xlabel('Frecuencia [Hz]'); ylabel('Amplitud')
title('Espectro AM SSB (banda superior)')
grid on

%% Función auxiliar: Transformada de Fourier (un solo lado)
function [f, P1] = Fourier(s, Fs)
    L = length(s);
    Y = fft(s);
    Y = Y / sqrt(L);
    P2 = abs(Y / L);
    P1 = P2(1:L/2);
    P1(2:end-1) = 2*P1(2:end-1);
    f = Fs*(0:(L/2 -1))/L;
end
