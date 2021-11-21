clc,clear 
%Leer el sonido desde la ubicacion 
[Senal,Fs]=audioread('Sonido.wav');
%Noralización de la señal entre 0 y 1 
Minimo=min(Senal);
Normalizada=Senal+abs(Minimo);
Maximo=max(Normalizada);
Normalizada=Normalizada/Maximo;
%Ampliando
Ampliada=floor(255.*Normalizada);
%Archivo plano
writematrix(Ampliada,'Sonido.txt');
%Plot
subplot(3,1,1)
plot(Senal)
title('Original')
subplot(3,1,2)
plot(Normalizada)
title('Normalizada')
subplot(3,1,3)
plot(Ampliada)
title('Ampliada')