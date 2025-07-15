clc;
clear;
close all;

% Crear una función en MATLAB
function resultado = ejemploFuncion(entrada)
    if entrada > 0
        resultado = 'Positivo';
    elseif entrada < 0
        resultado = 'Negativo';
    else
        resultado = 'Cero';
    end
end

% Uso de While
while true
    % Entrada del usuario
    entradaUsuario = input(...
        'Por favor, ingresa un número (o escribe "salir" para terminar): ', ...
        's'); 
    % Comparar String
    if strcmp(entradaUsuario, 'salir')
        break; 
    end
    % Convertir la entrada a número
    entradaUsuario = str2double(entradaUsuario); 
    if isnan(entradaUsuario)
        disp('Entrada no válida. Por favor, ingresa un número.'); 
    else
        resultado = ejemploFuncion(entradaUsuario); 
        disp(['El número es: ', resultado]); 
    end
end

% Uso de for
for i = 1:5
    fprintf('Iteración %d: ', i);
    disp(ejemploFuncion(i - 3)); 
end