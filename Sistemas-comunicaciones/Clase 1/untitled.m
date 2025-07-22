clc, clear;                          % Limpiar pantalla y borrar variables
Duracion = 5;                        % Tiempo de grabación en segundos
Fs = 44100;                          % Frecuencia de muestreo

% Crear un objeto con propiedades de audio
% En este caso es un micrófono que se va a muestrear, que se va a muestrear
% con Fs, una resolución de 16 bits y por un solo canal.
% 1 es monofónico, 2 es estéreo
Entrada = audiorecorder(Fs, 16, 1);

% Abrir cuadro de diálogo
msgbox("Grabando...", "Titulo");

% Función para capturar el sonido
recordblocking(Entrada, Duracion);
msgbox("Finalizó la grabación", "titulo");

% Almacenar audio en una variable
x = getaudiodata(Entrada, 'int16');

% Guardar en un archivo de audio
audiowrite('Sonido.wav', x, Fs);

% Limpiar pantalla y borrar variables
clc, clear;

Nombre_Archivo = 'Sonido.wav';

% Esta instrucción retorna el archivo de audio
% en forma de vector (y) y la frecuencia de
% muestreo (Fs) con la que fue grabado
[y, Fs] = audioread(Nombre_Archivo);
sound(y, Fs)

plot(y)
% sound reproduce el sonido
sound(y, Fs)