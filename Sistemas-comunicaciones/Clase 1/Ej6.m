clc; 
clear;
close all;

N = 50;

t = linspace(-pi, pi, 1000);
%Acumula todos los valores de la serie evaluado en todos los puntos de t
f_fourier = zeros(size(t));

% Construir la suma de la serie exponencial
% (omitiendo n=0 por división por cero)
for n = -N:N
    if n ~= 0
        % Coeficiente complejo de Fourier
        Cn = (-1)^n / (-1j * n);  
        % Suma de serie
        f_fourier = f_fourier + Cn * exp(1j * n * t);  
    end
end

% Función original
f_original = t;

% Graficar la reconstrucción y la señal original
figure;
plot(t, real(f_fourier), 'r', 'LineWidth', 2); hold on;
plot(t, f_original, 'k--', 'LineWidth', 1.5);
xlabel('t'); ylabel('f(t)');
title(['Reconstrucción de f(t) = t con ', num2str(2*N), ...
    ' términos de Fourier exponencial']);
legend('Serie de Fourier (parte real)', 'f(t) = t');
grid on;
