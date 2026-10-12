/* Crear BD */

USE master;
GO

CREATE DATABASE SeguridadClase;
GO


/* Crear Tabla */

USE SeguridadClase;
GO

CREATE TABLE Estudiante (
    id_estudiante INT IDENTITY(1,1) PRIMARY KEY,
    nombre VARCHAR(100) NOT NULL,
    correo VARCHAR(120) NOT NULL UNIQUE
);
GO

INSERT INTO Estudiante (nombre, correo)
VALUES
    ('Ana Torres', 'ana@universidad.edu'),
    ('Luis Pérez', 'luis@universidad.edu'),
    ('Marta Díaz', 'marta@universidad.edu');
GO

SELECT *
FROM Estudiante;
GO


/* Nivel 1-Login: Permite entrar a la instancia de SQL Server*/

USE master;
GO

CREATE LOGIN estudiante_sql
WITH PASSWORD = 'ClaseSQL1*',
     DEFAULT_DATABASE = SeguridadClase,
     CHECK_POLICY = ON;
GO

/* Nivel 2-User: Representa al LOGIN dentro de una base de datos*/

USE SeguridadClase;
GO

CREATE USER estudiante_sql
FOR LOGIN estudiante_sql;
GO

/* Crear Rol */

USE SeguridadClase;
GO

CREATE ROLE rol_consulta;
GO

/* El rol puede consultar la tabla Estudiante */

GRANT SELECT
ON dbo.Estudiante
TO rol_consulta;
GO

/*Agregar usuario al rol*/

ALTER ROLE rol_consulta
ADD MEMBER estudiante_sql;
GO


/*Probar permisos sin cerrar la sesión*/
USE SeguridadClase;
GO

EXECUTE AS USER = 'estudiante_sql';

SELECT USER_NAME() AS usuario_actual;

SELECT *
FROM dbo.Estudiante;

REVERT;
GO

/*Probar acción no autorizada*/
USE SeguridadClase;
GO

EXECUTE AS USER = 'estudiante_sql';

BEGIN TRY

    INSERT INTO dbo.Estudiante (nombre, correo)
    VALUES ('Carlos Ruiz', 'carlos@universidad.edu');

END TRY
BEGIN CATCH

    SELECT
        ERROR_NUMBER() AS numero_error,
        ERROR_MESSAGE() AS mensaje_error;

END CATCH;

REVERT;
GO

/*Conceder permisos de inserción*/
USE SeguridadClase;
GO

GRANT INSERT
ON dbo.Estudiante
TO rol_consulta;
GO

/*Eliminar permiso de inserción*/
REVOKE INSERT
ON dbo.Estudiante
FROM rol_consulta;
GO

/*Limpieza*/
USE SeguridadClase;
GO

ALTER ROLE rol_consulta
DROP MEMBER estudiante_sql;
GO

DROP USER estudiante_sql;
GO

DROP ROLE rol_consulta;
GO

USE master;
GO

DROP LOGIN estudiante_sql;
GO

DROP DATABASE SeguridadClase;
GO