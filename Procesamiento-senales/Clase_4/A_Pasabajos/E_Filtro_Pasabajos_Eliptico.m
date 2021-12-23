%Filtro pasabajos
clc, clear
fsim=40000;
Rp=3;               
Rs=10;              
Wp=2*3000/fsim;     
Ws=2*4000/fsim;     
%Técnica de diseño
[N, Wn]=ellipord(Wp,Ws,Rp,Rs);
[b, a]=ellip(N,Rp,Rs,Wn);
%Intervalo de pruebas
f=0:1:10000;       
H=freqz(b,a,f,fsim);
%Grafica
plot(f,abs(H),'linewidth',2);
title('Filtro pasabajos');
xlabel('Frecuencia');
ylabel('Amplitud');