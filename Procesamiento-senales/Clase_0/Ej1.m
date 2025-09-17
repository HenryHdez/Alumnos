clear; 
clc; 
close all;
syms t n
% Definir la función original en el intervalo [-pi, pi]
f = t;
% Intervalo del periodo
T = pi;

% Coeficientes a_0 
a0 = (1/2*T)*int(f, t, -T, T);
% Coeficientes a_n
an = (1/T)*int(f*cos(n*pi*t/T), t, -T, T);
% Coeficientes b_n
bn = (1/T)*int(f*sin(n*pi*t/T), t, -T, T);
% Mostrar el resultado simbólico para b_n
disp('Coeficiente b_n:');
bn = simplify(bn)

% Aproximar la función con N términos
N = 5;         % Número de armónicos
ft_approx = 0;  % como a0 y an son cero

% Sustituir el valor específico de n
for k = 1:N
    bk = subs(bn, n, k);  
    ft_approx = ft_approx + bk * sin(k*pi*t/T);
end
% Mostrar la expansión
disp(ft_approx)

% Graficar
% Vector de tiempo
t_vals = linspace(-pi, pi, 1000); 
% Función original
f_vals = t_vals;                      
% Evaluación simbólica
f_fourier = double(subs(ft_approx, t, t_vals));  

figure;
plot(t_vals, f_vals, 'k--', 'LineWidth', 1.5); hold on;
plot(t_vals, f_fourier, 'r', 'LineWidth', 2);
xlabel('t'); ylabel('f(t)');
title(['Aproximación de f(t) = t mediante ', num2str(N), ...
    ' términos de su Serie de Fourier']);
legend('f(t) original', 'Serie de Fourier');
grid on;