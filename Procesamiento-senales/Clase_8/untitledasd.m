clear, clc
%Operaciones morfológicas
Ima=imread('circulos.jpg');
%Circulos rojos
Ima_R=Ima(:,:,1);
Ima_R=edge(Ima_R,'canny');
SE = strel('disk',10);
Ima_D=imdilate(Ima_R,SE);
%Rellenar estructuras
Ima_D=imfill (Ima_D,'Holes');
figure; 
imshow(Ima_D)
%Obtener esqueleto
Ima_Esq = bwmorph(Ima_D,'skel',Inf); 
figure; 
imshow(Ima_Esq)
%skel, remove, circles, bridge


%[L, Ne]=bwlabel(Ima_R);


%Estimar propiedad
%propiedad=regionprops(L,'BoundingBox'); %Ubicación

% Area, Centroid, BoundingBox, SubarrayIdx, MajorAxisLength, 
% MinorAxisLength,     Eccentricity, Orientation, ConvexHull, 
% ConvexImage, ConvexArea, Image,     FilledImage,  FilledArea, 
% EulerNumber Extrema, EquivDiameter, Solidity,     Extent, 
% PixelIdxList, PixelList, Perimeter.
%Area=regionprops(L,'Area'); %Area de cada circulo
%Perimetro=regionprops(L,'Perimeter'); %Perimetro de cada circulo

% px=10;                       %Cantidad de pixeles
% %Dilatación
% SE = strel('disk',px);       %elemento estructurante
% Im_D=imdilate(Ima_R,SE);
% figure; 
% imshowpair(Ima_R,Im_D,'montage') 
% %Erosión
% SE = strel('disk',px);       %elemento estructurante
% Im_E=imerode(Ima_R,SE);
% figure;
% imshowpair(Ima_R,Im_E,'montage') 




