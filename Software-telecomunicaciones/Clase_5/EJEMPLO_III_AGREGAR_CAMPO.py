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
"""Ejecutar comandos de SQL con .execute, por ejemplo agregar un equipo"""
Comando="INSERT INTO Administrador_Red (Equipos, Seriales) VALUES(%s, %s);"
Valores=("PC Personal",str(77))
Cursor.execute(Comando,Valores)
BD.commit()
"""Cerrar la BD"""
BD.close()