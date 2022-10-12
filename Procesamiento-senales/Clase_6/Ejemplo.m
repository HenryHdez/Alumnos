clc, clear
t=0:0.5:pi;
%Construya un vector de salida
x1=tan(t);
x2=sin(t);
x3=exp(t);
x4=cos(t);
Entrada=[x1,x2,x3];
%Construyra un arreglo de salida
y1=ones(1,length(x1));
y2=2.*ones(1,length(x1));
y3=3.*ones(1,length(x1));
Salida=[y1,y2,y3];
%Entrenamiento y creación de la red de base radial
red = newrb(Entrada,Salida);
%Simulación de la red
%Todas las combinaciones
y = red(x2);
plot(y)
prom=mean(y);
if(prom>0.9 && prom<1.2)
    disp("tangente")
elseif(prom>1.9 && prom<2.2)
    disp("seno")
elseif(prom>2.9 && prom<3.2)
    disp("exponencial")
else
    disp("otro")
end

