clc, clear %Limpiar variables y pantalla
%>>>>>>>>>FUNCIÓN EN EL DOMINIO DEL TIEMPO<<<<<<<<<<
t=0:0.01:5; %Crear vector con pasos de 0.01
y=double(t>=1 & t<=2); %Amplitudes definidas de forma logica
%Graficar
figure
plot(t,y,LineWidth=2,Color='red') 
%Caracteristicas del gráfico
grid on %Activar la cuadricula
xlabel('tiempo')
ylabel('Amplitud')
title('f(t)')
%>>>>>>>>>TRANSFORMADA DE FOURIER<<<<<<<<<<
syms w F(w)
F(w)=exp(-2/1i*w)*(exp(1i*w)-1);
w=-10:0.1:10;
figure
plot(w,F(w),LineWidth=2,Color='red')
%Caracteristicas del gráfico
grid on %Activar la cuadricula
xlabel('Frecuencia')
ylabel('Amplitud')
title('F(w)')

