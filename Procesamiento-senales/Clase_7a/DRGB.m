clc, clear;
[X, map] = imread('peppers.png');
%X es la imágen
%map es el mapa de color
%Convertir a rgb
img = ind2rgb(X, map);
figure;
imshow(img);
title('Imagen convertida a RGB');

%Separación del canal
R = img(:,:,1);
G = img(:,:,2);
B = img(:,:,3);

figure;
subplot(2,3,1); imshow(R); title('Canal R');
subplot(2,3,2); imshow(G); title('Canal G');
subplot(2,3,3); imshow(B); title('Canal B');
subplot(2,3,4); imhist(R); title('Histograma canal Rojo');
subplot(2,3,5); imhist(G); title('Histograma canal Verde');
subplot(2,3,6); imhist(B); title('Histograma canal Azul');


img = im2double(img);

R = img(:,:,1);
G = img(:,:,2);
B = img(:,:,3);

%Mascara lógica binaria
% R > 0.45, Rojo dominante
% R > G + Umbral, Componente rojo mayor que verde
% R > B + Umbral, Componente rojo mayor que azul
Umbral = 0.0;
masc_roja = (R > 0.3) & (R > G + Umbral) & (R > B + Umbral);
%Crear mascara de rojos con valores lógicos
aplic_mas = repmat(masc_roja,[1 1 3]);

figure;
imshow(double(aplic_mas));
title('Máscara roja');

img_no_red = img;
img_no_red(aplic_mas) = 0;

figure;
subplot(1,2,1);
imshow(img);
title('Original');

subplot(1,2,2);
imshow(img_no_red);
title('Sin regiones rojas');

%Separación del canal
R = img_no_red(:,:,1);
G = img_no_red(:,:,2);
B = img_no_red(:,:,3);

figure;
subplot(2,3,1); imshow(R); title('Canal R');
subplot(2,3,2); imshow(G); title('Canal G');
subplot(2,3,3); imshow(B); title('Canal B');
subplot(2,3,4); imhist(R); title('Histograma canal Rojo');
subplot(2,3,5); imhist(G); title('Histograma canal Verde');
subplot(2,3,6); imhist(B); title('Histograma canal Azul');



%--------------------Creación de relieve------------------
% Definir la malla de trabajo (Tomar capa rojos)
% size(obj,2)=>numero col
% size(obj,2)=>numero filas
[col, filas] = meshgrid(1:size(R,2), 1:size(R,1));
% Normalizar
Z = im2double(gray);
figure;
surf(col, filas, R, img, 'EdgeColor', 'none');
xlabel('X');
ylabel('Y');
zlabel('Intensidad');
axis tight;


%Usar todos los componentes de la imagen
Z = 0.299*R + 0.587*G + 0.114*B;
[col, filas] = meshgrid(1:size(Z,2), 1:size(Z,1));
figure;
surf(col, filas, Z, img, 'EdgeColor', 'none');
xlabel('X');
ylabel('Y');
zlabel('Luminancia');
axis tight;


%Grafica scatter o gráfico de dispersión
[col, filas] = meshgrid(1:size(R,2), 1:size(R,1));
x = col(:);
y = filas(:);
z = R(:);
%Reorganiza la imagen en lista de pixeles
c = reshape(img, [], 3);

figure;
scatter3(x, y, z, 8, c, 'filled');
xlabel('X');
ylabel('Y');
zlabel('Cantidad de rojo');