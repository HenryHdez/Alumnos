const express = require('express');
const mysql = require('mysql2/promise');
const app = express();
const port = 3000;

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

app.listen(port, () => {
  console.log('Server running on http://localhost:${port}');
});
