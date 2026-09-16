import pymysql

# Conexión al nodo maestro
master_connection = pymysql.connect(
    host='localhost',
    user='root',
    password='micontrasena',
    port=3308
)

cursor = master_connection.cursor()
cursor.execute("SHOW DATABASES")

for db in cursor.fetchall():
    print(db)

cursor.close()
master_connection.close()