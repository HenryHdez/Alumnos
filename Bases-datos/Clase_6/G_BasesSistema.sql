/* =========================================================
   PRÁCTICA: BASES DE DATOS DEL SISTEMA EN SQL SERVER
   ========================================================= */


/* 1. MASTER
   Consultar las bases registradas en la instancia
*/

USE master;
GO

SELECT
    name AS base_de_datos,
    database_id,
    state_desc AS estado,
    recovery_model_desc AS recuperacion
FROM sys.databases
ORDER BY database_id;
GO


/* Consultar los archivos de las bases del sistema */

SELECT
    DB_NAME(database_id) AS base_de_datos,
    name AS nombre_logico,
    physical_name AS ubicacion,
    type_desc AS tipo_archivo,
    size * 8.0 / 1024 AS tamaño_mb
FROM sys.master_files
WHERE database_id <= 4
ORDER BY database_id, type_desc;
GO


/* 2. MODEL
   Consultar algunas propiedades de la base plantilla
*/

SELECT
    name,
    recovery_model_desc,
    collation_name,
    is_auto_create_stats_on,
    is_auto_update_stats_on
FROM sys.databases
WHERE name = 'model';
GO


/* 3. TEMPDB
   Crear y utilizar una tabla temporal
*/

USE tempdb;
GO

CREATE TABLE #ProductosTemporales
(
    id_producto INT PRIMARY KEY,
    nombre VARCHAR(50),
    precio DECIMAL(10,2)
);
GO

INSERT INTO #ProductosTemporales
    (id_producto, nombre, precio)
VALUES
    (1, 'Computador', 2500000),
    (2, 'Teclado', 120000),
    (3, 'Mouse', 80000);
GO

SELECT *
FROM #ProductosTemporales;
GO

/* La tabla se elimina automáticamente al cerrar la sesión */

DROP TABLE #ProductosTemporales;
GO


/* 4. MSDB
   Consultar el historial de copias de seguridad
*/

USE msdb;
GO

SELECT TOP (10)
    database_name AS base_de_datos,
    backup_start_date AS inicio,
    backup_finish_date AS finalizacion,
    CASE type
        WHEN 'D' THEN 'Copia completa'
        WHEN 'I' THEN 'Copia diferencial'
        WHEN 'L' THEN 'Copia del registro'
        ELSE 'Otro tipo'
    END AS tipo_copia
FROM dbo.backupset
ORDER BY backup_finish_date DESC;
GO


/* 5. CONSULTA FINAL
   Identificar la base actual y el servidor conectado
*/

SELECT
    @@SERVERNAME AS servidor,
    DB_NAME() AS base_actual,
    SYSTEM_USER AS usuario_conectado,
    GETDATE() AS fecha_servidor;
GO