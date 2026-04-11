clear; clc;
client = tcpclient("127.0.0.1", 4000);
disp("Conectado al servidor.");

while true

    msg = input("Escriba mensaje (exit para salir): ", "s");
    % Enviar al servidor
    writeline(client, msg);
    % Esperar respuesta del servidor
    while client.NumBytesAvailable == 0
        pause(0.1);
    end
    respuesta = readline(client);
    disp("Servidor responde: " + respuesta);
    % Condición de salida
    if msg == "exit"
        disp("Cerrando cliente...");
        break;
    end
end