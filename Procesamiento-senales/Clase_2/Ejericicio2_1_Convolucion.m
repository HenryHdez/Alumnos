%Convolucion usando MATLAB
%Definicion de las funciones a operar
%>>>>>Vector de tiempo<<<<<
n=-10:1:10;
%>>>>>Inddexación lógica<<<<<<
%Señal escalón unitario 
u=double(n>0);%Casting de lógico a número
x=(2/3).^n;
x=x.*u;
h=(2/3).^n;
h=h.*u;%Eliminacion de la parte negativa de h
y=conv(x,h,'same');
%El comando conv realiza la convolucion
%El string same le indica que el vector resultantee tiene 
%la misma dimensionalidad de x y h
stem(n,y,'linewidth',2);grid on;title('Convolucion');
axis([0,11,0,1]);xlabel('n');ylabel('x[n]')