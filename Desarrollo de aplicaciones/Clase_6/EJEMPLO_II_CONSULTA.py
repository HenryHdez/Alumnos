# -*- coding: utf-8 -*-
"""Importar librería del conector de mysql"""
import pymysql as mysql
"""Crear variables con los parámetros de acceso a la BD"""
ORIGEN="localhost"
USUARIO="root"
CONTRASENA="0000"
BASEDATOS="EJ1"
PORT=3307

"""Establecer la conexión con la BD"""
BD = mysql.connect(host=ORIGEN, user=USUARIO, passwd=CONTRASENA, db=BASEDATOS, port=PORT)
Cursor = BD.cursor()
"""Ejecutar comandos de SQL con .execute, por ejemplo una consulta"""
Cursor.execute("SELECT * FROM Nombredelatabla")
for row in Cursor:
   print(row)
"""Cerrar la BD"""
BD.close()

