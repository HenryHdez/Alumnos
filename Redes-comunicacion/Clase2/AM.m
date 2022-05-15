% AM
clc, clear, close all;
t=0:0.01:2;        %Definición del intervalo
Ac=0.8;             %Amplitud portadora
fc=100;             %Frecuencia portadora
ka=1;               %Factor 
p=cos(2*fc*pi*t);   %Señal portadora
m=1*sin(3*pi*t);    %Señal a modular


s=Ac.*(1+ka.*m).*p;
%Graficar Modulación AM
plot(t,s)
grid on
title('Modulación AM')

%Transformada de Fourier
syms w t f(t) F(w)
p=cos(2*fc*pi*t);   %Señal portadora
m=1*sin(3*pi*t);    %Señal a modular
f(t)=Ac*(1+ka*m)*p;
F(w)=int(f(t)*exp(-1i*w*t),t,0,2);
w=-1500:10:1500;
%Graficar Transformada
figure
plot(w,F(w),LineWidth=2,Color='red')
grid on
xlabel('Frecuencia')
ylabel('Amplitud')
title('F(w)')
