clc;
clear;
close all;

t = 0:0.01:1;           % Vector de tiempo
f = 5;                  % Frecuencia
s = sin(2 * pi * f * t);

figure;
plot(t, s); 
title('Seno'); 
xlabel('Tiempo (s)'); 
ylabel('Amplitud'); 
grid on; 

% Edición del gráfico
xlim([0 1]);                             % Limitar el eje x
ylim([-1 1]);                            % Limitar el eje y
set(gca, 'FontSize', 12);                % Cambiar el tamaño de la fuente
legend('seno', 'Location', 'northeast'); % Añadir leyenda


hold on; 
plot(t, s, 'r--', 'LineWidth', 2);
legend('seno', 'seno modificado', 'Location', 'northeast'); 
hold off; 

% Tipos de línea y colores disponibles:
% Líneas continuas: '-' (azul por defecto)
% Líneas discontinuas: '--' (rojo 'r')
% Líneas punteadas: ':' (verde 'g')
% Líneas de puntos y rayas: '-.' (negro 'k')
% Colores: 'b' (azul), 'g' (verde), 'r' (rojo), 
% 'c' (cian), 'm' (magenta), 'y' (amarillo), 'k' (negro)