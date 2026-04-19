const net = require('net');

const HOST = 'ubuntu1';
const PORT = 5000;

const client = new net.Socket();

client.connect(PORT, HOST, () => {
  console.log(`Conectado al servidor ${HOST}:${PORT}`);
  client.write('Hola servidor');
});

client.on('data', (data) => {
  console.log('Respuesta del servidor:', data.toString());
  client.end();
});

client.on('close', () => {
  console.log('Conexion cerrada');
});

client.on('error', (err) => {
  console.log('Error:', err.message);
});
