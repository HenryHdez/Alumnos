//Agregar el código del servidor TCP y el servidor HTTP en un mismo archivo
// ---------- Vista HTML ----------
app.get('/tabla', (req, res) => {
  let filas = historial.map((item, index) => `
    <tr>
      <td>${index + 1}</td>
      <td>${item.hostname ?? ''}</td>
      <td>${item.plataforma ?? ''}</td>
      <td>${item.cpu ?? ''}</td>
      <td>${item.memoria_total ?? ''}</td>
      <td>${item.memoria_libre ?? ''}</td>
      <td>${item.uptime ?? ''}</td>
      <td>${item.timestamp ?? ''}</td>
    </tr>
  `).join('');

  const html = `
  <!DOCTYPE html>
  <html lang="es">
  <head>
    <meta charset="UTF-8">
    <meta http-equiv="refresh" content="5">
    <title>Monitoreo de equipos</title>
    <style>
      body {
        font-family: Arial, sans-serif;
        margin: 20px;
      }
      h1 {
        margin-bottom: 10px;
      }
      table {
        border-collapse: collapse;
        width: 100%;
      }
      th, td {
        border: 1px solid #999;
        padding: 8px;
        text-align: center;
      }
      th {
        background-color: #eaeaea;
      }
      tr:nth-child(even) {
        background-color: #f7f7f7;
      }
    </style>
  </head>
  <body>
    <h1>Historial de monitoreo</h1>
    <p>Total de registros: ${historial.length}</p>
    <table>
      <thead>
        <tr>
          <th>#</th>
          <th>Hostname</th>
          <th>Plataforma</th>
          <th>CPU</th>
          <th>Memoria total</th>
          <th>Memoria libre</th>
          <th>Uptime</th>
          <th>Timestamp</th>
        </tr>
      </thead>
      <tbody>
        ${filas}
      </tbody>
    </table>
  </body>
  </html>
  `;

  res.send(html);
});