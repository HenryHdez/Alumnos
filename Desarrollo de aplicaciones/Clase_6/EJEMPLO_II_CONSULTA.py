# -*- coding: utf-8 -*-
"""Importar librería del conector de mysql"""
import pymysql as mysql
"""Crear variables con los parámetros de acceso a la BD"""
ORIGEN="localhost"
USUARIO="root"
CONTRASENA="12345"
BASEDATOS="ejm1"

"""Establecer la conexión con la BD"""
BD = mysql.connect(host=ORIGEN, user=USUARIO, passwd=CONTRASENA, db=BASEDATOS)
Cursor = BD.cursor()
"""Ejecutar comandos de SQL con .execute, por ejemplo una consulta"""
Cursor.execute("SELECT * FROM tabla")
for row in Cursor:
   print(row)
"""Cerrar la BD"""
BD.close()

