%Filtro de banda eliminada
clc, clear all
fsim=40000;
Rp=1;
Rs=20;
Wp=(2.*[4000 7000])/fsim;   %Frecuencias de corte
Ws=(2.*[3000 8000])/fsim;   %Frecuencias de paso
%tecnicas de diseño
[N, Wn]=buttord(Wp,Ws,Rp,Rs);
[b, a]=butter(N,Wn,'Stop');
%>>>>>>>>------------<<<<<<<
f=0:1:10000;
H=freqz(b,a,f,fsim);
%Grafica
plot(f,abs(H),'linewidth',2);
title('Filtro banda eliminada');
xlabel('Frecuencia');
ylabel('Amplitud');