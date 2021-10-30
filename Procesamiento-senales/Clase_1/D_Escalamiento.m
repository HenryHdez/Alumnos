clc, clear
n=-20:1:20;
y=(n>-7&n<7).*cos(n); %Definición de la señal
Cant_Filas=3;
Cant_Columnas=1;
Graf_Activa=1;
%División de la ventana para graficar
subplot(Cant_Filas,Cant_Columnas,Graf_Activa);
stem(n,y,"linewidth",2);
axis([-20,20,0,2]);
grid on;
xlabel("Muestras [n]");
ylabel("Amplitud x[n]");
title("Señal original");

Graf_Activa=2;
subplot(Cant_Filas,Cant_Columnas,Graf_Activa);
stem(2*n,y,"linewidth",2); %Multiplica a la variable independiente
axis([-20,20,0,2]);
grid on;
xlabel("Muestras [n]");
ylabel("Amplitud x[n]");
title("División por 2");

Graf_Activa=3;
subplot(Cant_Filas,Cant_Columnas,Graf_Activa);
Fact_diezmacion=2;
MA=[n./Fact_diezmacion;y]; %Matriz temporal
MB=MA(:,1:Fact_diezmacion:end);
stem(MB(1,:),MB(2,:),"linewidth",2);
axis([-20,20,0,2]);
grid on;
xlabel("Muestras [n]");
ylabel("Amplitud x[n]");
title("Diezmación por 2");
