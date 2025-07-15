clc; clear; close all;

%% Parámetros de la señal
T = 1;                                  % Duración total (segundos)
fs = 50;                                % Frecuencia de muestreo
t = 0:1/fs:T;                           % Vector de tiempo

% Señal triangular
f_tri = 5;                                    % Frecuencia
x = 0.5 * sawtooth(2*pi*f_tri*t, 0.5) + 0.5;  % Escalar y trasladar

% Cuantificación
N = 3;                                % Bits de cuantificación
niveles = 2^N;                        % Número de niveles
% Rango de la señal
xmin = min(x); xmax = max(x); 
% Paso de cuantificación
delta = (xmax - xmin) / (niveles-1); 

% Índice del nivel más cercano
x_q = round((x - xmin) / delta); 
% Asegurar rango válido
x_q = min(max(x_q, 0), niveles-1);    
% Valor cuantificado real
xq_val = xmin + x_q * delta;          

% Codificación binaria
codigos_bin = dec2bin(x_q, N);        

% Mostrar los primeros valores
disp(" t(s)   Señal     Cuantificada     Código Binario");
for i = 1:10
    fprintf("%5.3f   %6.3f     %6.3f        %s\n",...
        t(i), x(i), xq_val(i), codigos_bin(i,:));
end

% Graficar
figure;
subplot(2,1,1)
plot(t, x, 'b', 'LineWidth', 1.5); hold on;
stem(t, xq_val, 'r','filled');
title('Cuantificación');
xlabel('Tiempo (s)');
ylabel('Amplitud');
legend('Original','Cuantificada');
grid on;

subplot(2,1,2)
stairs(t, bin2dec(codigos_bin), 'k','LineWidth',1.5);
title('Codificación digital');
xlabel('Tiempo (s)');
ylabel('Nivel codificado');
grid on;
