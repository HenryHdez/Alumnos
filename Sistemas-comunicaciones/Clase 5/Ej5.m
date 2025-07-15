clc; clear; close all;

%% 1. Secuencia de bits
bits = [1 1 0 1 0 0 1 0];
N = length(bits);

%% 2. Parámetros
Tb = 1;                        % Duración del bit
fs = 100;                      % Frecuencia de muestreo
t = 0:1/fs:Tb - 1/fs;          % Tiempo por bit
half = length(t)/2;
time_total = 0:1/fs:N*Tb - 1/fs;

%% 3. Inicialización de señales
nrz_polar = [];
manchester_polar = [];
manchester_bipolar = [];
clock_signal = [];

%% Alternancia para bipolar
% comienza con +1
last_level = 1;  
for i = 1:N
    % --- NRZ Polar ---
    if bits(i) == 1
        nrz = ones(1, length(t));
    else
        nrz = -ones(1, length(t));
    end
    nrz_polar = [nrz_polar nrz];

    % --- Manchester Polar ---
    if bits(i) == 1
        mp = [ones(1, half), -ones(1, half)];  % 1 → alta a baja
    else
        mp = [-ones(1, half), ones(1, half)];  % 0 → baja a alta
    end
    manchester_polar = [manchester_polar mp];

    % --- Manchester Bipolar ---
    if bits(i) == 1
        level = last_level;
        mb = [level*ones(1, half), -level*ones(1, half)];
        %Cambiar signo
        last_level = -last_level;  
    else
        mb = [-ones(1, half), ones(1, half)];
    end
    manchester_bipolar = [manchester_bipolar mb];

    % --- Reloj ---
    clk = [ones(1, half), zeros(1, half)];
    clock_signal = [clock_signal clk];
end

figure;

subplot(4,1,1);
plot(time_total, nrz_polar, 'LineWidth', 2);
title('Codificación NRZ Polar');
xlabel('Tiempo (s)'); ylabel('Amplitud');
axis([0 N -1.5 1.5]); grid on;

subplot(4,1,2);
plot(time_total, manchester_polar, 'LineWidth', 2);
title('Codificación Manchester Polar');
xlabel('Tiempo (s)'); ylabel('Amplitud');
axis([0 N -1.5 1.5]); grid on;

subplot(4,1,3);
plot(time_total, manchester_bipolar, 'LineWidth', 2);
title('Codificación Manchester Bipolar (Alternante)');
xlabel('Tiempo (s)'); ylabel('Amplitud');
axis([0 N -1.5 1.5]); grid on;

subplot(4,1,4);
plot(time_total, clock_signal, 'LineWidth', 2);
title('Señal de Reloj');
xlabel('Tiempo (s)'); ylabel('Nivel');
axis([0 N -0.5 1.5]); grid on;
