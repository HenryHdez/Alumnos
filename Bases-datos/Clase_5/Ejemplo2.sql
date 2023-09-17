#Tabla sin cifrar
CREATE TABLE InformacionPersonal (
    ID int PRIMARY KEY,
    Nombre varchar(255),
    Direccion varchar(255),
    SSN varchar(11)
);

INSERT INTO InformacionPersonal (ID, Nombre, Direccion, SSN)
VALUES (1, 'Juan', 'Calle Falsa 123', AES_ENCRYPT('123-45-6789', 'llave_secreta'));

ALTER TABLE InformacionPersonal
MODIFY SSN BLOB;

SELECT ID, Nombre, Direccion, CAST(AES_DECRYPT(SSN, 'llave_secreta') AS CHAR(15)) as SSN_decifrado
FROM InformacionPersonal;


CREATE TABLE Usuarios (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(255) NOT NULL,
    password BLOB
);

INSERT INTO Usuarios (username, password) VALUES
('Usuario1', DES_ENCRYPT('pass1', 'miClaveSecreta')),
('Usuario2', DES_ENCRYPT('pass2', 'miClaveSecreta')),
('Usuario3', DES_ENCRYPT('pass3', 'miClaveSecreta')),
('Usuario4', DES_ENCRYPT('pass4', 'miClaveSecreta')),
('Usuario5', DES_ENCRYPT('pass5', 'miClaveSecreta'));

SELECT username, CAST(DES_DECRYPT(password, 'miClaveSecreta') AS CHAR(50)) AS password_decrypted
FROM Usuarios;

CREATE TABLE Usuarios (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(255) NOT NULL,
    hashed_password CHAR(64)
);

INSERT INTO Usuarios (username, hashed_password) VALUES 
('user1', SHA2('password1', 256)),
('user2', SHA2('password2', 256)),
('user3', SHA2('password3', 256));

SELECT username 
FROM Usuarios 
WHERE username = 'user1' AND hashed_password = SHA2('password1', 256);



