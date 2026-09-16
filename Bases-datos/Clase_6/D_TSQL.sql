/* Variables */
DECLARE @nombre VARCHAR(100);
DECLARE @nota DECIMAL(3,2);

SET @nombre = 'Ana Torres';
SET @nota = 4.50;

SELECT
    @nombre AS estudiante,
    @nota AS nota;
GO

/*Asignar datos de una tabla a una variable */
USE Universidad;
GO

DECLARE @promedio DECIMAL(3,2);

SELECT @promedio = AVG(nota) FROM Matricula;

SELECT @promedio AS promedio_general;
GO

/*Mostrar mensajes*/
DECLARE @mensaje VARCHAR(100);

SET @mensaje = 'Inicio de la consulta';

PRINT @mensaje;
GO

/*Condicionales*/
/*IF...ELSE*/
DECLARE @nota DECIMAL(3,2) = 3.80;

IF @nota >= 3.00
BEGIN
    PRINT 'El estudiante aprobó';
END
ELSE
BEGIN
    PRINT 'El estudiante reprobó';
END;
GO

/*Con información de tablas*/
IF EXISTS (
    SELECT 1
    FROM Estudiante
    WHERE correo = 'ana@universidad.edu'
)
BEGIN
    PRINT 'El estudiante ya está registrado';
END
ELSE
BEGIN
    PRINT 'El estudiante no está registrado';
END;
GO

/*Estructura CASE*/
SELECT
    id_estudiante,
    id_asignatura,
    nota,
    CASE
        WHEN nota >= 4.5 THEN 'Superior'
        WHEN nota >= 4.0 THEN 'Alto'
        WHEN nota >= 3.0 THEN 'Aprobado'
        ELSE 'Reprobado'
    END AS resultado
FROM Matricula;
GO

/*Ciclo WHILE*/
DECLARE @contador INT = 1;

WHILE @contador <= 5
BEGIN
    PRINT CONCAT('Iteración: ', @contador);

    SET @contador = @contador + 1;
END;
GO

/*TRY...CATCH*/
BEGIN TRY

    INSERT INTO Matricula (
        id_estudiante,
        id_asignatura,
        nota
    )
    VALUES (1, 1, 6.00);

END TRY
BEGIN CATCH

    SELECT
        ERROR_NUMBER() AS numero_error,
        ERROR_MESSAGE() AS mensaje_error;

END CATCH;
GO

/*Control de transacciones*/
/*Conserva*/
BEGIN TRANSACTION;

UPDATE Matricula
SET nota = 4.5
WHERE id_estudiante = 1
  AND id_asignatura = 1;

-- Nota temporalmente modificada
SELECT *
FROM Matricula
WHERE id_estudiante = 1
  AND id_asignatura = 1;

ROLLBACK TRANSACTION;

-- La nota vuelve al valor original
SELECT *
FROM Matricula
WHERE id_estudiante = 1
  AND id_asignatura = 1;
GO

/*Confirma*/
COMMIT TRANSACTION;