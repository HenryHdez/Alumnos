const express = require('express');
const mysql = require('mysql2/promise');
const cors = require('cors');
const app = express();
const port = 5000;

//Cors es una indicación de origenes autorizados a ingresar a un recurso
app.use(cors({
  origin: ['http://localhost:8080', 'http://127.0.0.1:8080', 'http://localhost:5000']
}));

//Es un manejador de archivos JSON como parametro de entrada
app.use(express.json()); 

const pool = mysql.createPool({
  host: 'db',
  user: 'usuario',
  database: 'Ejemplo',
  password: 'contrasena',
  waitForConnections: true,
  connectionLimit: 10,
  queueLimit: 0
});

app.get('/elementos', async (req, res) => {
  try {
    const [rows, fields] = await pool.execute('SELECT * FROM elementos');
    res.send(rows);
  } catch (err) {
    console.error(err);
    res.send("Error " + err);
  }
});

app.get('/elementos/:id', async (req, res) => {
  const itemId = req.params.id;
  try {
      const [rows, fields] = await pool.execute('SELECT * FROM elementos WHERE id = ?', [itemId]);
      if (rows.length === 0) {
          return res.status(404).send("No encontrado");
      }
      res.send(rows[0]);
  } catch (err) {
      console.error(err);
      res.status(500).send("Error " + err);
  }
});
// Agregar un nuevo elemento
app.post('/elementos', async (req, res) => {
  const { nombre } = req.body;
  if (!nombre) {
      return res.status(400).json({ error: "Digite un nombre" });
  }
  try {
      const [resultado] = await pool.execute('INSERT INTO elementos (name) VALUES (?)', [nombre]);
      res.json({ message: "Elemento agregado satisfactoriamente", id: resultado.insertId });
  } catch (err) {
      console.error(err);
      res.status(500).json({ error: "Error del servidor" });
  }
});
// Actualizar un elemento
app.put('/elementos/:id', async (req, res) => {
  const elementoid = req.params.id;
  const { nombre } = req.body;
  if (!nombre) {
      return res.status(400).json({ error: "Digite un nombre" });
  }
  try {
      const [result] = await pool.execute('UPDATE elementos SET name = ? WHERE id = ?', [nombre, elementoid]);
      if (result.affectedRows === 0) {
          return res.status(404).json({ error: "Elemento no encontrado" });
      }
      res.json({ message: "Elemento actualizado" });
  } catch (err) {
      console.error(err);
      res.status(500).json({ error: "Error interno del servidor" });
  }
});
//Creación del oyente
app.listen(port, () => {
  console.log('Servidor en ejecución');
});