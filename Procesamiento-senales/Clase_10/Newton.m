function biseccion_metodo
% Definición de la función
f = @(x) 4*x^2 - 5*x;

xi = 1;
xu = 1.6;
tolerancia = 0.001;
max_iter = 100;

% Inicialización de variables
iter = 0;
error = 1;

% Crear tabla para mostrar resultados
fprintf('it\txi\t\txu\t\tXR\t\tf(xi)\t\tf(XR)\t\tf(xi)*f(XR)\n');
fprintf('----------------------------------------------------------------\n');

while (error > tolerancia && iter < max_iter)
    % Calcular punto medio
    xr = (xi + xu)/2;
    
    % Calcular valores de función
    fxi = f(xi);
    fxr = f(xr);
    producto = fxi * fxr;
    
    % Mostrar resultados de la iteración
    fprintf('%d\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\n', ...
        iter+1, xi, xu, xr, fxi, fxr, producto);
    
    if producto < 0
        xu = xr;
    else
        xi = xr;
    end
    
    if iter > 0
        error = abs(xr - xr_ant);
    end
    xr_ant = xr;
    iter = iter + 1;
end

end