CREATE TABLE Empleados (ID INT PRIMARY KEY,  Nombre VARCHAR(50),  Salario INT,  Departamento VARCHAR(50), Foto LONGTEXT);

INSERT INTO Empleados (ID, Nombre, Salario, Departamento) VALUES 
(1, 'Juan Perez', 25000, 'Ventas'),       
(2, 'Maria Rodriguez', 60000, 'Marketing'),      
(3, 'Pedro Sanchez', 35000, 'Ventas'),       
(4, 'Laura Gomez', 40000, 'Marketing'),       
(5, 'Carlos Hernandez', 45000, 'Finanzas');

START TRANSACTION;	
	SELECT Salario FROM Empleados WHERE ID = 2 FOR UPDATE;	
	UPDATE Empleados SET Salario = 120000 WHERE ID = 2;
COMMIT;

START TRANSACTION;
	SELECT Salario FROM Empleados WHERE ID = 2 FOR UPDATE;
	UPDATE Empleados SET Salario = 60000 WHERE ID = 2;
ROLLBACK; #Deshacer los cambios

SELECT Foto FROM empleados WHERE id = 1
