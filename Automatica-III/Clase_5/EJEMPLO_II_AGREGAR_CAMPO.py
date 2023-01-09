# -*- coding: utf-8 -*-
"""Importar librería del conector de mysql"""
import mysql.connector as mysql
"""Crear variables con los parámetros de acceso a la BD"""
ORIGEN="localhost"
USUARIO="root"
CONTRASENA="12345"
BASEDATOS="Admin_auto_III"

"""Establecer la conexión con la BD"""
BD = mysql.connect(host=ORIGEN, user=USUARIO, passwd=CONTRASENA, db=BASEDATOS)
Cursor = BD.cursor()
"""Ejecutar comandos de SQL con .execute, por ejemplo agregar un equipo"""
Comando="INSERT INTO Motor (Valvulas, Seriales) VALUES(%s, %s);"
Valores=(str(12),str(123))
Cursor.execute(Comando,Valores)
BD.commit()
"""Cerrar la BD"""
BD.close()

