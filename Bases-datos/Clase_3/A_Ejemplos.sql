CREATE DATABASE EJEMPLO;
USE EJEMPLO;
CREATE TABLE DEPORTES(
	ID INT AUTO_INCREMENT PRIMARY KEY,
	ACTIVIDAD VARCHAR(100) NOT NULL    
);

CREATE TABLE ALUMNOS(
	ID INT AUTO_INCREMENT PRIMARY KEY,
    IDEPORTE INT DEFAULT 1,
    NOMBRE VARCHAR(100) NOT NULL,
    FOREIGN KEY (IDEPORTE) REFERENCES DEPORTES(ID)
);

INSERT INTO DEPORTES (ACTIVIDAD) VALUES ('NATACIÓN'), ('FUTBOL'), ('BALONCESTO');

INSERT INTO ALUMNOS (IDEPORTE, NOMBRE) VALUES (3, 'EST1'), (2, 'EST2'), (2, 'EST3');

SELECT * FROM DEPORTES;
SELECT * FROM ALUMNOS;

DROP TABLE ALUMNOS;
DROP TABLE DEPORTES;
DROP TABLE MATRICULA;

CREATE TABLE DEPORTES(
	ID_DEP INT AUTO_INCREMENT PRIMARY KEY,
	ACTIVIDAD VARCHAR(100) NOT NULL    
);

CREATE TABLE ALUMNOS(
	ID_ALU INT AUTO_INCREMENT PRIMARY KEY,
    NOMBRE VARCHAR(100) NOT NULL
);

CREATE TABLE MATRICULA(
	ID INT AUTO_INCREMENT PRIMARY KEY,
    ID_DEP INT NOT NULL,
    ID_ALU INT NOT NULL,
    FOREIGN KEY (ID_DEP) REFERENCES DEPORTES(ID_DEP),
    FOREIGN KEY (ID_ALU) REFERENCES ALUMNOS(ID_ALU)
);

INSERT INTO DEPORTES (ACTIVIDAD) VALUES ('NATACIÓN'), ('FUTBOL'), ('BALONCESTO');
INSERT INTO ALUMNOS (NOMBRE) VALUES ('EST1'), ('EST2'), ('EST3');
INSERT INTO MATRICULA (ID_DEP, ID_ALU) VALUES (1,1), (1,2), (2,1), (1,3);

SELECT * FROM DEPORTES;
SELECT * FROM ALUMNOS;
SELECT * FROM MATRICULA;

CREATE TABLE ALUMNOS(
	ID_ALU INT PRIMARY KEY,
    NOMBRE VARCHAR(100) NOT NULL
);

CREATE TABLE MATRICULA(
	ID_ALU INT UNIQUE,
    HORARIO VARCHAR(100) NOT NULL,
    FOREIGN KEY (ID_ALU) REFERENCES ALUMNOS(ID_ALU)
);

INSERT INTO ALUMNOS (ID_ALU, NOMBRE) 
VALUES (1, 'EST1'), (2, 'EST2'), (3, 'EST3');
INSERT INTO MATRICULA (ID_ALU, HORARIO) 
VALUES (1,'MAÑANA'), (2,'MAÑANA'), (3,'TARDE');
