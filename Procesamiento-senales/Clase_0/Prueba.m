clc; clear; close all;

% Parámetros de la señal
A = 1;                  % Amplitud
f = 1;                  % Frecuencia de la señal [Hz]
fs = 50;                % Frecuencia de muestreo [Hz]
N = 300;                 % Número de muestras
n = 0:N;                % Índice discreto

% Señal discreta senoidal
x = A * cos(pi/4 * (f/fs) * n);

t=0:0.1:pi;
y1=sin(t);
for i=1:length(y1)
    x = A * cos(pi/4 * (f/fs) * (n-i));
    stem(n,x,'ob',LineWidth=4)
    pause(0.1)
    drawnow();
end