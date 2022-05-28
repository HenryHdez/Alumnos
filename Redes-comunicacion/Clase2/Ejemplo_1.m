clc, clear 
n=0:1:20;
Fs=250;%Este valor cambia de acuerdo con el ejemplo 
y=3*cos(100*pi*(n/Fs));
plot(n,y,'--','linewidth',2);
hold on 
stem(n,y,'linewidth',4);
grid on 
title('Señal Discretizada');
ylabel('x[n]');
xlabel('n');