CREATE DATABASE CLA7EJ1;
USE CLA7EJ1;

CREATE TABLE Autores (autor_id INT PRIMARY KEY, nombre VARCHAR(255));
INSERT INTO Autores VALUES (1, 'J.K. Rowling'), (2, 'J.R.R. Tolkien'), (3, 'George Orwell');

CREATE TABLE Libros (libro_id INT PRIMARY KEY, titulo VARCHAR(255), autor_id INT);
INSERT INTO Libros VALUES (1, 'Harry Potter', 1), (2, 'The Hobbit', 2), (3, '1984', 3), (4, 'The Lord of the Rings', 2), (5, 'Animal Farm', 3);

SELECT * FROM Autores;
SELECT * FROM Libros;

SELECT * FROM Libros WHERE autor_id = 3;

SELECT Libros.titulo, Autores.nombre 
FROM Libros 
INNER JOIN Autores ON Libros.autor_id = Autores.autor_id;

SELECT Autores.nombre, COUNT(Libros.libro_id) as number_of_books 
FROM Libros 
JOIN Autores ON Libros.autor_id = Autores.autor_id 
GROUP BY Autores.nombre;

SELECT Autores.nombre, COUNT(Libros.libro_id) as number_of_books 
FROM Libros 
JOIN Autores ON Libros.autor_id = Autores.autor_id 
GROUP BY Autores.nombre 
ORDER BY number_of_books DESC 
LIMIT 1;

SELECT nombre FROM Autores WHERE autor_id IN (SELECT autor_id FROM Libros GROUP BY autor_id HAVING COUNT(libro_id) > 1);

UPDATE Autores SET nombre = 'Joanne Rowling' WHERE autor_id = 1;

DELETE FROM Libros WHERE titulo = 'The Hobbit';

SELECT autor_id FROM Libros GROUP BY autor_id HAVING COUNT(libro_id) > 1;




