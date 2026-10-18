var mysql      =  require('mysql2');
//Parámetros de la conexión
var conexion = mysql.createConnection({
  host             : 'localhost',
  port             : '3307',
  user             : 'root',
  password         : '0000',
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
//Realizar una consulta
conexion.query('SELECT * FROM Tabla1', 
function (error, results, fields) {
  if (error)
      throw error;
  //Lectura de la respuesta del QUERY y 
  results.forEach(result => {
      console.log(result);
  });
});
//Terminar la conexión a la BD
conexion.end();

