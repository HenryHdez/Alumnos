% Definir los parámetros DH: [a, alpha, d, theta]
% Cada fila corresponde a un eslabón (Link)
DH_params = [
    0.3,  pi/2,  0.5,  0;    % Primer eslabón
    0.2,     0,    0,  pi/4; % Segundo eslabón
    0.1, -pi/2,    0,  pi/6; % Tercer eslabón
];

% Número de eslabones, calculo de la matriz total
n_links = size(DH_params, 1);
T_total = eye(4);

% Iterar por cada eslabón y calcular la matriz de transformación
for i = 1:n_links
    % Extraer los parámetros DH
    a = DH_params(i, 1);
    alpha = DH_params(i, 2);
    d = DH_params(i, 3);
    theta = DH_params(i, 4);
    % Calcular la matriz de transformación homogénea A_i
    A_i = [
        cos(theta), -sin(theta)*cos(alpha),  sin(theta)*sin(alpha), a*cos(theta);
        sin(theta),  cos(theta)*cos(alpha), -cos(theta)*sin(alpha), a*sin(theta);
        0,           sin(alpha),            cos(alpha),            d;
        0,           0,                     0,                     1
    ];
    % Multiplicar para obtener la transformación acumulada
    T_total = T_total * A_i;
end

% Mostrar la matriz de transformación total
disp('Matriz de transformación total (T_0^n):');
disp(T_total);

% Interpretación:
% La matriz T_total tiene la forma:
% [ nx,  ox,  ax,  px ]
% [ ny,  oy,  ay,  py ]
% [ nz,  oz,  az,  pz ]
% [  0,   0,   0,   1 ]
% Donde:
% - [nx, ny, nz] es la dirección del eje x del extremo del manipulador.
% - [ox, oy, oz] es la dirección del eje y del extremo.
% - [ax, ay, az] es la dirección del eje z del extremo.
% - [px, py, pz] es la posición del extremo en el espacio.
