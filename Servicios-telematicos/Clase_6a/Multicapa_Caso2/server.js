const express = require('express');
const mysql = require('mysql2/promise');
const cors = require('cors');
const app = express();
const port = 3000;

app.use(cors({
  origin: ['http://localhost:8080', 'http://127.0.0.1:8080', 'http://localhost:3000'] // ajusta según tus necesidades
}

));

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

app.put('/elementos/:id', async (req, res) => {
  const itemId = req.params.id;
  const { name } = req.body;

  if (!name) {
      return res.status(400).send("Name is required");
  }

  try {
      const [result] = await pool.execute('UPDATE elementos SET name = "asdasd" WHERE id = 1');
      if (result.affectedRows === 0) {
          return res.status(404).send("Item not found");
      }
      res.send("Item updated successfully");
  } catch (err) {
      console.error(err);
      res.status(500).send("Error " + err);
  }
});

app.listen(port, () => {
  console.log('Server running on http://localhost:${port}');
});
