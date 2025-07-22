% Introducción al manejo de MATLAB
% >>>>>>>>>>>>>>>>>>>0. Comandos básicos<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
clc;                            %Limpiar comand windows
clear;                          %Eliminar variables
close all;                      %Cerrar ventanas de gráficos

% >>>>>>>>>>>>>>>>>>>1. Crear variables<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
a = 5;                          % Variable escalar
b = [1, 2, 3, 4, 5];            % Vector fila
c = [1; 2; 3; 4; 5];            % Vector columna
d = [1, 2; 3, 4];               % Matriz 2x2

% Tipos de variable
e = 10.5;                       % Variable escalar (número decimal)
f = [6, 7, 8];                  % Vector fila (números enteros)
g = [9; 10; 11];                % Vector columna (números enteros)
h = [12, 13; 14, 15];           % Matriz 2x2 (números enteros)
i = true;                       % Variable escalar (booleano)
j = 'Hola';                     % Variable escalar (cadena de caracteres)
k = {1, 2; 'texto', [3, 4]};    % Celda que contiene diferentes tipos de datos

% Estructuras
persona.nombre = 'Juan';         
persona.edad = 30;               
persona.altura = 1.75;           
persona.pesos = [70, 72, 68];    

% Acceso
nombre_persona = persona.nombre; 
edad_persona = persona.edad;     
altura_persona = persona.altura; 
pesos_persona = persona.pesos;   

% Actualizar
persona.edad = 31;              






% >>>>>>>>>>>>>>>>>>>>>2. Operaciones básicas<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
suma = a + 10;              % Suma / resta
producto = a * 2;           % Producto
potencia = a^2;             % Potencia
raiz = sqrt(a);             % Raíz cuadrada
seno = sin(pi/2);           % Seno









% >>>>>>>>>>>>>>>>>>>>>3. Operaciones entre matrices<<<<<<<<<<<<<<<<<<<<<<<<<<<<
% Definir una matriz y un escalar
matriz = [1, 2; 3, 4];     
escalar = 2;                
matriz_sumada = matriz + escalar;  
matriz_producto = matriz * escalar 

% Multiplicar componente a componente
matriz2 = [5, 6; 7, 8];      
producto_componentes = matriz .* matriz2;  

% Inicialización de matrices
matriz_zeros = zeros(3, 3)    % Matriz de ceros
matriz_ones = ones(2, 4);      % Matriz de unos
matriz_identidad = eye(4);     % Matriz identidad 
matriz_aleatoria = rand(3, 2); % Matriz con valores aleatorios entre 0 y 1
% Matriz con enteros aleatorios entre 1 y 10
matriz_enteros_aleatorios = randi(10, 2, 3); 

% Ej. Aplicación
A = [2, 1, -1; 3, 2, -1; 1, 1, 1];   % Matriz de coeficientes
d = [8; 13; 3];                      % Vector de términos independientes
Ad = [A, d];
rref_Ab = rref(Ad);                  % Resolver el sistema
solucion = rref_Ab(:, end);          % Solución

% Extraer un elemento específico de una matriz
elemento_matriz = matriz(2, 1);  
% Extraer una fila completa de una matriz
fila_matriz = matriz(1, :);      
% Extraer una columna completa de una matriz
columna_matriz = matriz(:, 2);    
% Extraer un subarreglo de un vector
subarreglo_vector = b(2:4);       







% >>>>>>>>>>>>>>>>>>>>>4. Números complejos<<<<<<<<<<<<<<<<<<<<<<<<<<<<
z1 = 3 + 4i;                
z2 = 1 - 2i;                
suma_complejos = z1 + z2;
producto_complejos = z1 * z2;
% Conversión a coordenadas polares
[r, theta] = cart2pol(real(z1), imag(z2));
% Conversión de coordenadas polares a cartesianas
[x, y] = pol2cart(theta, r);