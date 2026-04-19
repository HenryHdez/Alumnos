const net = require('net');

const HOST = '0.0.0.0';
const PORT = 5000;

const server = net.createServer((socket) => {
  console.log('Cliente conectado desde:', socket.remoteAddress, socket.remotePort);

  socket.on('data', (data) => {
    const mensaje = data.toString();
    console.log('Mensaje recibido del cliente:', mensaje);

    socket.write('Hola cliente, recibi su mensaje: ' + mensaje);
  });

  socket.on('end', () => {
    console.log('Cliente desconectado');
  });

  socket.on('error', (err) => {
    console.log('Error en el socket:', err.message);
  });
});

server.listen(PORT, HOST, () => {
  console.log(`Servidor TCP escuchando en ${HOST}:${PORT}`);
});