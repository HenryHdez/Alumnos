clear, clc
%Importe las imágenes
ima1=imread('Imagenes/Hongo.jpg');
ima2=imread('Imagenes/Fondo.jpg');
ima3=imresize(ima1,0.3);
L=size(ima3);
%Rutina de movimiento
Memoria=ima2;
for i=10:5:1000
    %Pasar la primer columna de la imágen al final
    Memoria1=Memoria(1:end,1,:);
    Memoria2=Memoria(1:end,2:end,:);
    Memoria(1:end,end,:)=Memoria1;
    Memoria(1:end,1:end-1,:)=Memoria2;
    %Almacenar temporalmente para poner el hongo
    Temp=Memoria;
    Temp(250:249+L(1),200:199+L(2),:)=ima3;
    imshow(Temp)
    pause(0.1)
end

