clc, clear;          %Limpiar pantalla y borrar variables
Duracion=1;          %tiempo de grabación en segundos 
Fs=44100;            % Frecuencia de muestreo 
%Crear un objeto con propiedades de audio 
%En este caso es un microfono que se va a muestrear con Fs, una resolucion
%de 16 bits y por un solo canal.
%1 es monofónico, 2 es estéreo
Entrada=audiorecorder(Fs,16,1);
%Abrir cuadro de dialogo
msgbox("Grabando...","Titulo");
%Función para capturar el sonido 
recordblocking(Entrada,Duracion);
msgbox("Finalizo la grabacion","titulo")
%Almacenar audio en una variable
x=getaudiodata(Entrada,'int16');
%Guardar en un archivo de audio
audiowrite('Sonido.wav',x,Fs);