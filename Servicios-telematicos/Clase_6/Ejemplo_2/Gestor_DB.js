async function consulta() {
    //Consulta optimizada
    const mysql = require('mysql2/promise');
    //Crear conexión
    const connection = await mysql.createConnection({
    host             : 'localhost',
    port             : '3307',
    user             : 'root',
    password         : '0000',
    database         : 'SERVICIOS',
    });
    //Realizar query
    const [Filas, Campos] = await(connection.execute('SELECT * FROM Tabla1'));
    connection.end();
    return Filas;
}
module.exports=consulta();

