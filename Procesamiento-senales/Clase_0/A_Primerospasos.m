%Los comentarios en el codigo de Matlab se ingresan anteponiendo el signo
%porcentaje
%%Para Limpiar el comand Window use clc
clc
%%Para borrar el Workspace use Clear all
clear all
%%Las Variables en Matlab No tienen Tipo
entera=4;
decimal=0.1;
Palabra='Hola';
Caracter='v';
%Estructuras de datos
vector=[1,2,3,4,5];
Matrices=[1,2,3;4,5,6;7,8,9];
Mezcla=['1',2,3,4]
Matriz=[2 3.4 5 6;3 4 5 6];
%Funcion que indica si la función es un arreglo.
F=isvector(vector); %1 si lo es, 0 no es arreglo.
R=class(vector); %indica que tipo de variable es.
Inicio=0;
Fin=3;
Paso=0.5;
Secuencia=Inicio:Paso:Fin;
%Cuando Se pone ; al final de la instrucción MATLAB NO muestra resultados
%en workspace
MA=[1,2;3,4];
MB=[4,5;1,2];
MC=[MA,MB];
%%%%%Extraer datos de una Matriz%%%%
A=[1 2 3; 2 3 5; 3 3 3];
B=A(1,:)%%Extrae la Fila 1
C=A(:,2)%%Extrae la Columna 2
D=[A(:,1) A(:,3)] %%Elimina Comuna 2
E=[A(2,:);A(3,:)] %%Elimina Fila 1
F=[A(2,:) A(3,:)] %%Anida en Vector Fila
G=[A(:,1);A(:,3)] %%Anida en Vector Columna
G=G'%%Matriz Transpuesta
