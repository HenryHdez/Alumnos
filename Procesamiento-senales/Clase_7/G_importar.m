%>>>>Importar imagen<<<<
ima=imread('Hongo.jpg');
%Separar los componentes
%de la imágen
Comp_R=ima(:,:,1);
ima_bina_1=imbinarize(Comp_R);
Comp_G=ima(:,:,2);
ima_bina_2=imbinarize(Comp_G);
Comp_B=ima(:,:,3);
ima_bina_3=imbinarize(Comp_B);
%Presentar
subplot(2,2,1)
imshow(ima);title('Original');
subplot(2,2,2)
imshow(ima_bina_1);title('Binario 1');
subplot(2,2,3)
imshow(ima_bina_2);title('Binario 2');
subplot(2,2,4)
imshow(ima_bina_3);title('Binario 3');

%>>>>Importar imagen<<<<
ima=imread('Hongo.jpg');
%Binarizar
Comp_R=ima(:,:,1);          
ima_bina=imbinarize(Comp_R);   
%Presentar
figure 
imshowpair(ima,ima_bina,'montage')

%>>>>Importar imagen<<<<
ima=imread('Hongo.jpg');
%Binarizar          
ima_gris=rgb2gray(ima); 
Umbral=0.1;
ima_negr=imbinarize(ima_gris,Umbral);
%Presentar
figure 
imshowpair(ima,ima_negr,'montage')

%Determine el valor de color
%de un pixel
ima=imread('Hongo.jpg');
fila=12;
columna=10;
%Indicación del color de un color
impixel(ima,columna,fila)
%Visor de imagenes
imtool(ima)


