-- Crear base de datos y usarla
CREATE DATABASE IF NOT EXISTS Empresa;
USE Empresa;

-- Crear tabla de vendedores
CREATE TABLE IF NOT EXISTS Vendedores (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nombre VARCHAR(100) NOT NULL
);

-- Crear tabla de ventas
CREATE TABLE IF NOT EXISTS Ventas (
    id INT AUTO_INCREMENT PRIMARY KEY,
    id_vendedor INT,
    cantidad INT,
    fecha DATE,
    FOREIGN KEY (id_vendedor) REFERENCES Vendedores(id)
);

-- Insertar algunos vendedores
INSERT INTO Vendedores (nombre) VALUES 
('Laura Gómez'),
('Carlos Pérez'),
('Ana Martínez');

-- Insertar algunas ventas
INSERT INTO Ventas (id_vendedor, cantidad, fecha) VALUES 
(1, 40, '2024-01-10'),
(1, 30, '2024-01-15'),
(2, 60, '2024-01-12'),
(2, 45, '2024-01-20'),
(3, 110, '2024-01-10');

-- Crear procedimiento para evaluar desempeño
DELIMITER //
CREATE PROCEDURE EvaluarDesempenoVendedor(IN vendedor_id INT)
BEGIN
    DECLARE totalVentas INT;
    -- Calcular total de ventas del vendedor
    SELECT SUM(cantidad) INTO totalVentas
    FROM Ventas
    WHERE id_vendedor = vendedor_id;
    -- Evaluar desempeño según el total
    IF totalVentas > 100 THEN
        SELECT 'Excelente vendedor' AS Resultado;
    ELSEIF totalVentas BETWEEN 50 AND 100 THEN
        SELECT 'Buen desempeño' AS Resultado;
    ELSE
        SELECT 'Debe mejorar' AS Resultado;
    END IF;
END;
//
DELIMITER ;

-- llamar el procedimiento para cada vendedor
CALL EvaluarDesempenoVendedor(70); 
