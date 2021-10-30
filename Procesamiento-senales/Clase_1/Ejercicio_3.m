clc,clear
t=-pi:0.1:pi;
valor=input('Digite un numero');
if(valor==1)
    plot(t,sin(t));
elseif(valor==2)
    plot(t,cos(t));
else
    plot(t,tan(t))
end