CREATE DATABASE UNIVERSIDAD;
USE UNIVERSIDAD;

CREATE TABLE Estudiantes (  
ID_Estudiante INT PRIMARY KEY,  
Nombre VARCHAR(50),  
Apellido VARCHAR(50));

CREATE TABLE Asignaturas (  
ID_Asig INT PRIMARY KEY,  
Nombre VARCHAR(50));

CREATE TABLE Estudiantes_Asignaturas ( ID_Estudiante INT,  
ID_Asig INT,  
PRIMARY KEY (ID_Estudiante, ID_Asig), 
FOREIGN KEY (ID_Estudiante) REFERENCES Estudiantes(ID_Estudiante),  FOREIGN KEY (ID_Asig) REFERENCES Asignaturas(ID_Asig));


INSERT INTO Estudiantes (ID_Estudiante, Nombre, Apellido)
VALUES (1, 'Juan', 'Pérez'),
       (2, 'María', 'González'),
       (3, 'Pedro', 'Sánchez'),
       (4, 'Ana', 'Ramírez');
       
INSERT INTO Asignaturas (ID_Asig, Nombre)
VALUES (1, 'Matemáticas'),
       (2, 'Historia'),
       (3, 'Ciencias'),
       (4, 'Lengua');
       
       
INSERT INTO Estudiantes_Asignaturas (ID_Estudiante, ID_Asig)
VALUES (1, 1),
       (1, 2),
       (2, 3),
       (3, 1),
       (3, 4),
       (4, 2),
       (4, 3);

INSERT INTO Estudiantes_Asignaturas (ID_Estudiante, ID_Asig)
VALUES (1, 1),
       (4, 3);
       
       
       
-- Crear tabla original con datos separados por comas
CREATE TABLE example (
   id INT PRIMARY KEY,
   data VARCHAR(50)
);

INSERT INTO example VALUES
   (1, 'apple, orange, banana'),
   (2, 'pear, peach, kiwi'),
   (3, 'grape, cherry');

-- Crear tabla separada y poblarla
CREATE TABLE example_normalized (
   id INT,
   item VARCHAR(50)
);

CREATE TABLE Clientes (
  ID_Cliente INT PRIMARY KEY,
  Nombre_Cliente VARCHAR(50)
);

INSERT INTO Clientes (ID_Cliente, Nombre_Cliente)
VALUES
  (1, 'Ana'),
  (2, 'Juan'),
  (3, 'Luis');

CREATE TABLE Productos (
  ID_Producto INT PRIMARY KEY,
  Nombre_Producto VARCHAR(50)
);

INSERT INTO Productos (ID_Producto, Nombre_Producto)
VALUES
  (1, 'Producto A'),
  (2, 'Producto B'),
  (3, 'Producto C');

CREATE TABLE Ventas (
  ID_Venta INT PRIMARY KEY,
  ID_Cliente INT,
  ID_Producto INT,
  Cantidad INT,
  Precio_Unitario DECIMAL(8,2),
  FOREIGN KEY (ID_Cliente) REFERENCES Clientes(ID_Cliente),
  FOREIGN KEY (ID_Producto) REFERENCES Productos(ID_Producto)
);

INSERT INTO Ventas (ID_Venta, ID_Cliente, ID_Producto, Cantidad, Precio_Unitario)
VALUES
  (1, 1, 1, 2, 10),
  (2, 1, 2, 1, 15),
  (3, 2, 1, 3, 10),
  (4, 3, 3, 1, 20);
  
  SELECT *FROM Ventas;
  
CREATE TABLE Ventas ( 
  ID INT PRIMARY KEY,
  Producto VARCHAR(50),
  Cantidad INT,
  Precio INT
  );

INSERT INTO Ventas (ID, Producto, Cantidad, Precio)
VALUES (1, 'A', 5, 10), (2, 'B', 10, 15), (3, 'C', 2, 20),
(4, 'D', 3, 25);


