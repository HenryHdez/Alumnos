clear, clc
%Importe la imágen
Ima=imread('Koopa.png');
%Convierta en escala de gris
Ima_gray=rgb2gray(Ima);
%Agregue ruido a la imágen
densidad=0.05;
Ima_con_ruido_1=imnoise(Ima_gray,'salt & pepper',densidad);
Ima_con_ruido_2=imnoise(Ima_gray, 'gaussian');
%Agregue un filtro
Filtro = fspecial('disk',10);
%Filtro = fspecial('sobel');
Ima_Filtrada_1=imfilter(Ima_con_ruido_1,Filtro);
Ima_Filtrada_2=imfilter(Ima_con_ruido_2,Filtro);
%Presente los resultados
subplot(2,2,1)
imshow(Ima_con_ruido_1)
subplot(2,2,2)
imshow(Ima_Filtrada_1)
subplot(2,2,3)
imshow(Ima_con_ruido_2)
subplot(2,2,4)
imshow(Ima_Filtrada_2)



