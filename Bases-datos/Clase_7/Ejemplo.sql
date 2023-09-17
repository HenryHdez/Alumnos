CREATE DATABASE EJEMPLOI;
USE EJEMPLOI;
#Mostrar directorio de trabajo
SHOW VARIABLES LIKE 'secure_file_priv';
#Mover el archivo al directorio de trabajo

SELECT 'C:/Users/usuario/Desktop/iris.csv' 
INTO OUTFILE '/var/lib/mysql-files/iris.csv';
#Crear tabbla FLORES
CREATE TABLE FLORES (ANTALL DOUBLE, LGTALL DOUBLE, 
					 ANPET DOUBLE, LGPET DOUBLE,
                     ESPECIE TEXT);
#Mover CSV a la tabla
LOAD DATA INFILE '/var/lib/mysql-files/iris.csv'
INTO TABLE EJEMPLOI.FLORES
FIELDS TERMINATED BY ','
LINES TERMINATED BY '\n'
IGNORE 1 ROWS;

SELECT * FROM EJEMPLOI.FLORES;

SELECT *
INTO OUTFILE '/var/lib/mysql-files/iris.sql'
FIELDS TERMINATED BY ','
LINES TERMINATED BY '\n'
FROM FLORES;

CREATE DATABASE EJEMPLOIa;
USE EJEMPLOIa;
