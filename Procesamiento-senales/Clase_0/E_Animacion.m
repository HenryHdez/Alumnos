%%%CREAR UNA ANIMACIÓN
clc, clear 
%%Crear un vector de tiempo
x=-2:0.01:2;
for i=1:length(x)
    %% La i Cumple la funcion de puntero en el vector, es decir en cada 
    %% iteración el vector crece un posición
    muestras(i)=x(i);
    %%%Reemplazar en la función para cada instante tiempo 
    f(i)=(1-(abs(x(i))-1).^(2)).^(1/2);
    g(i)=acos(1-abs(x(i)))-(pi);
    plot(muestras,f,'*r',muestras,g,'og')
    pause(0.001);
    drawnow;
end

