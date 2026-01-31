clc,clear
adaptador=imaqhwinfo('winvideo',1);
Video=videoinput('winvideo',1);
preview(Video)
i=0;
while i==0
    imagen=getsnapshot(Video);
    Ima_gray=rgb2gray(imagen);
    %Detector de bordes sobel
    BW1 = edge(Ima_gray,'sobel'); 
    imshow(BW1)
    pause(0.1)
end