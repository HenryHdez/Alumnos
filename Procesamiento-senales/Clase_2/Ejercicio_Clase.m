%>>>>>>>>>>>>TRANSFORMADA DE FOURIER<<<<<<<<<<
%Defina el conjuto de muestras
x=[0,2,2,0,1,1,0,2,2,0,1,1];
n=[0,1,2,3,4,5,6,7,8,9,10,11];
%Calculo de x(k) de forma manual
N = 7;
x(k)=2*exp(-2*1i*pi*k/7)+2*exp(-2*1i*pi*k*2/7)...
     +exp(-2*1i*pi*k*4/7)+exp(-2*1i*pi*k*5/7);
%Rango de valores para k
k=-10:0.2:10;

% Inicialización del vector de la señal en el tiempo
xn = zeros(1, N);
% Cálculo de la transformada inversa
for n = 0:N-1
    for k = 0:N-1
        xn(n+1) = xn(n+1) + (1/N) * Xk(k+1) * exp(1i*2*pi*n*k/N);
    end
end
% Visualización de la señal en el tiempo
n = 0:N-1; % Vector de tiempo/discreto
stem(n, real(xn), 'linewidth', 2); % Se grafica la parte real de la señal
grid on;
axis([0 N-1 min(real(xn)) max(real(xn))]);
xlabel('n');
ylabel('x[n]');
title('Señal en el dominio del tiempo');


