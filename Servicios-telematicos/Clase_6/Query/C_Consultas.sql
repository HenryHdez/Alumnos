CREATE DATABASE EJEMPLO_2;
USE EJEMPLO_2;
#Inserte este registro 3 veces
INSERT INTO Tabla1 VALUES ('2015-01-31', '19:40:12', 'PROFESOR', 28);
#Todos los registros
SELECT *FROM Tabla1;
#Solo dos atributos (Antes del SELECT va el nombre del(los) atributo(s))
SELECT FECHA, USUARIO FROM Tabla1;
#Selecciona datos unicos o una sola etiqueta por registro
SELECT DISTINCT FECHA FROM Tabla1;
#Datos ordenados MENOR A MAYOR
SELECT *FROM Tabla1 ORDER BY EDAD;
#Datos ordenados MAYOR A MENOR
SELECT *FROM Tabla1 ORDER BY EDAD DESC;
#Filtrado
SELECT *FROM Tabla1 WHERE EDAD=21;
SELECT *FROM Tabla1 WHERE EDAD>=21 AND EDAD<24;
SELECT *FROM Tabla1 WHERE USUARIO<>'PROFESOR';