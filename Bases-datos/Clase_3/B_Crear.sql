CREATE TABLE EMPLEADOS(
	emp_id INT AUTO_INCREMENT PRIMARY KEY,
    nombre VARCHAR(100),
    apellido VARCHAR(100),
    sexo VARCHAR(100),
    fecha_Nacimiento DATE NOT NULL
);

INSERT INTO EMPLEADOS(nombre, apellido, sexo, fecha_Nacimiento)
VALUES
	('Sahin','Tenar','M', DATE '1984-01-09'),
	('cali', 'Devi', 'M', DATE '1989-03-26'),
  	('Joel','Roota','F', DATE '1948-11-29'),
	('Moe', 'Alister', 'F', DATE '1959-04-16');

# Consulta de todos los registros
SELECT * FROM EMPLEADOS;
# Fijar valor del autoincremento
ALTER TABLE EMPLEADOS AUTO_INCREMENT=10;
# Insertar registro
INSERT INTO EMPLEADOS (nombre, apellido, sexo, fecha_Nacimiento) 
VALUES ('PRUEBA','PP','M', DATE '1984-01-09');
# *= campos que quiere ver
SELECT nombre FROM EMPLEADOS;
# Datos unicos del campo seleccionado
SELECT DISTINCT nombre FROM EMPLEADOS;
# Condición para filtrar los registros
SELECT * FROM EMPLEADOS WHERE sexo = 'M';
# Operadores logicos NOT, AND Y OR
# WHERE CONDICION 1 AND/OR CONDICION 2 ....
SELECT * FROM EMPLEADOS WHERE NOT sexo = 'M';
SELECT * FROM EMPLEADOS WHERE NOT sexo = 'M' AND nombre = 'Sahin';
SELECT * FROM EMPLEADOS WHERE NOT sexo = 'M' OR nombre = 'Sahin';

#Ordenar los resultados de forma ascendente o descendente ASC|DESC
SELECT * FROM EMPLEADOS ORDER BY nombre ASC;
#Limitar cantidad de registros de salida
SELECT * FROM EMPLEADOS LIMIT 3;
#Limitar en orden 
SELECT * FROM EMPLEADOS ORDER BY nombre ASC LIMIT 2;
#Consulta compuesta
SELECT * FROM EMPLEADOS WHERE emp_id>=0 ORDER BY nombre ASC LIMIT 2;
#Crear un alias para guardar un campo
SELECT nombre AS APODO FROM EMPLEADOS;
#Valor minimo o maximo MIN/MAX
SELECT MIN(nombre) FROM EMPLEADOS;
SELECT MAX(emp_id) FROM EMPLEADOS;
#Conteo, desviación estandar y/o sumatoria COUNT/AVG/SUM/
SELECT COUNT(emp_id) FROM EMPLEADOS; #WHERE emp_id=1; 
#Actualizar un registro
UPDATE EMPLEADOS SET nombre = 'JOTA' WHERE emp_id=10;
#Borrar registro(s) 
DELETE FROM EMPLEADOS WHERE emp_id=10;



