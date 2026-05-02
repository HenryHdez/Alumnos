%>>>>>>>>>>>>>>>>>>>>>>Histograma<<<<<<<<<<<<<<<<<<<<<
clc; clear; close all;
img = imread('cameraman.png');
figure;
imshow(img);
title('Imagen original');
figure;
imhist(img);    %Histograma                
title('Histograma de la imagen');

%>>>>>>>>>>>Aclarar, oscurecer o expandir el contraste<<<<<<<<<<<<
%img_adjust = imadjust(img);
%imadjust(img_double,rango a modificar,rango nuevo);
img_double = im2double(img); %Normalización de la imagen
img_adjust = imadjust(img_double,[0.1 0.2],[0 1]);
figure;
subplot(2,2,1);
imshow(img);
title('Original');
subplot(2,2,2);
imhist(img);
title('Histograma original');

subplot(2,2,3);
imshow(img_adjust);
title('Imagen con imadjust');
subplot(2,2,4);
imhist(img_adjust);
title('Histograma con imadjust');



%>>>>>>>>>>Equalización del histograma<<<<<<<<<<<<<<
img_eq = histeq(img);

figure;
subplot(2,2,1);
imshow(img);
title('Original');
subplot(2,2,2);
imhist(img);
title('Histograma original');

subplot(2,2,3);
imshow(img_eq);
title('Imagen con histeq');
subplot(2,2,4);
imhist(img_eq);
title('Histograma ecualizado');