const net = require('net');
const os = require('os');

const HOST = 'ubuntu1';
const PORT = 5000;

const client = new net.Socket();

client.connect(PORT, HOST, () => {
  console.log('Conectado al servidor');

  setInterval(() => {
    const data = {
      hostname: os.hostname(),
      plataforma: os.platform(),
      cpu: os.cpus().length,
      memoria_total: os.totalmem(),
      memoria_libre: os.freemem(),
      uptime: os.uptime(),
      timestamp: new Date().toISOString()
    };

    client.write(JSON.stringify(data));
  }, 5000);
});

client.on('error', (err) => {
  console.log('Error:', err.message);
});

client.on('close', () => {
  console.log('Conexion cerrada');
});