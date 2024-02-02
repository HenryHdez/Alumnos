#Eliminar base de datos
DROP DATABASE Ejemplo_II;
#Crear base de datos
CREATE DATABASE Ejemplo_II;
#El comando USE designa la BD como la BD de trabajo
USE Ejemplo_II;
#Crear una tabla dentro de la BD
CREATE TABLE Ejemplo_II(Valvulas INT, Seriales REAL);
#Mostrar informaciòn de los atributos de la BD
DESCRIBE Ejemplo_II;
#Agregar un registro
INSERT INTO Ejemplo_II VALUES (12, 12.4);
#Consultar Tabla o Tablas de la BD
SELECT * FROM Ejemplo_II;

#Tabla con llave primaria
CREATE TABLE Ejemplo_IIa(ID INT AUTO_INCREMENT PRIMARY KEY,
						 NOMBRES VARCHAR(30),
                         APELLIDOS VARCHAR(20));
#Actualizar registro
UPDATE Ejemplo_IIa SET ID = 14 WHERE ID=1; 

