clc, clear
%%%%%Variable 1%%%%%%
%Defina intervalo de temperatura
x1=0:0.1:50;
%Defina la salida 1
corte_inf=10;
corte_sup=40;
y1=smf(x1,[corte_inf, corte_sup]);
figure(1)  
plot(x1,y1,'linewidth',3); grid on;
%%%%%Variable 2%%%%%%
%Defina la sensación de calor
x2=0:0.1:4;
%Defina la salida 2
corte_inf=2;
corte_sup=3;
y2=smf(x2,[corte_inf, corte_sup]);
figure(2) 
plot(x2,y2,'linewidth',3); grid on;
%Realice el producto cartesiano
for i=1:length(y1)
    for j=1:length(y2)
        MA(i,j)=min(y1(i),y2(j));
    end
end
%Definir intervalos de la malla
[X,Y]=meshgrid(x2,x1);
%Imprimir malla
figure(3) 
mesh(X,Y,MA)
