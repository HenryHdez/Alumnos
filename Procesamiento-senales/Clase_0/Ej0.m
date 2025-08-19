clc; clear; close all;

% Definición de la señal
n = 0:40;
x = sin((pi/8)*n);

% Animación del desplazamiento
figure;
for k = 0:10
    stem(n, circshift(x, k), 'filled', 'LineWidth', 2); % desplaza en k
    xlabel('n (muestras)');
    ylabel('Amplitud');
    title(['Animación: Secuencia desplazada, k = ' num2str(k)]);
    grid on;
    axis([0 40 -1.2 1.2]);
    pause(0.5); % pausa entre cuadros
end
