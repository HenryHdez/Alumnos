clear, clc
%detección de bordes
Ima=imread('Koopa.png');
%Convierta en escala de gris
Ima_gray=rgb2gray(Ima);
%Detector de bordes sobel
BW1 = edge(Ima_gray,'sobel'); 
%Detector de bordes canny
BW2 = edge(Ima_gray,'canny'); 
figure; 
imshowpair(BW1,BW2,'montage') 
title('Filtro sobel y canny')
