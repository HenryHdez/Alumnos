clc,clear
[y, Fs]=audioread('Sonido.wav');
%Recortar 
plot(y);
intervalo=3400:44000;
yl=y(intervalo);%Extraer de y 
sound(y,Fs)
%Aumentara o disminuir la frecuenci de muestreo 
sound(y,Fs/2);  %Lento
sound(y,Fs*2);  %rapido 
%Diezmación 
Factor_diezmacion=10;
Senal_diezmada=y(1:Factor_diezmacion:end);
sound(Senal_diezmada,Fs);