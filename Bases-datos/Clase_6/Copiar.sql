#cOMENTARIO 1 LINEA
/*
vARIAS LINEAS
*/
CREATE DATABASE BASE1;
USE HENRY;

SET GLOBAL local_infile = 1;
SET GLOBAL interactive_timeout = 300;

CREATE TABLE FLORES(LGTALLO FLOAT NOT NULL, ANTALLO FLOAT NOT NULL, 
					LGPETALO FLOAT NOT NULL, ANPETALO FLOAT NOT NULL, 
                    ESPECIE VARCHAR(20) NOT NULL)
                    ENGINE = CSV;

LOAD DATA LOCAL INFILE 'C:/Users/usuario/Desktop/iris.csv' INTO TABLE flores;
CREATE DATABASE EJEMPLOI;
USE EJEMPLOI;
#Mostrar directorio de trabajo
SHOW VARIABLES LIKE 'secure_file_priv';
#Mover el archivo al directorio de trabajo
SELECT 'C:/Users/usuario/Desktop/iris.csv' 
INTO OUTFILE 'C:\\ProgramData\\MySQL\\MySQL Server 8.0\\Uploads\\iris.csv';
#Crear tabbla FLORES
CREATE TABLE FLORES (ANTALL DOUBLE, LGTALL DOUBLE, 
					 ANPET DOUBLE, LGPET TEXT,
                     ESPECIE TEXT);
#Mover CSV a la tabla
LOAD DATA INFILE 'C:\\ProgramData\\MySQL\\MySQL Server 8.0\\Uploads\\iris.csv'
INTO TABLE FLORES
FIELDS TERMINATED BY ','
LINES TERMINATED BY '\n'
IGNORE 1 ROWS;


SELECT * FROM EJEMPLOI.FLORES;

SELECT *
INTO OUTFILE '/var/lib/mysql-files/iris.sql'
FIELDS TERMINATED BY ','
LINES TERMINATED BY '\n'
FROM FLORES;
