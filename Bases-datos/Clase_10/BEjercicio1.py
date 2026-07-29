import base64
import pandas as pd
from sqlalchemy import create_engine 
#(pip install --upgrade sqlalchemy<2.0)
#create_engine('tipo_de_base_de_datos://usuario:contraseña@host:puerto/base_de_datos')

with open('ArchivoOriginal.jpg', 'rb') as file:
    archivo = file.read()
archivo_base64 = base64.b64encode(archivo)
print("Base64:", archivo_base64[:60])

#Procesamos como string
diccionario={'imagen1':[archivo_base64]}
print(diccionario)
df=pd.DataFrame(diccionario)
conn = create_engine('mysql+pymysql://root:12345@localhost:3308/BIBLIOTECA')
df.to_sql('Imagenes', conn, if_exists='replace')
#El string lo podemos enviar a una base de datos donde hay un campo tipo TEXT

archivo_decodificado = base64.b64decode(archivo_base64)
with open('archivoRestaurado.jpg', 'wb') as file:
    file.write(archivo_decodificado)




