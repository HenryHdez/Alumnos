/*Crear Respaldo*/
BACKUP DATABASE Universidad
TO DISK = '/var/opt/mssql/backup/Universidad.bak'
WITH
    INIT,
    NAME = 'Respaldo completo de Universidad',
    CHECKSUM,
    STATS = 10;
GO

/*Verificar el respaldo*/
RESTORE VERIFYONLY
FROM DISK = '/var/opt/mssql/backup/Universidad.bak'
WITH CHECKSUM;
GO

/*Consultar contenido de respaldo*/
RESTORE HEADERONLY
FROM DISK = '/var/opt/mssql/backup/Universidad.bak';
GO

/*Consultar archivos lógicos*/
RESTORE FILELISTONLY
FROM DISK = '/var/opt/mssql/backup/Universidad.bak';
GO

/*Restaurar*/
USE master;
GO

RESTORE DATABASE UniversidadRestaurada
FROM DISK = '/var/opt/mssql/backup/Universidad.bak'
WITH
    MOVE 'Universidad'
        TO '/var/opt/mssql/data/UniversidadRestaurada.mdf',

    MOVE 'Universidad_log'
        TO '/var/opt/mssql/data/UniversidadRestaurada_log.ldf',

    RECOVERY,
    STATS = 10;
GO