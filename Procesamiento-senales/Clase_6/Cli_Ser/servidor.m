%En el CDM, poner la ruta donde se encuentran los scripts
%D:\GiHub\Alumnos\Procesamiento-senales\Clase_6\Cli_Ser
%Ejecute (dos veces) matlab -nodesktop -nosplash
%Luego escriba el nombre del script

clear; clc;


server = tcpserver("127.0.0.1", 4000);
disp("Servidor iniciado. Esperando cliente...");
% Esperar conexión
while ~server.Connected
    pause(0.1);
end
disp("Cliente conectado.");

% Bucle de recepción
while true
    % Esperar datos
    if server.NumBytesAvailable > 0
        % Leer línea de texto
        msg = readline(server);
        disp("Cliente dice: " + msg);
        writeline(server, "Recibido: " + msg);
        if msg == "exit"
            disp("Cerrando servidor...");
            break;
        end
    end
    pause(0.1);
end