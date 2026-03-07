#Crear test_db 
#CREATE DATABASE test_db;
import pymysql

# Conexión al servidor MySQL
connection = pymysql.connect(
    host='localhost',
    user='root',
    password='12345',
    port=3306,
    database='test_db'
)

try:
    with connection.cursor() as cursor:
        # Crear tabla
        cursor.execute("""
            CREATE TABLE IF NOT EXISTS empleados (
                id INT AUTO_INCREMENT PRIMARY KEY,
                nombre VARCHAR(50),
                puesto VARCHAR(50),
                salario DECIMAL(10, 2)
            )
        """)

        # Insertar datos (si aún no hay registros)
        cursor.execute("SELECT COUNT(*) FROM empleados")
        if cursor.fetchone()[0] == 0:
            cursor.execute("INSERT INTO empleados (nombre, puesto, salario) VALUES (%s, %s, %s)", ('Ana Pérez', 'Ingeniera', 4500.00))
            cursor.execute("INSERT INTO empleados (nombre, puesto, salario) VALUES (%s, %s, %s)", ('Luis Torres', 'Técnico', 3200.00))
            connection.commit()

        # Consulta
        cursor.execute("SELECT * FROM empleados")
        resultados = cursor.fetchall()

        # Mostrar resultados
        print("Lista de empleados:")
        for fila in resultados:
            print(fila)

finally:
    connection.close()
