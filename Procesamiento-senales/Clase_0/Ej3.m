clc; clear all;

% Definir Parámetros
t = -2:0.01:2;

% Definir Funciones
f1 = double(t < 0);
f2 = -2 * double(t >= 0);
y = f1 + f2;
cantidad_de_terminos = 30;
acumulador = 0;

%% Expansión de la sumatoria
for n = 1:cantidad_de_terminos
    an = 0;
    bn = (3 * (-1 + ((-1)^n))) / (pi * n);
    aux = an + bn * sin((pi * n / 2) * t);
    acumulador = acumulador + aux;
end

a0 = -1/2;
acumulador = a0 + acumulador;

% Graficar Funciones
hold on

% Función Aproximada
plot(t, acumulador, 'r', 'linewidth', 4);

% Función Original
plot(t, y, 'b', 'linewidth', 4);
title('Función aproximada');
xlabel('Intervalo');
ylabel('Amplitud');
grid on;
