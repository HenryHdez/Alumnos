# -*- coding: utf-8 -*-
"""Importar librería del conector de mysql"""
import mysql.connector as mysql
"""Crear variables con los parámetros de acceso a la BD"""
ORIGEN="localhost"
USUARIO="root"
CONTRASENA="12345"
BASEDATOS="Ejemplo_II"

"""Establecer la conexión con la BD"""
BD = mysql.connect(host=ORIGEN, user=USUARIO, passwd=CONTRASENA, db=BASEDATOS)
Cursor = BD.cursor()
"""Ejecutar comandos de SQL con .execute, por ejemplo una consulta"""
Cursor.execute("SELECT * FROM Motor")
for row in Cursor:
   print(row)
"""Cerrar la BD"""
BD.close()

