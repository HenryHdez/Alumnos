clc; %Limpiar Pantalla
clear all; %Eliminar Variables del WorkSpace
%%Operaciones Básicas en MATLAB
%%Suma
Resultado=entera+decimal;
%%Resta
Resultado=entera-decimal;
%%Multiplicacion
Resultado=entera*decimal;
%%Division
Resultado=entera/decimal;
%%Para mostrar en el comand Window use el comando disp
disp(Resultado)
%%Operaciones entre Matrices
%%Definimos Dos Matrices
A=[2 1;3 2]
B=[1 4;-1 5]
%%Suma
C=A+B
%%Resta
C=A-B
%%Multiplicación Matrices
C=A*B
%%División (Caso particular de multiplicacion de matrices)
C=A/B
%%Multiplicacion Componente a Componente
C=A.*B
%%Division componente a componente
C=A./B
%%Tamaño de un arreglo 
size(C)
%%Generar Matriz identidad
D=eye(3)
%%Generar Arreglo de unos
D=ones(2,3)
%%Generar Arreglo de Ceros
D=zeros(2,3)
%%Resolver un sistema de ecuaciones lineales usando Gauss Jordan
A=[2 3 4 3;4 5 6 3; 9 3 0 2];
D=rref(A)
syms a b c; %Definir variable Simbolica
syms f(t) s(x,y) M(j,i); %Definir funciones de cuantos nesecite argumentos
%Ejemplos de Aplicación
%%Definir la formula
f(t) = t^2;
%%Evaluando la Función
disp(f(5));
%%Ahora con mas de una variable
s(x,y)=x+y;
%%Evaluando la función
disp(s(2,3));
%%Las funciones pueden ser expresadas en arreglos matriciales o vectoriales
M(j,i)=[i,j^2;j*i,i+j];
%%Mostrar Matriz
disp(M(3,2))
%%Otra forma de evaluar la función
S = (a^2-a*b-a*c+b^2-b*c+c^2)^(1/2);
%%Una forma de simplificar un polinomio
S=simplify(S);
disp(S)
%%Una forma de mostrar la ecuación de una manera agradable
pretty(1/S);
%%Ahora una forma de solucionar polinomios usando el comando solve
syms q
f=q^2-q+6;
solve(f) %%Solve obtiene las raices del polinomio 
%%Para realizar una integral Indefinida se usa la siguiente estructura
syms f(x);
f(x)=x^2;
rta=int(f,x);
pretty(rta)
%%Para una función de mas de una variable
syms f(x,y,z);
f(x)=x^2+y,z^3;
rta=int(f,z);
pretty(rta)
%%Si es una integral doble, triple o la que sea, sugiero ingresarla de la siguiente forma
syms f(x,y,z);
f(x)=x^2+y,z^3;
rta=int(int(f,z),y); %Se resolvera primeramente la integral mas interna y luego la externa
pretty(rta)
%%Si es una integral definida hagalo de la siguiente forma
syms f(x,y,z);
f(x)=x^2+y,z^3;
lo=0;%%Limite inferior
lh=10;%%Limite Superior
rta=int(f,z,lo,lh);
pretty(rta)
%%Los limites de la integral definida también pueden ser variables
%%simbolicas
syms f(x,y,z) lo lh;
f(x)=x^2+y,z^3;
rta=int(f,z,lo,lh);
pretty(rta)
%%Para derivar una función se sigue la estructura mostrada a continuación
syms f(x);
f(x)=x^2;
rta=diff(f,x);
pretty(rta)
%%Para derivar una función de mas de dos variables 
syms f(x,y,z);
f(x)=x^2+y,z^3;
rta=diff(f,x);%Donde el segundo termino es el cual voy a derivar
pretty(rta)
%%Para derivar con respecto a una coordenada seria
syms f(x,y,z);
f(x)=x^2+y,z^3;
c=0;%%Limite inferior
rta=int(f,z,c);
pretty(rta)