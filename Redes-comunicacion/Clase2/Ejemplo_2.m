clc, clear %Limpiar variables y pantalla
%>>>>>>>>>TRANSFORMADA INVERSA DE FOURIER<<<<<<<<<<
syms w t f(t)
%int=integral(funcion, variable, limite inferior, limite superior)
f(t)=int(((exp(-2*1i*w)/(1i*w))*(exp(1i*w)-1))*exp(1i*w*t),w,-1000,1000);
%Presentación de la solución
pretty(f(t))
%Definición de los parámetros para asignar valores a la ecuación
t=0:0.1:10;
%Graficar
plot(t,f(t),LineWidth=2, Color='blue')
%Caracteristicas del gráfico
grid on %Activar la cuadricula
xlabel('tiempo')
ylabel('Amplitud')
title('f(t)')
