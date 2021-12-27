# -*- coding: utf-8 -*-
"""Importar librer�a del conector de mysql"""
import mysql.connector as mysql

"""Crear variables con los par�metros de acceso a la BD"""
ORIGEN="localhost"
USUARIO="root"
CONTRASENA=""
BASEDATOS="Administrador_Red"
"""Establecer la conexi�n con la BD"""
BD = mysql.connect(host=ORIGEN, user=USUARIO, passwd=CONTRASENA, db=BASEDATOS)
Cursor = BD.cursor()
"""Ejecutar comandos de SQL con .execute, por ejemplo una consulta"""
Cursor.execute('SELECT * FROM Administrador_Red WHERE (Equipos= "PC")')
for row in Cursor:
   print(row)
"""Cerrar la BD"""
BD.close()
