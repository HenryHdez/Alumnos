% Parámetros de Denavit-Hartenberg (DH) iniciales
DH_params = [
    0.3,  pi/2,  0.5,  0;    % Primer eslabón
    0.2,     0,    0,  pi/4; % Segundo eslabón
    0.1, -pi/2,    0,  pi/6; % Tercer eslabón
];

% Parámetros DH finales (modificar ángulos theta para mover el brazo)
DH_params_final = [
    0.3,  pi/2,  0.5,  pi/6; % Primer eslabón
    0.2,     0,    0,  pi/2; % Segundo eslabón
    0.1, -pi/2,    0,  pi/3; % Tercer eslabón
];

% Número de pasos para la animación
n_steps = 50;

% Número de eslabones
n_links = size(DH_params, 1);

% Interpolación de los ángulos theta para cada articulación
theta_steps = zeros(n_links, n_steps); % Matriz para almacenar ángulos interpolados
for i = 1:n_links
    theta_steps(i, :) = linspace(DH_params(i, 4), DH_params_final(i, 4), n_steps);
end

% Crear la figura
figure;
hold on;
grid on;

% Configuración de la visualización
axis equal;
xlabel('X (m)');
ylabel('Y (m)');
zlabel('Z (m)');
title('Animación del manipulador robótico');
view(3);

% Dibujar el sistema de coordenadas base
quiver3(0, 0, 0, 0.1, 0, 0, 'r', 'LineWidth', 2); % Eje X (rojo)
quiver3(0, 0, 0, 0, 0.1, 0, 'g', 'LineWidth', 2); % Eje Y (verde)
quiver3(0, 0, 0, 0, 0, 0.1, 'b', 'LineWidth', 2); % Eje Z (azul)

% Inicializar las posiciones y las gráficas de las líneas
positions = zeros(3, n_links + 1);
lines = gobjects(1, n_links); % Para guardar las líneas de los eslabones

% Inicializar las líneas de los eslabones
for i = 1:n_links
    lines(i) = plot3([0, 0], [0, 0], [0, 0], 'k-', 'LineWidth', 2); % Líneas negras
end

% Animación del movimiento
for step = 1:n_steps
    % Actualizar los ángulos theta en los parámetros DH
    DH_params(:, 4) = theta_steps(:, step);

    % Calcular la transformación y actualizar las posiciones
    T_total = eye(4); % Matriz identidad
    positions(:, 1) = [0; 0; 0]; % Base

    for i = 1:n_links
        % Extraer los parámetros DH actuales
        a = DH_params(i, 1);
        alpha = DH_params(i, 2);
        d = DH_params(i, 3);
        theta = DH_params(i, 4);

        % Calcular la matriz de transformación homogénea
        A_i = [
            cos(theta), -sin(theta)*cos(alpha),  sin(theta)*sin(alpha), a*cos(theta);
            sin(theta),  cos(theta)*cos(alpha), -cos(theta)*sin(alpha), a*sin(theta);
            0,           sin(alpha),            cos(alpha),            d;
            0,           0,                     0,                     1
        ];

        % Acumular la transformación
        T_total = T_total * A_i;

        % Guardar la posición de la articulación actual
        positions(:, i + 1) = T_total(1:3, 4);
    end

    % Actualizar las líneas del brazo robótico
    for i = 1:n_links
        set(lines(i), 'XData', positions(1, i:i+1), ...
                      'YData', positions(2, i:i+1), ...
                      'ZData', positions(3, i:i+1));
    end

    % Actualizar la visualización
    drawnow;
end

hold off;
