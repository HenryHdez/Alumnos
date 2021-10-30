%>Generación de una imagen de 2X2<
%>>>>>>>de 4 pixeles binaria<<<<<<
MA=[1,0;    %Línea 1
    0,1];   %Línea 2
%Filas=alto, Columnas=ancho
%Mostar imagen
imshow(MA)
%1=blanco, 0=negro

%>>>Cruz de 11X12 pixeles<<<
MA=[0,0,0,0,0,0,0,0,0,0,0,0;
    0,0,0,0,1,1,1,1,0,0,0,0;
    0,0,0,0,1,1,1,1,0,0,0,0;
    0,0,0,0,1,1,1,1,0,0,0,0;
    0,1,1,1,1,1,1,1,1,1,1,0;
    0,1,1,1,1,1,1,1,1,1,1,0;
    0,1,1,1,1,1,1,1,1,1,1,0;
    0,0,0,0,1,1,1,1,0,0,0,0;
    0,0,0,0,1,1,1,1,0,0,0,0;
    0,0,0,0,1,1,1,1,0,0,0,0;
    0,0,0,0,0,0,0,0,0,0,0,0;];
imshow(MA)
%Extraiga las dimensiones de la matriz
Dim=size(MA);
Columnas=Dim(1);
Filas=Dim(2);
%Pinte cada pixel
for i=1:Columnas
    for j=1:Filas
        Grises(i,j)=MA(i,j)*rand;
    end
end
figure
imshow(Grises)
%Genere las matrices de color
Matriz_Rojo =0.5.*MA;
Matriz_Azul =0.1.*MA;
Matriz_Verde=0.2.*MA;
%Componente Rojo
Imagen_RGB(:,:,1)=Matriz_Rojo;
%Componente Azul
Imagen_RGB(:,:,2)=Matriz_Azul;
%Componente Verde
Imagen_RGB(:,:,3)=Matriz_Verde;
imshow(Imagen_RGB)






