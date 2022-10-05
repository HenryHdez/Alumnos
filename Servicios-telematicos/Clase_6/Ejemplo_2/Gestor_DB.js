async function consulta() {
    //Consulta optimizada
    const mysql = require('mysql2/promise');
    //Crear conexión
    const connection = await mysql.createConnection({
        host             : 'localhost',
        port             : '3306',
        user             : 'root',
        password         : '12345',
        database         : 'SERVICIOS',
    });
    //Realizar query
    const [Filas, Campos] = await(connection.execute('SELECT * FROM Tabla1'));
    connection.end();
    return Filas;
}
module.exports=consulta();

