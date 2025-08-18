//Módulos requeridos
const express = require('express');
const mysql = require('mysql2/promise');
const app = express();
//Puerto o recurso
const port = 5000;
//pool es una técnica para gestionar varias BD
const pool = mysql.createPool({
  host: 'db',
  user: 'usuario',
  database: 'Ejemplo',
  password: 'contrasena',
  waitForConnections: true,
  connectionLimit: 10,
  queueLimit: 0
});
//Realizar una consulta de la tabla elementos
app.get('/elementos', async (req, res) => {
  try {
    //Presenta la información en forma de json para su presentación en el 
    //servidor
    const [rows, fields] = await pool.execute('SELECT * FROM elementos');
    res.send(rows);
  } catch (err) {
    console.error(err);
    res.send("Error " + err);
  }
});
//Consultar elemento por ID
app.get('/elementos/:id', async (req, res) => {
  const elemID = req.params.id;
  try {
      const [rows, fields] = await pool.execute('SELECT * FROM elementos WHERE id = ?', [elemID]);
      if (rows.length === 0) {
        //res es la respuesta, status es una forma estandar para renderizar el error 404 con el 
        //texto No se encontro elemento
          return res.status(404).send("No se encontro elemento");
      }
      res.send(rows[0]);
  } catch (err) {
      console.error(err);
      //500 es error interno del servidor
      res.status(500).send("Error " + err);
  }
});
//Configuración del oyente
app.listen(port, () => {
  console.log('Servidor en ejecución');
});
