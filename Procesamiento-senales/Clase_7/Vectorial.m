clear, clc
%>>>>Imágen vectorial<<<<
%Cree un entorno de dibujo
Ancho=680;
Alto=480;
Ima=zeros(Alto,Ancho);
imshow(Ima);
%Cree un rectángulo
x1=30;y1=10;x2=300;y2=100;
rectangle('Position',[x1 y1 x2 y2], ...
    'EdgeColor','k','FaceColor','c');
%Otras figuras geométricas básicas son
%>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<
%El vector de posición se compone de:
%[posicion en x,posicion en y,Ancho,Alto]
%>>>>>>>>>>>>>Circulo<<<<<<<<<<<<<<<
rectangle('Position',[200,200,50,50], ...
    'EdgeColor','k','FaceColor','m',...
    'Curvature',[1 1])
%>>>>>>>>>Rectángulo redondeado<<<<<<<<
rectangle('Position',[400,200,80,50], ...
    'EdgeColor','k','FaceColor','r',...
    'Curvature',0.3)
%>>>>>>>>>>>Línea<<<<<<<<<<<<<<<<
line([20 100],[380 420],'Color','w','LineWidth',2)
%>>>>>>>>>>>Texto<<<<<<<<<<<<<<<<
text(380,420,'Hola','Color','w')
%Guardar figura e imagen o figura
imwrite(Ima,'Nombre.jpg') %Guarda imagen
saveas(fig,'Grafico.jpg') %gcf es la figura actual