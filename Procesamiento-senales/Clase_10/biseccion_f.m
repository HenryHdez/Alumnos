function [root, fx, iter, a, b] = biseccion_f(x1, x2)
% biseccion_f   biseccion en la funcion (x^3)+(4*x^2)-10, 100 iteraciones
%   [root, fx, iter, a, b] = biseccion_f(x1, x2)
% Inputs:
%   x1, x2 - endpoints iniciales (deben satisfacer f(x1)*f(x2)<0)
% Outputs:
%   root - aproximacion de la raiz tras 100 iteraciones
%   fx   - valor de la funcion en root
%   iter - numero de iteraciones realizadas (100)
%   a,b  - extremos finales del intervalo

if nargin<2
    error('Proporcione dos extremos iniciales x1 y x2');
end

f = @(x) x.^3 + 4*x.^2 - 10;

fa = f(x1);
fb = f(x2);
if fa*fb > 0
    error('f(x1) y f(x2) deben tener signos opuestos');
end

a = x1;
b = x2;
for iter = 1:100
    c = (a + b)/2;
    fc = f(c);
    if fa*fc < 0
        b = c;
        fb = fc;
    else
        a = c;
        fa = fc;
    end
end

root = (a + b)/2;
fx = f(root);
end