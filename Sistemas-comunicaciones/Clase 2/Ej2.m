clear; 
clc;
close all;
syms w t;

% Definir la función
F = (exp(-2j*w)/(1j*w)) * (exp(1j*w) - 1) * exp(1j*w*t);
% integrar la función ente -10 y 10
f_t = int(F, w, -100, 100);
f_t = simplify(f_t);
disp('Resultado:');
pretty(f_t)

% Convertir a función evaluable
f_numeric = subs(f_t , t , t);

% Evaluar y graficar
t_vals = linspace(-1, 4, 500);
f_vals = subs(f_t , t , t_vals);

figure;
plot(t_vals, real(f_vals), 'b', 'LineWidth', 2);
xlabel('t');
ylabel('f(t)');
title('Transformada inversa');
grid on;
xline(1, '--r', 't = 1');
xline(2, '--r', 't = 2');

