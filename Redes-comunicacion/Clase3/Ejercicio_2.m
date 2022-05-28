%FM
clc, clear, close all;
N=1024;                 %Total de muestras
Fs=20000;               %Frecuencia de muestreo [Hz]
Ts=1/Fs;                %Periodo de muestreo [s]
t=(0:N-1).*Ts;          %Vector de muestras

Ac=1;                   %Amplitud portadora
fc=100;                 %Frecuencia portadora
fm=30;                  %Frecuencia señal a modular
m=1.5;                  %Indice modulación 
s=Ac.*cos(2*pi*fc*t+m.*sin(2*pi*fm*t));     %FM
%Graficar Modulación FM
plot(t,s)
grid on
title('Modulación FM')
hold on 
plot(t,sin(2*pi*fm*t))

