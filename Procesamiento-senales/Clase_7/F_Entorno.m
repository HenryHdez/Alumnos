clear, clc
%Importe las imágenes
ima1=imread('Hongo.jpg');
ima2=imread('Fondo.jpg');
ima3=imresize(ima1,0.3);
L=size(ima3);
%Rutina de movimiento
Memoria=ima2;
for i=10:5:580
    pos_ini_x=10+i;
    pos_ini_y=420;
    pos_y=pos_ini_y:pos_ini_y+L(1)-1;
    pos_x=pos_ini_x:pos_ini_x+L(2)-1;
    Memoria(pos_y,pos_x,:)=ima3;
    pixel=impixel(ima2,pos_ini_x,pos_ini_y);
    %Comparar dos arreglos
    if(isequal(pixel,[35,177,77]))
        break
    else
        imshow(Memoria)
        pause(0.1)
        Memoria=ima2;        
    end
end


%>>>Rotar la imagen<<<
Angulo=45; %Angulo
im_rot=imrotate(ima3,Angulo);
figure
imshowpair(ima3,im_rot,'montage')
%>>>Cortar la imágen<<<
%[Pos inicial x, y, Ancho, Alto]
im_cut=imcrop(ima2,[0,0,100,200]);
figure
imshowpair(ima2,im_cut,'montage')

