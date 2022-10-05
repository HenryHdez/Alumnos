#Comentario de una sola lìnea
/*Comentario en SQL 
de varias lìneas*/
#Crear una Base de Datos (BD)
CREATE DATABASE EJEMPLO_1;
#El comando USE designa la BD como la BD de trabajo
USE EJEMPLO_1;
#Crear una tabla dentro de la BD
CREATE TABLE Tabla1(SENSOR_1 INT, SENSOR_2 REAL);
#Mostrar informaciòn de los atributos de la BD
DESCRIBE Tabla1;
#Agregar un registro
INSERT INTO Tabla1 VALUES (12, 12.4);
#Consultar Tabla o Tablas de la BD
SELECT *FROM Tabla1;
#Eliminar Tabla
DROP TABLE Tabla1;


