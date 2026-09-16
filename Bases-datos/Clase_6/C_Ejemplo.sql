CREATE DATABASE Universidad;
GO

USE Universidad;
GO

/* Primera tabla principal */

CREATE TABLE Estudiante (
    id_estudiante INT IDENTITY(1,1),
    nombre VARCHAR(100) NOT NULL,
    correo VARCHAR(120) NOT NULL,

    CONSTRAINT PK_Estudiante
        PRIMARY KEY (id_estudiante),

    CONSTRAINT UQ_Estudiante_Correo
        UNIQUE (correo)
);
GO


/* Segunda tabla principal */

CREATE TABLE Asignatura (
    id_asignatura INT IDENTITY(1,1),
    nombre VARCHAR(100) NOT NULL,
    creditos INT NOT NULL,

    CONSTRAINT PK_Asignatura
        PRIMARY KEY (id_asignatura)
);
GO


/* Tabla de unión */

CREATE TABLE Matricula (
    id_estudiante INT NOT NULL,
    id_asignatura INT NOT NULL,
    fecha DATE NOT NULL DEFAULT GETDATE(),
    nota DECIMAL(3,2),

    CONSTRAINT PK_Matricula
        PRIMARY KEY (id_estudiante, id_asignatura),

    CONSTRAINT FK_Matricula_Estudiante
        FOREIGN KEY (id_estudiante)
        REFERENCES Estudiante(id_estudiante),

    CONSTRAINT FK_Matricula_Asignatura
        FOREIGN KEY (id_asignatura)
        REFERENCES Asignatura(id_asignatura),

    CONSTRAINT CK_Matricula_Nota
        CHECK (nota BETWEEN 0 AND 5)
);
GO

/* Agregar registros */

INSERT INTO Estudiante (nombre, correo)
VALUES
    ('Ana Torres', 'ana@universidad.edu'),
    ('Luis Pérez', 'luis@universidad.edu');
GO

INSERT INTO Asignatura (nombre, creditos)
VALUES
    ('Bases de Datos', 3),
    ('Redes de Datos', 3);
GO

INSERT INTO Matricula
    (id_estudiante, id_asignatura, nota)
VALUES
    (1, 1, 4.50),
    (1, 2, 3.80),
    (2, 1, 4.20);
GO

/* Mostrar tres tablas */
SELECT
    e.nombre AS estudiante,
    a.nombre AS asignatura,
    m.fecha,
    m.nota
FROM Matricula AS m
INNER JOIN Estudiante AS e
    ON m.id_estudiante = e.id_estudiante
INNER JOIN Asignatura AS a
    ON m.id_asignatura = a.id_asignatura
ORDER BY e.nombre, a.nombre;
GO