const net = require('net');

const HOST = '0.0.0.0';
const PORT = 5000;

const server = net.createServer((socket) => {
  console.log('Cliente conectado:', socket.remoteAddress);

  socket.on('data', (data) => {
    try {
      const info = JSON.parse(data.toString());
      console.log('Datos recibidos:');
      console.log(info);
    } catch (e) {
      console.log('Error al parsear:', data.toString());
    }
  });

  socket.on('end', () => {
    console.log('Cliente desconectado');
  });
});

server.listen(PORT, HOST, () => {
  console.log(`Servidor escuchando en ${HOST}:${PORT}`);
});