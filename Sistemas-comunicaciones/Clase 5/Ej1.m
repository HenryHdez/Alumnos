clc;
clear;
close all;

% Parámetros generales
f = 5;                        % Frecuencia de la señal (Hz)
fs = 20;                      % Frecuencia de muestreo (Hz)
Ts = 1/fs;
t = linspace(0, 1, 1000);     % Tiempo continuo (1 s)
x = sin(2*pi*f*t);            % Señal original continua

% Instantes de muestreo y valores muestreados
t_s = 0:Ts:1-Ts;
x_s = sin(2*pi*f*t_s);

%% 1. Muestreo Ideal
ideal_train = zeros(size(t));
for k = 1:length(t_s)
    [~, idx] = min(abs(t - t_s(k)));
    ideal_train(idx) = 1;
end

figure('Name','Muestreo ideal');
subplot(3,1,1)
plot(t, x, 'k', 'LineWidth', 2); title('Señal Continua');
ylabel('Amplitud'); grid on; xlim([0 0.5]);

subplot(3,1,2)
plot(t, ideal_train, 'r', 'LineWidth', 2); title('Tren de Pulsos');
ylabel('Pulso'); ylim([-0.2 1.2]); grid on; xlim([0 0.5]);

subplot(3,1,3)
plot(t, x, '--k', 'LineWidth', 1); hold on;
stem(t_s, x_s, 'b', 'filled'); title('Superposición');
xlabel('Tiempo [s]'); ylabel('Amplitud'); grid on; xlim([0 0.5]);

%% 2. Muestreo Natural (con forma del seno)
anchura = Ts * 0.3;
natural_train = zeros(size(t));
x_natural = zeros(size(t));

for k = 1:length(t_s)
    indices = find((t >= t_s(k)) & (t < t_s(k) + anchura));
    natural_train(indices) = 1;
    x_natural(indices) = x(indices);
end

figure('Name','Muestreo natural');
subplot(3,1,1)
plot(t, x, 'k', 'LineWidth', 2); title('Señal Continua');
ylabel('Amplitud'); grid on; xlim([0 0.5]);

subplot(3,1,2)
plot(t, natural_train, 'b', 'LineWidth', 2); title('Tren de Pulsos');
ylabel('Pulso'); ylim([-0.2 1.2]); grid on; xlim([0 0.5]);

subplot(3,1,3)
plot(t, x, '--k', 'LineWidth', 1); hold on;
plot(t, x_natural, 'b', 'LineWidth', 2);
title('Superposición');
xlabel('Tiempo [s]'); ylabel('Amplitud'); grid on; xlim([0 0.5]);

%% 3. Sample and Hold
t_hold = []; x_hold = [];

for k = 1:length(t_s)
    t_hold = [t_hold t_s(k)];
    x_hold = [x_hold x_s(k)];
    if k < length(t_s)
        t_hold = [t_hold t_s(k+1)];
        x_hold = [x_hold x_s(k)];
    else
        t_hold = [t_hold t_s(k)+Ts];
        x_hold = [x_hold x_s(k)];
    end
end

%% Tren de pulsos
hold_train = zeros(size(t));
pulso_duracion = round(length(t) * 0.002);

for k = 1:length(t_s)
    [~, idx] = min(abs(t - t_s(k)));
    fin_idx = min(idx + pulso_duracion, length(t));
    hold_train(idx:fin_idx) = 1;
end

figure('Name','Sample and Hold');
subplot(3,1,1)
plot(t, x, 'k', 'LineWidth', 2); title('Señal Continua');
ylabel('Amplitud'); grid on; xlim([0 0.5]);

subplot(3,1,2)
plot(t, hold_train, 'g', 'LineWidth', 2); title('Tren de Pulsos');
ylabel('Pulso'); ylim([-0.2 1.2]); grid on; xlim([0 0.5]);

subplot(3,1,3)
plot(t, x, '--k', 'LineWidth', 1); hold on;
stairs(t_hold, x_hold, 'g', 'LineWidth', 2);
title('Superposición');
xlabel('Tiempo [s]'); ylabel('Amplitud'); grid on; xlim([0 0.5]);
