clc, clear
t=0:0.01:10;
y=double(t>=1 & t<=2)+2*(t>=4 & t<=4.5)+3*(t>=7 & t<=9)
%Graficar
figure
plot(t,y,LineWidth=2, Color='blue')
%Caracteristicas del gráfico
grid on %Activar la cuadricula
xlabel('tiempo')
ylabel('Amplitud')
title('f(t)')