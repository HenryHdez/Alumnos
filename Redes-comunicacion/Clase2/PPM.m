% PPM
clc, clear, close all;
t=0:0.001:1; %Definición del intervalo
s=sawtooth(2*pi*10*t+pi,1/2); %Definición de la señal triangular
m=1*sin(3*pi*t); %Función a modular
n=length(s); %Cantidad de elementos de s
%Comparador
for i=1:n
    if (m(i)>=s(i))
        pwm(i)=1;
    elseif (m(i)<=s(i))
        pwm(i)=0;
    end
end


%Graficar señal triangular
figure
plot(t,s,LineWidth=2, Color='blue')
grid on
title('señal a modular')
axis([0 1 -1.5 1.5]);
%Graficar función a modular
figure
plot(t,m,LineWidth=2, Color='blue')
grid on
axis([0 1 -1.5 1.5]);
title('Oscilador')
%Graficar PPM superpuesta con una PWM
figure
y2=diff(pwm);
y2=double(y2<0);
plot(t(2:end),pwm(2:end),'-g',t(2:end),y2,'--r');
grid on;
title('PWM')
axis([0 1 -1.5 1.5]);