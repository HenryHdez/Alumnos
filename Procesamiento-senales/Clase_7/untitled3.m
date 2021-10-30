%Otra función de utilidad
clear, clc
ima=imread('Fondo.jpg');
imshow(ima)
%Esta función le permite capturar los puntos
%seleccionados hasta hacer clic derecho con el 
%mouse
[x,y] = getpts

