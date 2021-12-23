clc, clear;
x=[8.9, 2, 3.4, 90, 88];          %Vector  1               
y=[12, 22.5, 24, 45, 68];         %Vector  2           
n=length (x);                     % numero de muestras
xy=x.*y;                          %x*y
S_x=sum(x);                       %sumatoria x_i
S_y=sum(y);                       %sumatoria y_i
S_x_2=sum(x.^2);                  %sumatoria x_i^2
S_y_2=sum(y.^2);                  %sumatoria y_i^2
S_xy=sum(xy);                     %sumatoria x*y
rxy=((n*S_xy)-(S_x*S_y));         %Numerador
rx=((n*S_x_2)-(S_x^2));           %Denominador 1
ry=((n*S_y_2)-(S_y^2));           %Denominador 2
r=rxy/(rx*ry);                    %Correlación (r)
disp(r)                           %Mostrar
