/* 1. CREAR Y SELECCIONAR UNA BASE DE DATOS
   CREATE DATABASE Tienda;
   USE Tienda;
*/
CREATE DATABASE Tienda;
GO
USE Tienda;
GO

/* 2. IDENTIFICADOR AUTOMÁTICO
   CREATE TABLE Producto (
       id_producto INT AUTO_INCREMENT PRIMARY KEY,
       nombre VARCHAR(100)
   );
*/
CREATE TABLE Producto (
    id_producto INT IDENTITY(1,1) PRIMARY KEY,
    nombre VARCHAR(100),
    precio DECIMAL(10,2)
);
GO

/* Insertar información para realizar las consultas */
INSERT INTO Producto (nombre, precio) VALUES
    ('Computador', 2500000),
    ('Teclado', 85000),
    ('Mouse', 45000);
GO

/* 3. LIMITAR RESULTADOS
   SELECT * FROM Producto LIMIT 2;
*/
SELECT TOP 2 * FROM Producto;
GO

/* 4. FECHA Y HORA ACTUAL
   SELECT NOW();
   SQL Server utiliza GETDATE().
*/
SELECT GETDATE() AS fecha_actual;
GO


/* 5. REEMPLAZAR VALORES NULOS
   SELECT IFNULL(precio, 0)
   FROM Producto;
   SQL Server utiliza ISNULL().
*/
SELECT
    nombre,
    ISNULL(precio, 0) AS precio
FROM Producto;
GO

