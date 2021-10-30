%Defina el tipo de filtrado a realizar
Filtro=[ 1, 1, 1;
         0, 0, 0;
        -1,-1,-1];
%Importe la imágen
Ima=imread('Koopa.png');
figure(1)
imshow(Ima)
figure(2)
%Extraiga un componente de la matriz
ImaR=Ima(:,:,1);
imshow(conv2(Filtro,ImaR))

