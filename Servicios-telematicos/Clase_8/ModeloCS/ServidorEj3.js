const express = require('express');
const net = require('net');

const app = express();

const API_PORT = 8080;
const TCP_PORT = 5000;
const TCP_HOST = '0.0.0.0';

let ultimoDato = null;
let historial = [];

// ---------- API REST ----------
app.get('/', (req, res) => {
  res.send('API de monitoreo activa');
});

app.get('/ultimo', (req, res) => {
  if (!ultimoDato) {
    return res.status(404).json({ mensaje: 'No hay datos recibidos' });
  }
  res.json(ultimoDato);
});

app.get('/historial', (req, res) => {
  res.json(historial);
});

app.get('/cantidad', (req, res) => {
  res.json({ cantidad: historial.length });
});

// ---------- Servidor TCP ----------
const tcpServer = net.createServer((socket) => {
  console.log(`Cliente conectado: ${socket.remoteAddress}:${socket.remotePort}`);

  socket.on('data', (data) => {
    try {
      const texto = data.toString().trim();
      const json = JSON.parse(texto);

      ultimoDato = json;
      historial.push(json);

      console.log('Dato recibido por TCP:');
      console.log(json);
    } catch (error) {
      console.log('Error al procesar dato recibido:', error.message);
      console.log('Contenido recibido:', data.toString());
    }
  });

  socket.on('end', () => {
    console.log('Cliente desconectado');
  });

  socket.on('error', (err) => {
    console.log('Error en socket:', err.message);
  });
});

// Levantar API
app.listen(API_PORT, '0.0.0.0', () => {
  console.log(`API REST ejecutándose en puerto ${API_PORT}`);
});

// Levantar servidor TCP
tcpServer.listen(TCP_PORT, TCP_HOST, () => {
  console.log(`Servidor TCP escuchando en ${TCP_HOST}:${TCP_PORT}`);
});