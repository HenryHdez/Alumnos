clc, clear %Limpiar variables y pantalla
n=-5:1:5;  %Vector de muestras
%y es un vector creado de forma condicional, es decir,
%si n es mayor que -3 y menor que 1 entonces y[n]=1
y=n>-3 & n<1; 
stem(n,y,"LineWidth",2); %Presenta el gráfico discreto
%Rótulos del gráfico
xlabel("Muestra [n]");
ylabel("Amplitud");

figure %Activa una nueva ventana de gráficos
stem(n,y,"LineWidth",2);
%Fija los ejes desde -x hasta x y desde -y hasta y
axis([-5,5,0,2]); 
grid on;
xlabel("Muestra [n]");
ylabel("Amplitud");
title('Señal original'); %Titulo de la figura

figure %Gráfico 2
stem(n+3,y,"LineWidth",2);
axis([-5,5,0,2]);
grid on;
xlabel("Muestra [n]");
ylabel("Amplitud");
title('Señal en atraso');

figure %Grafico 3
stem(n-2,y,"LineWidth",2);
axis([-5,5,0,2]);
grid on;
xlabel("Muestra [n]");
ylabel("Amplitud");
title('Señal en adelanto');
