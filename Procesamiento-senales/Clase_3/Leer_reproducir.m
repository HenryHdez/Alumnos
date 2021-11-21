%Limpiar pantalla y borrar variables
clc,clear;
Nombre_Archivo='Sonido.wav';
%Esta instruccion retorna el archivo de audio en forma de vector (y) y la
%frecuencia de muestreo (Fs) con la que fue grabado
[y, Fs]=audioread(Nombre_Archivo);
%sound reproduce el sonido
sound(y,Fs)