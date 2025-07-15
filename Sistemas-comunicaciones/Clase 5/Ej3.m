clc; 
clear; 
close all;

%% 1. Definir la secuencia binaria
bits = [1 1 0 1 0 0 1 0];       
N = length(bits);           

%% 2. Parámetros de tiempo
Tb = 1;                           % Duración de cada bit en segundos
fs = 100;                         % Frecuencia de muestreo
t = 0:1/fs:Tb - 1/fs;             % Tiempo por bit
time_total = 0:1/fs:N*Tb - 1/fs;  % Tiempo total

%% 3. Inicialización de señales
nrz_unipolar = [];
nrz_polar = [];

%% 4. Construcción de las señales codificadas
for i = 1:N
    if bits(i) == 1
        unipolar = ones(1, length(t));     % 1 → +1
        polar = ones(1, length(t));        % 1 → +1
    else
        unipolar = zeros(1, length(t));    % 0 →  0
        polar = -ones(1, length(t));       % 0 → -1
    end
    nrz_unipolar = [nrz_unipolar unipolar];
    nrz_polar = [nrz_polar polar];
end

figure;

subplot(2,1,1);
plot(time_total, nrz_unipolar, 'LineWidth', 2);
title('Codificación NRZ Unipolar');
xlabel('Tiempo (s)');
ylabel('Amplitud');
axis([0 N -0.5 1.5]);
grid on;

subplot(2,1,2);
plot(time_total, nrz_polar, 'LineWidth', 2);
title('Codificación NRZ Polar');
xlabel('Tiempo (s)');
ylabel('Amplitud');
axis([0 N -1.5 1.5]);
grid on;