clear, clc
ima1=imread('Hongo.jpg');
ima2=imread('Fondo.jpg');
ima3=imresize(ima1,0.3);
L=size(ima3);
Memoria=ima2;
for i=10:5:500
    pos_ini_x=10+i;
    pos_ini_y=420;
    pos_y=pos_ini_y:pos_ini_y+L(1)-1;
    pos_x=pos_ini_x:pos_ini_x+L(2)-1;
    Memoria(pos_y, pos_x,:)=ima3(:,:,:);
    pixel=impixel(ima2,pos_ini_x,pos_ini_y);
    if(isequal(pixel,[35,177,77]))
        break
    else
        imshow(Memoria)
        pause(0.1)
        Memoria=ima2;
    end
end
