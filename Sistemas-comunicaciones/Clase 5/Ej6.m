clc; clear; close all;

%% 1. Secuencia binaria
bits = [1 1 0 1 0 0 1 0];
N = length(bits);

%% 2. Parámetros
Tb = 1;                       % Duración del bit
fs = 100;                     % Frecuencia de muestreo
t = 0:1/fs:Tb - 1/fs;         % Tiempo para un bit
half = length(t)/2;
time_total = 0:1/fs:N*Tb - 1/fs;

%% 3. Inicialización de señales
nrz_polar = [];
ami = [];
clock_signal = [];
ami_level = 1;  % para alternancia

%% 4. Codificación de la secuencia
for i = 1:N
    % --- NRZ Polar ---
    if bits(i) == 1
        nrz = ones(1, length(t));    % 1 → +1
    else
        nrz = -ones(1, length(t));   % 0 → -1
    end
    nrz_polar = [nrz_polar nrz];

    % --- AMI ---
    if bits(i) == 1
        ami_bit = ami_level * ones(1, length(t));
        % alterna polaridad
        ami_level = -ami_level;  
    else
        ami_bit = zeros(1, length(t));
    end
    ami = [ami ami_bit];

    % --- Reloj ---
    clk = [ones(1, half), zeros(1, half)];
    clock_signal = [clock_signal clk];
end

figure;

subplot(3,1,1);
plot(time_total, nrz_polar, 'LineWidth', 2);
title('Codificación NRZ Polar');
xlabel('Tiempo (s)');
ylabel('Amplitud');
axis([0 N -1.5 1.5]);
grid on;

subplot(3,1,2);
plot(time_total, ami, 'LineWidth', 2);
title('Codificación AMI');
xlabel('Tiempo (s)');
ylabel('Amplitud');
axis([0 N -1.5 1.5]);
grid on;

subplot(3,1,3);
plot(time_total, clock_signal, 'LineWidth', 2);
title('Señal de Reloj');
xlabel('Tiempo (s)');
ylabel('Nivel');
axis([0 N -0.5 1.5]);
grid on;
