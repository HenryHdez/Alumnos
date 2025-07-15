clc;
clear;
close all;

% ----------------------------
% Parámetros y tiempo
% ----------------------------
t = 0:0.01:10;      % Vector de tiempo
y = zeros(size(t)); % Inicialización portadora

% ----------------------------
% Construir portadora PAM
% ----------------------------
for i = 0:10
    y = y + double(t >= i & t < i + 0.1);
end

% ----------------------------
% Señal mensaje
% ----------------------------
y1 = sin(t);  % Señal a modular

% ----------------------------
% Señal modulada (PAM por enmascaramiento)
% ----------------------------
y_modulada = y .* y1;

% ----------------------------
% Graficar portadora
% ----------------------------
figure;
plot(t, y, 'b', 'LineWidth', 2);
title('Portadora: Tren de pulsos PAM');
xlabel('Tiempo (s)');
ylabel('Amplitud');
grid on;

% ----------------------------
% Graficar señal mensaje
% ----------------------------
figure;
plot(t, y1, 'g', 'LineWidth', 2);
title('Señal mensaje: Senoidal');
xlabel('Tiempo (s)');
ylabel('Amplitud');
grid on;

% ----------------------------
% Graficar señal modulada
% ----------------------------
figure;
plot(t, y_modulada, 'r', 'LineWidth', 2);
title('Señal modulada PAM (enmascaramiento)');
xlabel('Tiempo (s)');
ylabel('Amplitud');
grid on;
