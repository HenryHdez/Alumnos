%>>>>>>>>>>>>TRANSFORMADA DE FOURIER<<<<<<<<<<
%Defina el conjuto de muestras
x=[0,2,2,0,1,1,0,2,2,0,1,1];
n=[0,1,2,3,4,5,6,7,8,9,10,11];
%Grafica de la funcion original
subplot(2,1,1)
stem(n,x,'linewidth',2);grid on;axis([0,12,0,2.5])
xlabel('n');ylabel('x[n]');title('Señal de prueba');
%Syms es un tipo de variable simbolica que le 
%permite definir funciones matematicas.
syms k x(k)
%la expresion 1i(uno i-latina) indica que es un número complejo
%Los puntos suspensivos indican que la instruccion continua abajo
x(k)=2*exp(-2*1i*pi*k/7)+2*exp(-2*1i*pi*k*2/7)...
     +exp(-2*1i*pi*k*4/7)+exp(-2*1i*pi*k*5/7);
%Rango de valores para k
k=-10:0.2:10;
disp(y)
%Grafica de la transformada de Fourier
subplot(2,1,2)
plot(k,x(k),'linewidth',2);grid on;axis([-10,10,-1,6.5]);
xlabel('k[Frecuencia en Hz]');ylabel('X(k)');
title('Transformada de Fuourier');