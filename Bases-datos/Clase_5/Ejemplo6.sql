-- Crear base de datos y seleccionarla
CREATE DATABASE IF NOT EXISTS EvaluacionVentas;
USE EvaluacionVentas;

-- Crear tabla de zonas con metas mensuales
CREATE TABLE IF NOT EXISTS Zonas (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nombre VARCHAR(50),
    meta_mensual INT
);

-- Crear tabla de vendedores asociados a una zona
CREATE TABLE IF NOT EXISTS Vendedores (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nombre VARCHAR(100),
    zona_id INT,
    FOREIGN KEY (zona_id) REFERENCES Zonas(id)
);

-- Crear tabla de ventas asociadas a cada vendedor
CREATE TABLE IF NOT EXISTS Ventas (
    id INT AUTO_INCREMENT PRIMARY KEY,
    id_vendedor INT,
    cantidad INT,
    fecha DATE,
    FOREIGN KEY (id_vendedor) REFERENCES Vendedores(id)
);

-- Insertar zonas con sus metas mensuales
INSERT INTO Zonas (nombre, meta_mensual) VALUES
('Norte', 100),
('Sur', 150),
('Centro', 120);

-- Insertar vendedores asignados a cada zona
INSERT INTO Vendedores (nombre, zona_id) VALUES
('Laura Gómez', 1),
('Carlos Pérez', 2),
('Ana Martínez', 3),
('Pedro Ramírez', 2);

-- Insertar ventas realizadas por cada vendedor
INSERT INTO Ventas (id_vendedor, cantidad, fecha) VALUES
(1, 50, '2024-04-01'),
(1, 60, '2024-04-15'),
(2, 70, '2024-04-10'),
(2, 60, '2024-04-20'),
(3, 130, '2024-04-05'),
(4, 40, '2024-04-08');

-- Crear el procedimiento para evaluar si los vendedores cumplieron la meta mensual
DELIMITER //

CREATE PROCEDURE EvaluarMetasZona(IN mes VARCHAR(7))
BEGIN
    -- Declarar variables para recorrer los datos
    DECLARE done INT DEFAULT 0;
    DECLARE nombre_vendedor VARCHAR(100);
    DECLARE nombre_zona VARCHAR(50);
    DECLARE total_ventas INT;
    DECLARE meta INT;

    -- Definir cursor para obtener nombre del vendedor, zona, meta de la zona, y total de ventas en el mes
    -- La función COALESCE(valor, valor_predeterminado) devuelve:
    -- valor si no es NULL
    -- valor_predeterminado si sí es NULL
    
    DECLARE cur CURSOR FOR
        SELECT 
            Vendedores.nombre,
            Zonas.nombre,
            Zonas.meta_mensual,
            COALESCE(SUM(Ventas.cantidad), 0) AS total
        FROM Vendedores
        JOIN Zonas ON Vendedores.zona_id = Zonas.id
        LEFT JOIN Ventas ON Ventas.id_vendedor = Vendedores.id 
             AND DATE_FORMAT(Ventas.fecha, '%Y-%m') = mes
        GROUP BY Vendedores.id;

    -- Manejador para detectar fin del cursor
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = 1;

    -- Abrir el cursor
    OPEN cur;

    -- Bucle para recorrer cada registro
    leer_loop: LOOP
        FETCH cur INTO nombre_vendedor, nombre_zona, meta, total_ventas;

        IF done THEN
            LEAVE leer_loop;
        END IF;

        -- Evaluar si el vendedor cumplió la meta
        IF total_ventas >= meta THEN
            SELECT 
                CONCAT(nombre_vendedor, ' - ', nombre_zona) AS VendedorZona,
                total_ventas AS Ventas,
                meta AS Meta,
                'Cumplió la meta' AS Resultado;
        ELSE
            SELECT 
                CONCAT(nombre_vendedor, ' - ', nombre_zona) AS VendedorZona,
                total_ventas AS Ventas,
                meta AS Meta,
                'No cumplió la meta' AS Resultado;
        END IF;
    END LOOP;

    -- Cerrar el cursor
    CLOSE cur;
END;
//

-- Restaurar el delimitador original
DELIMITER ;

-- Ejecutar el procedimiento para el mes de abril 2024
CALL EvaluarMetasZona('2024-04');
