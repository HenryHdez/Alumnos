import pymysql

# Conexión al nodo maestro
master_connection = pymysql.connect(
    host='localhost',
    user='root',
    password='micontrasena',
    port=3307
)

# Conexión a los nodos esclavos
slave1_connection = pymysql.connect(
    host='localhost',
    user='root',
    password='contraslave',
    port=3308
)

slave2_connection = pymysql.connect(
    host='localhost',
    user='root',
    password='contraslave',
    port=3309
)

cursor = master_connection.cursor()
cursor.execute("SHOW DATABASES")

for db in cursor.fetchall():
    print(db)

cursor.close()
master_connection.close()
slave1_connection.close()
slave2_connection.close()
