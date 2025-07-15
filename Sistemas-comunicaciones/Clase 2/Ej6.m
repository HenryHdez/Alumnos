clc;
clear;
close all;

% ---------------------------------------
% Parámetros y señales
% ---------------------------------------
t = 0:0.001:1;  % Intervalo de tiempo (1 ms de paso)

% Señal triangular 
f_tri = 10;                             % Frecuencia de la portadora (triangular)
s = sawtooth(2*pi*f_tri*t + pi, 0.5);   % 0.5 → señal triangular (simétrica)

% Señal moduladora (mensaje)
f_mod = 1;                              % Frecuencia de modulación
m = sin(2*pi*f_mod*t);

% Longitud de señales
n = length(t);

% ---------------------------------------
% Comparador para generar PWM
% ---------------------------------------
pwm = zeros(size(t));
for i = 1:n
    if m(i) >= s(i)
        pwm(i) = 1;
    else
        pwm(i) = 0;
    end
end

% ---------------------------------------
% Graficar señal triangular
% ---------------------------------------
figure;
plot(t, s, 'b', 'LineWidth', 2);
title('Señal portadora triangular');
xlabel('Tiempo (s)');
ylabel('Amplitud');
axis([0 1 -1.5 1.5]);
grid on;

% ---------------------------------------
% Graficar señal moduladora
% ---------------------------------------
figure;
plot(t, m, 'g', 'LineWidth', 2);
title('Señal moduladora (mensaje)');
xlabel('Tiempo (s)');
ylabel('Amplitud');
axis([0 1 -1.5 1.5]);
grid on;

% ---------------------------------------
% Graficar PWM
% ---------------------------------------
figure;
plot(t, pwm, 'k', 'LineWidth', 2);
hold on;
plot(t, m, '--g', 'LineWidth', 1.2);
plot(t, s, '--b', 'LineWidth', 1.2);
title('Señal PWM generada por comparación');
xlabel('Tiempo (s)');
ylabel('Nivel PWM');
legend('PWM', 'Moduladora', 'Triangular');
axis([0 1 -1.5 1.5]);
grid on;
