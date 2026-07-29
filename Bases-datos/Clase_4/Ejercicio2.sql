DELIMITER //
CREATE PROCEDURE obtener_iniciales_nombre()
BEGIN
  DECLARE contador INT DEFAULT 1;
  DECLARE total_registros INT;
  DECLARE nombre_completo VARCHAR(50);
  DECLARE inicial_nombre VARCHAR(10);

  SELECT COUNT(*) INTO total_registros FROM empleados;
  
  WHILE contador <= total_registros DO
    SELECT nombre INTO nombre_completo FROM empleados WHERE id = contador;
    SET inicial_nombre = SUBSTRING(nombre_completo, 1, 1);
    SET contador = contador + 1;
    SELECT inicial_nombre AS mensaje;
  END WHILE;
  
END;//
DELIMITER ;

CALL obtener_iniciales_nombre;
DROP PROCEDURE obtener_iniciales_nombre;

