clc;
clear;
close all;

% Parámetros de la señal
f = 10;                 % Frecuencia de la señal original (Hz)
fs = 100;               % Frecuencia de muestreo (Hz)
Ts = 1/fs;              % Período de muestreo
t = 0:1e-4:1;           % Tiempo continuo (resolución alta para graficar)
x = abs(sin(2*pi*f*t)); % Señal rectificada de onda completa

% Muestreo
n = 0:Ts:1;                    
x_muestreada = abs(sin(2*pi*f*n));

% Cuantificación (3 bits → 8 niveles)
niveles = 8;
xmin = 0;
xmax = 1;
delta = (xmax - xmin)/(niveles - 1);
niveles_vals = xmin:delta:xmax;

% Cuantificación por redondeo al nivel más cercano
[~, idx] = min(abs(x_muestreada' - niveles_vals), [], 2);
cuantificada = niveles_vals(idx);

% Codificación binaria
codigos_binarios = dec2bin(idx-1, 3);

% Gráfico
figure;
subplot(3,1,1);
plot(t, x, 'b', 'LineWidth', 1.5);
hold on;
stem(n, x_muestreada, 'r', 'filled');
title('Señal rectificada y muestreo');
xlabel('Tiempo (s)');
ylabel('Amplitud');
legend('Señal continua', 'Muestras');

subplot(3,1,2);
stem(n, cuantificada, 'k', 'filled');
title('Señal cuantificada');
xlabel('Tiempo (s)');
ylabel('Nivel cuantificado');

subplot(3,1,3);
text(n, cuantificada + 0.05, codigos_binarios, 'HorizontalAlignment', 'center');
stem(n, cuantificada, 'g', 'filled');
title('Señal codificada (binaria)');
xlabel('Tiempo (s)');
ylabel('Nivel');
ylim([0, 1.2]);

% Tabla de valores
disp('Tabla de cuantificación y codificación:');
tabla = table(n', x_muestreada', cuantificada', string(codigos_binarios), ...
              'VariableNames', {'Tiempo_s', 'Valor_Muestreado', 'Cuantificado', 'Codigo_Binario'});
disp(tabla);
