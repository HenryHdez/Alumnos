%% Demostración de la DFT de x[n] = [1 0 -1 0]

clear; clc;

% Vector en el dominio del tiempo
x = [1 0 -1 0];
N = length(x);
k = 0:N-1;

% DFT numérica con fft
X = fft(x);   % X[k]

% Candidatas de la pregunta
Xa = 1 * ones(1, N);                     % a) X[k] = 1
Xb = 2*cos(pi*k/2);                      % b) X[k] = 2 cos(pi k / 2)
Xc = 1 - exp(-1j*pi*k);                  % c) X[k] = 1 - e^{-j pi k}
Xd = 2j*sin(pi*k/2);                     % d) X[k] = 2 j sin(pi k / 2)
Xe = exp(-1j*2*pi*k) + exp(-1j*pi*k);    % e) X[k] = e^{-j2pi k} + e^{-j pi k}

disp('X[k] obtenida con fft(x):');
disp(X);

disp('Diferencia X - Xa (opción a)');
disp(X - Xa);

disp('Diferencia X - Xb (opción b)');
disp(X - Xb);

disp('Diferencia X - Xc (opción c)');
disp(X - Xc);

disp('Diferencia X - Xd (opción d)');
disp(X - Xd);

disp('Diferencia X - Xe (opción e)');
disp(X - Xe);
