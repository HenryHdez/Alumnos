%>>>>>>>>>>>>TRANSFORMADA INVERSA DE FOURIER<<<<<<<<<<
%Vectores dados
x1=[0,2,2,0,1,1,0,2,2,0,1,1];
n1=[0,1,2,3,4,5,6,7,8,9,10,11];

% Definición de parámetros
N = 7;                  % Longitud fundamental
n = 0:N-1;              % Índices de tiempo
k = 0:10;               % Índices de frecuencia

% Definición de X[k]
Xk = zeros(1, N);
for kk = 1:N
    k_val = k(kk);
    Xk(kk) = 2*exp(-1j*2*pi*k_val*1/N) ...
           + 2*exp(-1j*2*pi*k_val*2/N) ...
           +   exp(-1j*2*pi*k_val*4/N) ...
           +   exp(-1j*2*pi*k_val*5/N);
end
disp(Xk)
% Cálculo de la IDFT
xn = zeros(1, N);
for nn = 1:N
    for kk = 1:N
        xn(nn) = xn(nn) + (1/N) * Xk(kk) * exp(1j*2*pi*(nn-1)*(kk-1)/N);
    end
end

% Graficar resultados
figure
subplot(2,1,1);
stem(n1(1:7), x1(1:7),'filled','LineWidth',1.5); grid on;
xlabel('n'); ylabel('x[n]');
title('Datos originales');

subplot(2,1,2);
stem(n, real(xn),'filled','LineWidth',1.5); grid on;
xlabel('n'); ylabel('x[n]');
title('Señal reconstruida');

