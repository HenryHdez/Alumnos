clc, clear %Limpiar variables y pantalla
n=-5:1:5;  %Vector de muestras
%y es un vector creado de forma condicional, es decir,
%si n es mayor que -3 y menor que 1 entonces y[n]=1
y=n>-3 & n<1; 
stem(n,y,"LineWidth",2); %Presenta el gráfico discreto
axis([-5,5,0,2]); 
grid on;
%Rótulos del gráfico
xlabel("Muestra [n]");
ylabel("Amplitud");

figure %Activa una nueva ventana de gráficos
stem(-n,y,"LineWidth",2);
%Fija los ejes desde -x hasta x y desde -y hasta y
axis([-5,5,0,2]); 
grid on;
xlabel("Muestra [n]");
ylabel("Amplitud");
title('Señal Invertida'); %Titulo de la figura

