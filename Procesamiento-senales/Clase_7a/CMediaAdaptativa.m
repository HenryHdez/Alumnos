%----------------Media de la imágen------------------
clc; clear; close all;
img = imread('cameraman.tif');

% Media
m1 = mean(img(:));
disp(['Media (mean): ', num2str(m1)]);
%Valor alto => Imágen clara
%Valor bajo => Imágen oscura

%Expansión del histograma
img_d = im2double(img);
Imin = min(img_d(:));
Imax = max(img_d(:));

img_expand = (img_d - Imin) / (Imax - Imin);

figure;
subplot(2,2,1); imshow(img); title('Original');
subplot(2,2,2); imhist(img); title('Histograma');
subplot(2,2,3); imshow(img_expand); title('Expansión manual');
subplot(2,2,4); imhist(img_expand); title('Histograma');