clear;
clc;
close all;
syms t w;

% Definir la señal por tramos
f = 1*(heaviside(t - 1) - heaviside(t - 2))   ...   % amplitud 1, 1 ≤ t < 2
  + 2*(heaviside(t - 4) - heaviside(t - 5))   ...   % amplitud 2, 4 ≤ t < 5
  + 3*(heaviside(t - 7) - heaviside(t - 9));        % amplitud 3, 7 ≤ t < 9

% Transformada de Fourier
F_w = simplify(fourier(f, t, w));
% Transformada inversa (verificación)
f_i = simplify(ifourier(F_w, w, t));

% Evaluación 
t_vals = linspace(0, 10, 1000);             % tiempo
w_vals = linspace(-30, 30, 1000);           % frecuencia

f_v  = double(subs(f,   t, t_vals));        % señal original
f_iv = double(subs(f_i, t, t_vals));        % señal reconstruida
F_v  = double(subs(abs(F_w),   w, w_vals)); % magnitud del espectro
F_ph = double(subs(angle(F_w), w, w_vals)); % fase del espectro

% Gráficas
figure;

subplot(2,2,1)
plot(t_vals, f_v, 'b', 'LineWidth', 2)
grid on
xlabel('t'), ylabel('f(t)')
title('Función original')

subplot(2,2,2)
plot(w_vals, F_v, 'r', 'LineWidth', 2)
grid on
xlabel('\omega'), ylabel('|F(\omega)|')
title('Magnitud')

subplot(2,2,3)
plot(w_vals, F_ph, 'm', 'LineWidth', 2)
grid on
xlabel('\omega'), ylabel('\angle F(\omega)')
title('Fase')

subplot(2,2,4)
plot(t_vals, f_iv, 'g', 'LineWidth', 2)
grid on
xlabel('t'), ylabel('f(t)')
title('TFI')

