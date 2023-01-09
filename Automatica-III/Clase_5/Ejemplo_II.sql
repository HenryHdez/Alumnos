#Eliminar base de datos
DROP DATABASE Admin_auto_III;
#Crear base de datos
CREATE DATABASE Admin_auto_III;
#El comando USE designa la BD como la BD de trabajo
USE Admin_auto_III;
#Crear una tabla dentro de la BD
CREATE TABLE Motor(Valvulas INT, Seriales REAL);
#Mostrar informaciòn de los atributos de la BD
DESCRIBE Motor;
#Agregar un registro
INSERT INTO Motor VALUES (12, 12.4);
#Consultar Tabla o Tablas de la BD
SELECT *FROM Motor;


