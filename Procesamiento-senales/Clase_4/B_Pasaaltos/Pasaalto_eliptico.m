%Filtro pasa alto
clc, clear all
fsim=40000;
Rp=3;
Rs=10;
Wp=2*3000/fsim;   
Ws=2*4000/fsim;
%Eliptico
[N, Wn]=ellipord(Wp,Ws,Rp,Rs);
[b, a]=ellip(N,Rp,Rs,Wn,'High');
%>>>>>>>>------------<<<<<<<
f=0:1:10000;
H=freqz(b,a,f,fsim);
%Grafica
plot(f,abs(H),'linewidth',2);
title('Filtro pasaalto');
xlabel('Frecuencia');
ylabel('Amplitud');