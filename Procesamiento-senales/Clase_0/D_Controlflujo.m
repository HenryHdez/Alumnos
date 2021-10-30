%%%%Estructuras Basicas de control%%
%%Condicionales
Condicion=0
if (Condicion==0)
    %%Entonces Haga Tal Cosa
else
    %%Sino Haga esta Otra
end

if(Condicion==0)
    %%Entonces cuando condicion =0 haga esto
elseif (Condicion==1)
    %%Tenga en cuenta que si condicion es = 1 hara esto
elseif (Condicion==2)
    %%Si condicion es igual a 2 hara esto
else
    %%Si condicion no es igual a ninguna de los else if hara esto
    %%Tenga en cuenta que puede colocar tantos else if como desee
end

switch(Condicion)
    case 1
        %Si condicion es igual a 1 hara esto
    case 2
        %Si condicion es igual a 2 hara esto    
    case 3
        %Si condicion es igual a 3 hara esto        
    otherwise
        %Si condicion no es igual a ningun caso hara esto            
end

%%Bucles
for i=0:100
    %Haga esto de 0 hasta 100
end

while Condicion<0
    %Mientras Condicion sea cierta haga tal cosa
end
        