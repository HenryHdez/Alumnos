%Diseño de un filtro pasabajos
%Borra el Command Window y variables del espacio de trabajo.
clc, clear all
%caracteristicas del diseño
fsim=40000;
Rp=3;               %Rizado banda de paso
Rs=10;              %Rizado banda atenuda
Wp=2*3000/fsim;     %Frecuenci inicial
Ws=2*4000/fsim;     %Frecuencia de la banda atenuada
%Diseño por Butterworth
%Calculo de los coeficietes de la función de transferencia 
[N, Wn]=buttord(Wp,Ws,Rp,Rs);
[b, a]=butter(N,Wn);
%El comando tf presenta la funcio de transferencia
Tiempo_muestreo_ejemplo=0.1;
tf(b,a, Tiempo_muestreo_ejemplo,'variable','z^-1')
%Establezca un rango de simulacion para conocer el 
%comportamiento del filtro
%Frecuencia en Hertz 
f0=0;                %Inicial
paso=1;             %Paso
ff=10000;           %Final
f=f0:paso:ff;       %Intervalo de prueba 
%Estimar la respuesta del filtro 
H=freqz(b,a,f,fsim);
%Graficar 
plot(f,abs(H),'linewidth',2);
title('Filtro pasabajos');
xlabel('Frecuencia');
ylabel('Amplitud');