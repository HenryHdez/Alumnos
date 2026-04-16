CREATE database BIBLIOTECA;
USE BIBLIOTECA;
CREATE TABLE clientes (ID INT PRIMARY KEY,  Nombre VARCHAR(50),  Salario INT,  Departamento VARCHAR(50), Foto LONGTEXT);

INSERT INTO clientes (ID, Nombre, Salario, Departamento) VALUES 
(1, 'Juan Perez', 25000, 'Ventas'),       
(2, 'Maria Rodriguez', 60000, 'Marketing'),      
(3, 'Pedro Sanchez', 35000, 'Ventas'),       
(4, 'Laura Gomez', 40000, 'Marketing'),       
(5, 'Carlos Hernandez', 45000, 'Finanzas');