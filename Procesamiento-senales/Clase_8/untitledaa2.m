clc, clear
%MATLAB DE WEB
%webcamlist: obtiene información del adaptador de video disponible 
Adaptador=webcamlist
% MATLAB retorna la cantidad de dispositivos disponibles
% En micaso solo hay uno y es 'Integrated Camera'
Camara=webcam('Integrated Camera');
%Establezca el formato
%Presente en una ventana
preview(Camara);
%Con snaptshot obtiene una imagen
imagen=snapshot(Camara);
imshow(imagen)
%El procesamiento se realiza como se mostró anteriormente.
