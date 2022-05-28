% AM
clc, clear, close all;
N=1024;                 %Total de muestras
Fs=1200;                %Frecuencia de muestreo [Hz]
Ts=1/Fs;                %Periodo de muestreo [s]
t=(0:N-1).*Ts;          %Vector de muestras

Ac=1;                   %Amplitud portadora
fp=100;                 %Frecuencia portadora
fm=2;                   %Frecuencia señal a modular
ka=1;                   %Indice modulación 
p=cos(2*pi*fp*t);       %Señal portadora
m=sin(2*pi*fm*t);       %Señal a modular
s=Ac.*(1+ka.*m).*p;     %AM
%s=Ac.*m.*p;            %DSC-SC
%Graficar Modulación AM
plot(t,s)
grid on
title('Modulación AM')
