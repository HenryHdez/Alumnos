clc; 
clear; 
close all;

%% 1. Secuencia binaria
bits = [1 1 0 1 0 0 1 0];
N = length(bits);           

%% 2. Parámetros de tiempo
Tb = 1;                     % Duración del bit
fs = 100;                   % Frecuencia de muestreo
t = 0:1/fs:Tb - 1/fs;       % Tiempo para un bit
time_total = 0:1/fs:N*Tb - 1/fs;

%% 3. Inicialización de señales
nrz_polar = [];     % Codificación NRZ Polar
rz_polar = [];      % Codificación RZ Polar
rz_unipolar = [];   % Codificación RZ Unipolar

for i = 1:N
    % --- NRZ Polar ---
    if bits(i) == 1
        nrz_bit = ones(1, length(t));      % 1 → +1
    else
        nrz_bit = -ones(1, length(t));     % 0 → -1
    end
    nrz_polar = [nrz_polar nrz_bit];

    % --- RZ Polar ---
    if bits(i) == 1
        rz_p = [ones(1, length(t)/2), zeros(1, length(t)/2)];  % 1 → +1 medio bit
    else
        rz_p = -[ones(1, length(t)/2), zeros(1, length(t)/2)]; % 0 → -1 medio bit
    end
    rz_polar = [rz_polar rz_p];

    % --- RZ Unipolar ---
    if bits(i) == 1
        rz_u = [ones(1, length(t)/2), zeros(1, length(t)/2)];  % 1 → +1 medio bit
    else
        rz_u = zeros(1, length(t));                            % 0 → 0
    end
    rz_unipolar = [rz_unipolar rz_u];
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
plot(time_total, rz_polar, 'LineWidth', 2);
title('Codificación RZ Polar');
xlabel('Tiempo (s)');
ylabel('Amplitud');
axis([0 N -1.5 1.5]);
grid on;

subplot(3,1,3);
plot(time_total, rz_unipolar, 'LineWidth', 2);
title('Codificación RZ Unipolar');
xlabel('Tiempo (s)');
ylabel('Amplitud');
axis([0 N -0.5 1.5]);
grid on;
