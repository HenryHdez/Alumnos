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

