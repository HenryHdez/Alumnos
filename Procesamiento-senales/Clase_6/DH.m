% Parámetros de Denavit-Hartenberg (DH) para un brazo robótico de 3 articulaciones
% Los parámetros DH definen la cinemática de un robot según las siguientes variables:
% a     : Longitud del eslabón (distancia entre ejes z a lo largo del eje x).
% alpha : Ángulo entre los ejes z_i-1 y z_i (medido alrededor del eje x).
% d     : Desplazamiento a lo largo del eje z_i-1 (altura o distancia entre los ejes x_i-1 y x_i).
% theta : Ángulo de rotación alrededor del eje z_i-1 (posición articular).

% Definición de los parámetros DH: [a, alpha, d, theta]
DH_params = [
    0.3,  pi/2,  0.5,  0;    % Primer eslabón
    0.2,     0,    0,  pi/4; % Segundo eslabón
    0.1, -pi/2,    0,  pi/6; % Tercer eslabón
];

% Crear la tabla con 
DH_table = array2table(DH_params, ...
    'VariableNames', {'a (m)', 'alpha (rad)', 'd (m)', 'theta (rad)'}, ... % Nombres de las columnas
    'RowNames', {'Link 1', 'Link 2', 'Link 3'});                           % Nombres de las filas

% Mostrar la tabla
disp('Tabla de parámetros DH:');
disp(DH_table);

% Ejemplo de resultados interpretados:
% Link 1:
% - a = 0.3 m: El eslabón tiene una longitud de 0.3 metros.
% - alpha = pi/2 rad (90 grados): El eje z está inclinado 90° respecto al eje z anterior.
% - d = 0.5 m: Hay un desplazamiento de 0.5 metros a lo largo del eje z.
% - theta = 0 rad (0 grados): No hay rotación inicial en la articulación.

% Link 2:
% - a = 0.2 m: El eslabón tiene una longitud de 0.2 metros.
% - alpha = 0 rad (0 grados): Los ejes z están alineados sin inclinación entre ellos.
% - d = 0 m: No hay desplazamiento a lo largo del eje z.
% - theta = pi/4 rad (45 grados): La articulación tiene una rotación de 45°.

% Link 3:
% - a = 0.1 m: El eslabón tiene una longitud de 0.1 metros.
% - alpha = -pi/2 rad (-90 grados): El eje z está inclinado -90° respecto al eje z anterior.
% - d = 0 m: No hay desplazamiento a lo largo del eje z.
% - theta = pi/6 rad (30 grados): La articulación tiene una rotación de 30°.

% >>>>>>>>>>>Configuración del puerto serie<<<<<<<<<<<<
port_name = "COM3";  
baud_rate = 9600;    
serialObj = serialport(port_name, baud_rate);
message = "";
for i = 1:size(DH_params, 1)
    row = DH_params(i, :);
    message = message + sprintf("%.3f,%.3f,%.3f,%.3f\n", row(1), row(2), row(3), row(4));
end
% Enviar el mensaje por el puerto serie
write(serialObj, message, "char");
disp('Matriz DH enviada.');
% Cerrar el puerto serie
clear serialObj;


