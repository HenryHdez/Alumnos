clear, clc;
x=[8.9, 2, 3.4, 90, 88];            %Vector  1
y=[12, 22.5, 24, 45, 68];           %Vector  2
N=length(x);                        %Número de muestras
mem=0;                              %Acumulador temporal de la suma
puntero=1;                          %Indicador de la posición del vector
i=0;                                % Memoria  temporal de m
for m=-N+1:N-1                      %rango de muestras de x e y
    aux=circshift(x,-m);            %Funcion para la rotación del vector
     if(m<0)                        %Caso II
        i=abs(m);
        for n=N-i-1:-1:0            %Sumatoria
             mem=mem+ (aux (N-n) *y(N-n));
        end
     else                            %Caso I
        for n=N-i-1:-1:0             %sumatoria
            mem=mem + (aux(N-n)*y(N-n));
        end
    end
     r(puntero) =mem;                % Almacenamiento en un vector
     mem=0;                          %Reinicio de memoria
     puntero=puntero+1;              %aumento del puntero
end
disp(r)                              %Mostrar r
