CREATE TABLE empleados (
  id INT PRIMARY KEY,
  nombre VARCHAR(50),
  salario INT,
  departamento VARCHAR(50)
);

INSERT INTO empleados (id, nombre, salario, departamento)
VALUES 
  (1, 'Juan', 5000, 'Ventas'),
  (2, 'María', 6000, 'Marketing'),
  (3, 'Pedro', 7000, 'Ventas'),
  (4, 'Ana', 5500, 'Contabilidad'),
  (5, 'Carlos', 8000, 'Marketing');
  
DELIMITER //

CREATE PROCEDURE aumentar_salario()
BEGIN
  DECLARE id_empleado INT;
  DECLARE salario_actual INT;
  DECLARE nuevo_salario INT;
  DECLARE done INT DEFAULT FALSE;
  DECLARE cur CURSOR FOR SELECT id, salario FROM empleados WHERE departamento = 'Ventas';
  
  DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;

  OPEN cur;
  
  aumentar_salario_loop: LOOP
    FETCH cur INTO id_empleado, salario_actual;
    IF done THEN
      LEAVE aumentar_salario_loop;
    END IF;

    SET nuevo_salario = salario_actual * 1.1;
    IF salario_actual > 5000 THEN
      SET nuevo_salario = nuevo_salario * 1.05;
    END IF;

    UPDATE empleados SET salario = nuevo_salario WHERE id = id_empleado;
    SELECT CONCAT('Empleado ', id_empleado, ' tiene un nuevo salario de ', nuevo_salario) AS mensaje;

  END LOOP aumentar_salario_loop;

  CLOSE cur;
END //

DELIMITER ;

call aumentar_salario;

select *from empleados;