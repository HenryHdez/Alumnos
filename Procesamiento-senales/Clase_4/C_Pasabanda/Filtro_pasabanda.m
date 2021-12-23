%Filtro pasabandanda
clc, clear all
fsim=40000;
Rp=1;
Rs=20;
Wp=(2.*[4000 7000])/fsim;   %Frecuencias de paso
Ws=(2.*[3000 8000])/fsim;   %Frecuencias de corte
%tecnicas de diseño
[N, Wn]=buttord(Wp,Ws,Rp,Rs);
[b, a]=butter(N,Wn);
%>>>>>>>>------------<<<<<<<
f=0:1:10000;
H=freqz(b,a,f,fsim);
%Grafica
plot(f,abs(H),'linewidth',2);
title('Filtro pasabanda');
xlabel('Frecuencia');
ylabel('Amplitud');