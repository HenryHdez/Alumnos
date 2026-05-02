%Defina el tipo de filtrado a realizar
Filtro=[ 0, -0.1, 0;
         -0.1, 0.5, -0.1;
        0,-0.1,0];
%Importe la imágen
Ima=imread('Imagenes/Koopa.png');
figure(1)
imshow(Ima)
figure(2)
%Extraiga un componente de la matriz
ImaR=Ima(:,:,1);
imshow(conv2(Filtro,ImaR))

