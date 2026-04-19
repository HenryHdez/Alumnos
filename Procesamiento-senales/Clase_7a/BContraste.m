%>>>>>>>>>>>>>>>>>>>>Ajuste de contraste<<<<<<<<<<<<<<<<<<<<<<
%La función stretchlim estima límites inferiores y superiores de intensidad
clc; clear; close all;
img = imread('cameraman.png');
limite = stretchlim(img)

% Ajustar contraste usando esos límites
img_stretch = imadjust(img, limite, []);
img_equaliz = histeq(img);

figure;
subplot(3,2,1); imshow(img); title('Original');
subplot(3,2,2); imhist(img); title('Histograma original');
subplot(3,2,3); imshow(img_stretch); title('Contraste (stretchlim)');
subplot(3,2,4); imhist(img_stretch); title('Histograma ajustado');
subplot(3,2,5); imshow(img_equaliz); title('Contraste (Ecualizado)');
subplot(3,2,6); imhist(img_equaliz); title('Histograma ajustado');


%--------------------Segmentación-----------------------------
%>>>>>>>>>>>>>>>>>>>Cuantización en niveles<<<<<<<<<<<<<<<<<<<
% Calcular 3 umbrales (para 4 niveles)
thresh = multithresh(img, 3);
% Cuantizar la imagen
img_4niveles = imquantize(img, thresh);
% Visualización
figure;
subplot(1,3,1); imshow(img); title('Original');
subplot(1,3,2); imshow(img_4niveles,[]); title('4 niveles');
subplot(1,3,3); imhist(img_4niveles); title('Histograma cuantizado');

%>>>>>>>>>>>>>>>>Segmentación con método de Otsu<<<<<<<<<<<<<<<<
% Calcular umbral óptimo
level = graythresh(img);
% Binarizar imagen
img_otsu = imbinarize(img, level);

figure;
subplot(1,3,1); imshow(img); title('Original');
subplot(1,3,2); imshow(img_otsu); title('Segmentación Otsu');
subplot(1,3,3); imhist(img_otsu); title('Histograma');