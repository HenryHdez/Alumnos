% AM
clc, 
clear, 
close all;

N = 1024;               % Total de muestras
Fs = 1200;              % Frecuencia de muestreo [Hz]
Ts = 1/Fs;              % Periodo de muestreo [s]
t = (0:N-1).*Ts;        % Vector de muestras

Ac = 1;                 % Amplitud portadora
fp = 100;               % Frecuencia portadora
fm = 2;                 % Frecuencia señal a modular
ka = 0.8;                 % Índice modulación

p = cos(2*pi*fp*t);     % Señal portadora
m = sin(2*pi*fm*t);     % Señal a modular

s = Ac.*(1 + ka.*m).*p; % Señal modulada AM

% Graficar Modulación AM
figure;

subplot(3,1,1)
plot(t, p, 'b', 'LineWidth', 1.5)
title('Señal portadora')
xlabel('Tiempo [s]')
ylabel('Amplitud')
grid on

subplot(3,1,2)
plot(t, m, 'r', 'LineWidth', 1.5)
title('Señal a modular (mensaje)')
xlabel('Tiempo [s]')
ylabel('Amplitud')
grid on

subplot(3,1,3)
plot(t, s, 'k', 'LineWidth', 1.5)
title('Señal modulada AM')
xlabel('Tiempo [s]')
ylabel('Amplitud')
grid on
