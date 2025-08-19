clc; clear; close all;

% Parámetros de la señal
A = 1;                  % Amplitud
f = 1;                  % Frecuencia de la señal [Hz]
fs = 50;                % Frecuencia de muestreo [Hz]
N = 50;                 % Número de muestras
n = 0:N;                % Índice discreto

% Señal discreta senoidal
x = A * sin(2 * pi * (f/fs) * n);

% Gráfica señal discreta
figure;
stem(n, x, 'b', 'LineWidth', 2, 'Marker', 'o'); 
xlabel('n (muestras)');
ylabel('Amplitud');
grid on;

%%% >>>>>>>>>>>>>>>>>> Desplazamiento <<<<<<<<<<<<<<<<<<<<<<<<<<<<
n0_atraso = 5;   % atraso de 5 muestras
n0_adelanto = -5; % adelanto de 5 muestras

x_atrasada = A * sin(2 * pi * (f/fs) * (n - n0_atraso));
x_adelantada = A * sin(2 * pi * (f/fs) * (n - n0_adelanto));

figure;
stem(n, x, 'k', 'LineWidth', 2, 'Marker', 'o'); hold on;
stem(n, x_atrasada, 'r--', 'LineWidth', 1.5, 'Marker', 'x');
stem(n, x_adelantada, 'b--', 'LineWidth', 1.5, 'Marker', 's');
xlabel('n (muestras)');
ylabel('Amplitud');
legend('Original', 'Atrasada', 'Adelantada');
grid on;

%%% >>>>>>>>>>>>>>>>>> Escalado <<<<<<<<<<<<<<<<<<<<<<<<<<<<
a = 0.5; 
x_escalado = A * sin(2 * pi * (f/fs) * (a * n));

figure;
stem(n, x, 'b', 'LineWidth', 2, 'Marker', 'o'); hold on;
stem(n, x_escalado, 'r--', 'LineWidth', 1.5, 'Marker', 's');
xlabel('n (muestras)');
ylabel('Amplitud');
legend('Original', 'Escalada (a<1)');
grid on;

%%% >>>>>>>>>>>>>>>>>> Reflexión <<<<<<<<<<<<<<<<<<<<<<<<<<<<
x_reflejado = A * sin(2 * pi * (f/fs) * (-n));

figure;
stem(n, x, 'b', 'LineWidth', 2, 'Marker', 'o'); hold on;
stem(n, x_reflejado, 'r--', 'LineWidth', 1.5, 'Marker', 'x');
xlabel('n (muestras)');
ylabel('Amplitud');
legend('Original', 'Reflejada');
grid on;

%%% >>>>>>>>>>>>>>>>>> Combinaciones <<<<<<<<<<<<<<<<<<<<<<<<<<<<
x_comb = A * sin(2 * pi * (f/fs) * (-2 * (n - 5)));
figure;
stem(n, x, 'b', 'LineWidth', 2, 'Marker', 'o'); hold on;
stem(n, x_comb, 'r--', 'LineWidth', 1.5, 'Marker', 's');
xlabel('n (muestras)');
ylabel('Amplitud');
legend('Original', 'Transformada');
grid on;