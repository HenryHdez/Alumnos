var mysql      =  require('mysql2');
//Parámetros de la conexión
var conexion = mysql.createConnection({
  host             : 'localhost',
  port             : '3306',
  user             : 'root',
  password         : '12345',
  database         : 'SERVICIOS',
});
//Funcion conectar del API, retorna error.
conexion.connect(function(err){
  if (err) {
      console.error('Error de conexion: ' + err.stack);
      return;
  }
  console.log('Conectado con el identificador ' + conexion.threadId);
});
//Terminar la conexión a la BD
conexion.end();

