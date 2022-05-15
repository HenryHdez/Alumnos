clc, clear, close all
%Crear vector de tiempo
t=0:0.01:10;
y=double(t<0);
%Crear función portadora
for i=0:10
    y=double(t>=i & t<i+0.1)+y;
end
%Función a modular
y1=sin(t);
%Función portadora
figure
plot(t,y,LineWidth=2, Color='blue')
grid on
%Función a modular
figure
plot(t,y1,LineWidth=2, Color='blue')
grid on
%Función modulada
figure
plot(t,y.*y1,LineWidth=2, Color='blue')
grid on

