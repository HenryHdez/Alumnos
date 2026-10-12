USE Tienda;
GO

/* Genera una espera de 30 segundos */
WAITFOR DELAY '00:00:30';
GO

/*Plan de ejecución*/
USE Tienda;
GO

IF OBJECT_ID('dbo.Venta', 'U') IS NOT NULL
    DROP TABLE dbo.Venta;
GO

CREATE TABLE dbo.Venta
(
    id_venta INT IDENTITY(1,1) PRIMARY KEY,
    cliente VARCHAR(100) NOT NULL,
    producto VARCHAR(100) NOT NULL,
    cantidad INT NOT NULL,
    fecha DATE NOT NULL
);
GO

INSERT INTO dbo.Venta
    (cliente, producto, cantidad, fecha)
VALUES
    ('Ana', 'Computador', 1, '2026-09-01'),
    ('Luis', 'Teclado', 2, '2026-09-02'),
    ('Marta', 'Mouse', 3, '2026-09-03'),
    ('Ana', 'Monitor', 1, '2026-09-04'),
    ('Carlos', 'Teclado', 2, '2026-09-05');
GO