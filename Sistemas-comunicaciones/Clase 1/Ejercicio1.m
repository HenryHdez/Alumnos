clc; clear; close all;

% --------------------------
% Parámetros ajustables por el usuario
% --------------------------
f = 2;                      % Frecuencia de la señal (Hz)
fs = 100;                   % Frecuencia de muestreo (Hz)
T = 2;                      % Duración total de la señal (segundos)
velocidad = 5;              % Velocidad del retardo (cuadros por segundo)
direccion = 'derecha';      % Opciones: 'derecha' o 'izquierda'
amplitud = 1;               % Amplitud de la señal
n_frames = 40;              % Número de cuadros en la animación

% --------------------------
% Construcción del tiempo y señal original
% --------------------------
t = 0:1/fs:T;
x = amplitud * sin(2*pi*f*t);

% --------------------------
% Configuración de la figura
% --------------------------
figure;
set(gcf, 'Color', 'w');
axis tight manual
ylim([-1.2*amplitud, 1.2*amplitud]);
xlabel('Tiempo (s)');
ylabel('Amplitud');
title('Propagación de una señal senoidal con retardo');

% --------------------------
% Animación del desplazamiento
% --------------------------
for k = 1:n_frames
    % Cantidad de retardo o adelanto por cuadro
    delay = (k-1)*velocidad/fs;

    % Desplazamiento según dirección
    if strcmpi(direccion, 'derecha')
        t_shift = t - delay;
    else
        t_shift = t + delay;
    end

    % Recalcular la señal desplazada
    x_shifted = amplitud * sin(2*pi*f*t_shift);

    % Graficar
    plot(t, x_shifted, 'b', 'LineWidth', 2);
    grid on;
    axis([0 max(t) -1.2*amplitud 1.2*amplitud]);
    title(['Desplazamiento de la señal, cuadro #' num2str(k)]);
    pause(0.05);  % Controla la velocidad de la animación
end
