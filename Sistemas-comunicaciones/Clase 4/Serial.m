clc;
clear;
close all;
%Configurar el puerto COM
puerto = serialport("COM4", 9600);   
configureTerminator(puerto, "CR");       
flush(puerto);                           
%Inicializar lo vectores
datos = [];
tiempo = [];
i = 1;
% Crear figura
fig = figure('NumberTitle', 'off', ...
             'KeyPressFcn', @(src, event) setappdata(src, 'exit', true));
grafica = plot(tiempo, datos, '-ob');
xlabel('Muestras');
ylabel('Valor recibido');
grid on;

% Inicializar condición de salida
setappdata(fig, 'exit', false);

% Bucle principal
while true
    % Verificar si se presionó 'q'
    if getappdata(fig, 'exit')
        tecla = get(fig, 'CurrentCharacter');
        if lower(tecla) == 'q'
            disp('Tecla Q presionada. Finalizando...');
            break;
        else
            % Resetear si no fue Q
            setappdata(fig, 'exit', false);
        end
    end

    % Enviar 'g' al PSoC
    writeline(puerto, 'g');     
    pause(0.1);                 

    % Leer dato si está disponible
    if puerto.NumBytesAvailable > 0
        respuesta = readline(puerto);
        valor = str2double(strtrim(respuesta));
        if ~isnan(valor)
            datos(end+1) = valor;
            tiempo(end+1) = i;
            i = i + 1;
            % Mostrar en consola
            disp(valor)  
            plot(tiempo, datos, 'ro-', 'LineWidth', 2);
            xlabel('Muestras');
            ylabel('Valor recibido');
            grid on;
            drawnow;
        end
    end
end

% Liberar el puerto
clear puerto;
close(fig);
