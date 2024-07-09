import pandas as pd
import base64
from sqlalchemy import create_engine
from matplotlib import pyplot as plt
from matplotlib import image as mpimg

conn = create_engine('mysql+pymysql://root:12345@localhost:3306/universidad')
with open('Prueba.jpg', 'rb') as file:
    archivo = file.read()
    
contenido_codificado = "'"+base64.b64encode(archivo).decode('utf-8')+"'"

query = "UPDATE empleados SET Foto = "+contenido_codificado+" WHERE id = 1"
conn.execute(query)
df=pd.read_sql("SELECT * FROM empleados", conn)

# Decodifica el contenido de la imagen en Base64
contenido_decodificado = base64.b64decode(df['Foto'][0])
# Guarda el contenido decodificado en un archivo nuevo
with open("imagen_decodificada.jpg", "wb") as archivo:
    archivo.write(contenido_decodificado)
#Publicar imagen
image = mpimg.imread('imagen_decodificada.jpg')
plt.imshow(image)
plt.show()


import pandas as pd
import base64
from sqlalchemy import create_engine
from matplotlib import pyplot as plt
from matplotlib import image as mpimg

conn = create_engine('mysql+pymysql:'+
                     '//root:12345@localhost:3306/universidad')
#Convertir texto en String
base64.b64encode(archivo).decode('utf-8') 
query = "UPDATE tabla SET Algo WHERE Algo = 1"
conn.execute(query)
df=pd.read_sql("SELECT * FROM tabla", conn)


import pandas as pd
import base64
from sqlalchemy import create_engine
from matplotlib import pyplot as plt
from matplotlib import image as mpimg

# Conexión a la base de datos
conn = create_engine('mysql+pymysql://root:F1,N11.jkm*&11@localhost:3306/EjemploC')

# Carga de imagen
with open('Prueba.jpg', 'rb') as file:
    archivo = file.read()

# Codifica la imagen en Base64
contenido_codificado = "'"+base64.b64encode(archivo).decode('utf-8')+"'"

# Actualiza la tabla Empleados con la imagen
query = "UPDATE empleados SET Foto = "+contenido_codificado+" WHERE id = 1"
conn.execute(query)

# Lectura de datos de la tabla Empleados
df=pd.read_sql("SELECT * FROM empleados", conn)

# Decodifica el contenido de la imagen en Base64
contenido_decodificado = base64.b64decode(df['Foto'][0])

# Guarda el contenido decodificado en un archivo nuevo
with open("imagen_decodificada.jpg", "wb") as archivo:
    archivo.write(contenido_decodificado)

# Muestra la imagen
image = mpimg.imread('imagen_decodificada.jpg')
plt.imshow(image)
plt.show()

# -- coding: utf-8 --
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