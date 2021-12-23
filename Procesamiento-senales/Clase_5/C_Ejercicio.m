x=[4,2,1,3,7];
y=[8,9,2,4,5];
covarianza=cov(x,y);               %Calcula la covarianza entre dos vectores
Desviacion=std(x);                 %Calcula la desviación estándar de x
[rxy, m]=xcorr(x,y);               %Calcula la correlación cruzada entre x e y
[rnxy,m]=xcorr(x,y,'normalized');  %Calcula la correlación normalizada entre x e y
                                   %Normalized solo esta diponible en una 
                                   %versión de MATLAB posterior a la 2020