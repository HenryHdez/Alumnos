clc,clear all, close all

%Si practico mucho entonces paso el curso

%Horas de practica
x=0:0.1:8;

%Notas
y=0:0.1:5;

%Practicar Mucho
A=sigmf(x,[2,3]);

figure, plot(x,A)

%Notas
B=sigmf(y,[2.95,3]);

figure, plot(y,B)

%Realice en producto cartesiano
for i=1:length(A)
    for j=1:length(B)
        MA(i,j)=min(A(i),B(j));
    end
end

%Definir malla con los intervalos
[X,Y]=meshgrid(x,y);

%Imprimir Malla
figure,mesh(X,Y,MA')

%Realice en Condicional
for i=1:length(A)
    for j=1:length(B)

        MA(i,j)=max(1-A(i),B(j));

    end
end

%Definir malla con los intervalos
[X,Y]=meshgrid(x,y);

%Imprimir Malla
figure,mesh(X,Y,MA')