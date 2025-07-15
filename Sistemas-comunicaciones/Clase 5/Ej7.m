clc; clear; close all;

%% 1. Parámetros y secuencia binaria
bits = [1 0 0 0 0 1 0 0 0 0 0 1 0 1 0 0];
Tb = 1;
fs = 100;
t = 0:1/fs:Tb - 1/fs;
half = length(t)/2;
N = length(bits);

%% 2. Inicialización de señales
nrz = []; time_nrz = [];
ami = []; time_ami = [];
hdb3 = []; time_hdb3 = [];
clock = []; time_clk = [];

%% Control para AMI y HDB3
ami_level = 1;
last_level = 1;
pulse_count = 0;
zero_buffer = 0;

%% Para anotar marcas y violaciones
marcas_time = [];
violaciones_time = [];

%% 3. Codificación
i = 1;
while i <= N
    % Tiempo base del bit actual
    tbit_base = (length(nrz)/fs);

    % === NRZ Polar ===
    nrz_val = bits(i)*2 - 1;
    nrz = [nrz nrz_val * ones(1, length(t))];
    time_nrz = [time_nrz t + tbit_base];

    % === AMI ===
    if bits(i) == 1
        ami = [ami ami_level * ones(1, length(t))];
        ami_level = -ami_level;
    else
        ami = [ami zeros(1, length(t))];
    end
    time_ami = [time_ami t + tbit_base];

    % === Señal de reloj ===
    clk = [ones(1, half), zeros(1, half)];
    clock = [clock clk];
    time_clk = [time_clk t(1:length(clk)) + (length(clock)-length(clk))/fs];

    % === HDB3 ===
    if bits(i) == 1
        % Bit 1 normal
        hdb3 = [hdb3 last_level * ones(1, length(t))];
        time_hdb3 = [time_hdb3 t + (length(hdb3)/fs - length(t)/fs)];
        last_level = -last_level;
        pulse_count = pulse_count + 1;
        zero_buffer = 0;
        i = i + 1;
    else
        zero_buffer = zero_buffer + 1;
        if zero_buffer == 4
            start_t = length(hdb3)/fs;
            if mod(pulse_count, 2) == 0
                % Sustitución B00V
                % B
                hdb3 = [hdb3 last_level * ones(1, length(t))];
                time_hdb3 = [time_hdb3 t + start_t];
                marcas_time(end+1) = start_t + Tb/2;

                pulse_count = pulse_count + 1;

                % 0, 0
                for k = 1:2
                    hdb3 = [hdb3 zeros(1, length(t))];
                    time_hdb3 = [time_hdb3 t + (length(hdb3)/fs - length(t)/fs)];
                end

                % V
                hdb3 = [hdb3 last_level * ones(1, length(t))]; % misma polaridad que B
                time_hdb3 = [time_hdb3 t + (length(hdb3)/fs - length(t)/fs)];
                violaciones_time(end+1) = (length(hdb3)/fs - length(t)/fs) + Tb/2;
                last_level = -last_level;
            else
                % Sustitución 000V
                for k = 1:3
                    hdb3 = [hdb3 zeros(1, length(t))];
                    time_hdb3 = [time_hdb3 t + (length(hdb3)/fs - length(t)/fs)];
                end
                hdb3 = [hdb3 last_level * ones(1, length(t))]; % misma polaridad
                time_hdb3 = [time_hdb3 t + (length(hdb3)/fs - length(t)/fs)];
                violaciones_time(end+1) = (length(hdb3)/fs - length(t)/fs) + Tb/2;
                last_level = -last_level;
            end
            zero_buffer = 0;
            i = i + 1;
        else
            % Bit 0 común
            hdb3 = [hdb3 zeros(1, length(t))];
            time_hdb3 = [time_hdb3 t + (length(hdb3)/fs - length(t)/fs)];
            i = i + 1;
        end
    end
end

figure;

subplot(4,1,1);
plot(time_nrz, nrz, 'LineWidth', 2);
title('Codificación NRZ Polar');
xlabel('Tiempo (s)'); ylabel('Amplitud');
axis([0 max(time_nrz) -1.5 1.5]); grid on;

subplot(4,1,2);
plot(time_ami, ami, 'LineWidth', 2);
title('Codificación AMI');
xlabel('Tiempo (s)'); ylabel('Amplitud');
axis([0 max(time_ami) -1.5 1.5]); grid on;

subplot(4,1,3);
plot(time_hdb3, hdb3, 'LineWidth', 2); hold on;
title('Codificación HDB3 con Marcas (B) y Violaciones (V)');
xlabel('Tiempo (s)'); ylabel('Amplitud');
axis([0 max(time_hdb3) -1.5 1.5]); grid on;

for k = 1:length(marcas_time)
    text(marcas_time(k), 1.2, 'B', 'FontWeight', 'bold', 'Color', 'blue', 'FontSize', 12);
end
for k = 1:length(violaciones_time)
    text(violaciones_time(k), 1.2, 'V', 'FontWeight', 'bold', 'Color', 'red', 'FontSize', 12);
end

subplot(4,1,4);
plot(time_clk, clock, 'LineWidth', 2);
title('Señal de Reloj');
xlabel('Tiempo (s)'); ylabel('Nivel');
axis([0 max(time_clk) -0.5 1.5]); grid on;