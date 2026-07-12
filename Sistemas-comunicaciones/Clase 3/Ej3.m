clear, 
clc, 
close all

N=1024;               % Total de muestras
Fs=800;               % Frecuencia de muestreo [Hz]
Ts=1/Fs;              % Periodo de muestreo [s]
t=(0:N-1).*Ts;        % Vector de muestras

figure(1)

%% Señal moduladora
m=0.5;                                      % Índice de modulación
Fmod=10;                                    % Frecuencia señal moduladora
Amod=5;                                     % Amplitud señal moduladora
s_mod=Amod*sin(2*pi*Fmod.*t);
subplot(2,2,1)
plot(t,s_mod); title('señal moduladora');
xlabel('tiempo'); ylabel('Amplitud');

%% Señal portadora
Apor=Amod/m;                                % Amplitud de la señal portadora
Fpor=150;                                   % Frecuencia de la señal portadora
s_por=Apor*cos(2*pi*Fpor.*t);
subplot(2,2,2)
plot(t,s_por); title('Señal portadora');
xlabel('tiempo'); ylabel('Amplitud');

%% Modulación AM (DSB-SC)
s_mod_1=ammod(s_mod,Fpor,Fs,0,Apor); % 0 es la fase inicial
subplot(2,2,3)
plot(t,s_mod_1); title('Señal modulada');
xlabel('tiempo'); ylabel('Amplitud');

%% Espectro de frecuencias (DSB-SC)
[fx, s_f]=Fourier(s_mod_1,Fs);
subplot(2,2,4)
plot(fx,s_f); title('Espectro de frecuencias');
xlabel('Frecuencia [Hz]'); ylabel('Amplitud');

function [f, P1, Y] = Fourier(s, Fs)
    L = 2^nextpow2(Fs + 1);     % Longitud de la FFT (potencia de 2)
    Y = fft(s, L);              % Transformada rápida de Fourier
    Y = Y / sqrt(L);            % Normalización opcional
    P2 = abs(Y / L);            % Magnitud del espectro bilateral
    P1 = P2(1:L/2);             % Magnitud del espectro unilateral
    P1(2:end-1) = 2*P1(2:end-1);% Escalado para conservar la energía
    f = Fs * (0:(L/2 - 1)) / L; % Vector de frecuencias
end