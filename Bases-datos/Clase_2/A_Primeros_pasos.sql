#Comentario en SQL
/*  
Comentario de múltiples lineas 
*/ 
#Crear una Base de Datos (BD)
CREATE DATABASE NOMBREBD;
#Fijar la base de datos para su uso
USE NOMBREBD;
#Borrar una BD
DROP DATABASE NOMBREBD;
#Crear una BD con el character set y collage por defecto
CREATE DATABASE NOMBREBD CHARACTER SET utf8mb4 COLLATE utf8mb4_spanish_ci;

#Crear tabla dentro de la base de datos
USE NOMBREBD;
CREATE TABLE TABLA_EJEMPLO(
	ID INT AUTO_INCREMENT PRIMARY KEY,
	NOMBRE VARCHAR(100) NOT NULL,    
    CURSO SMALLINT NOT NULL,
    GRUPO VARCHAR(2) NOT NULL,
    FECHA_INGRESO DATE DEFAULT '1000-01-01' 
    #Default: la variable debe estar en el rango 
);


SHOW TABLES;
SHOW CREATE TABLE TABLA_EJEMPLO;
SHOW COLUMNS FROM TABLA_EJEMPLO;
RENAME TABLE TABLA_EJEMPLO TO TABLA_EJEMPLO_2;
ALTER TABLE TABLA_EJEMPLO_2 ADD Otro_campo INT NOT NULL;
ALTER TABLE TABLA_EJEMPLO_2 CHANGE Otro_campo Otro_campo_2 VARCHAR(10);
ALTER TABLE TABLA_EJEMPLO_2 DROP COLUMN Otro_campo_2;
RENAME TABLE TABLA_EJEMPLO_2 TO TABLA_EJEMPLO;

SELECT * FROM TABLA_EJEMPLO

