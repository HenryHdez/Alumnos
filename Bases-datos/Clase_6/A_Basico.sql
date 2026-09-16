-- Este es un comentario de una sola línea.

/*
Este es un comentario
de varias líneas.
*/

--GO Separa el bloque en lotes de instrucciones
CREATE DATABASE Tienda;
GO

USE Tienda;
GO

USE master;
DROP DATABASE Tienda;
GO

--Crear
CREATE TABLE Producto (
    id_producto INT IDENTITY(1,1) PRIMARY KEY,
    nombre VARCHAR(100) NOT NULL,
    precio DECIMAL(10,2) NOT NULL,
    cantidad INT NOT NULL
);
GO


--Insertar
INSERT INTO Producto (nombre, precio, cantidad) VALUES ('Computador', 2500000, 5);
GO


-- Leer
SELECT * FROM Producto;

--Actualizar
UPDATE Producto
SET precio = 90000,
    cantidad = 12
WHERE id_producto = 1;
GO

--Eliminar
DELETE FROM Producto
WHERE id_producto = 3;
GO