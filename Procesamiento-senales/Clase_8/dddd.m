I = [ 2 1 0 1 2;
      1 3 2 3 1;
      0 1 4 1 0;
      1 2 1 2 1;
      2 1 0 1 2 ];

H = [ 0  1  0;
      1 -4  1;
      0  1  0 ];

% Convolución válida (solo zona interior 3x3)
C_valid = conv2(I, H, 'same');

% Matriz de salida con el mismo tamaño que I
C = I;                          % copiar bordes
C(2:end-1, 2:end-1) = C_valid;  % reemplazar solo interior

disp(C);


disp('=== PREGUNTA 1: Resultado de la convolución 2D (C) ===');
disp(C);

% Si quieres verificar manualmente algún elemento:
% Por ejemplo, el elemento central C(3,3):
fprintf('Elemento central C(3,3) = %d\n\n', C(3,3));


%% ===================== PREGUNTA 2 =========================
% DFT de x[n] = [1, 0, -1, 0] y expresión de X[k]

x = [1 0 -1 0];
N = length(x);
k = 0:N-1;

% DFT numérica
X_num = fft(x);               % X[k] numérico

% Expresión teórica: X[k] = 1 - e^{-j*pi*k}
X_teo = 1 - exp(-1j*pi*k);    % Forma cerrada en términos de k

disp('=== PREGUNTA 2: DFT de x[n] = [1 0 -1 0] ===');
disp('X_num (fft(x)) =');
disp(X_num);
disp('X_teo (1 - exp(-j*pi*k)) =');
disp(X_teo);

% Verificación de igualdad numérica
disp('¿Coinciden X_num y X_teo (diferencia numérica)?');
disp(X_num - X_teo);
fprintf('\n');


%% ===================== PREGUNTA 3 =========================
% Función correcta para leer una imagen: imread

% Ejemplo (usa un archivo de prueba en la misma carpeta)
nombre_imagen = 'prueba.png';   % Cambia por el nombre real de tu archivo

try
    Iimg = imread(nombre_imagen);  % Función correcta para leer la imagen
    disp('=== PREGUNTA 3: Lectura de imagen con imread ===');
    fprintf('Imagen "%s" leída correctamente con imread.\n', nombre_imagen);
    disp('Tamaño de la imagen:');
    disp(size(Iimg));
catch ME
    disp('=== PREGUNTA 3: Lectura de imagen con imread ===');
    fprintf('No se pudo leer la imagen "%s". Verifique que exista en la carpeta.\n', nombre_imagen);
    disp(ME.message);
end

% Comentario:
% La función correcta para leer una imagen desde archivo en MATLAB es imread.
% Otras funciones como imshow, imagesc, etc., se usan para visualizar, no para leer el archivo.
