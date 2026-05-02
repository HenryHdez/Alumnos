import base64
import pandas as pd
from sqlalchemy import create_engine 
#(pip install --upgrade sqlalchemy<2.0)
#create_engine('tipo_de_base_de_datos://usuario:contraseña@host:puerto/base_de_datos')

with open('Prueba.jpg', 'rb') as file:
    archivo = file.read()
archivo_base64 = base64.b64encode(archivo)
#print("Base64:", archivo_base64[:60])

#Procesamos como string
diccionario={'imagen1':[archivo_base64]}
df=pd.DataFrame(diccionario)

#Leer clientes
conn = create_engine('mysql+pymysql://root:12345@localhost:3306/BIBLIOTECA')
dfleido = pd.read_sql("SELECT * FROM clientes", conn)
diccionario_leido = dfleido.to_dict(orient='list')
print(diccionario_leido)
diccionario_leido['Foto'][3]=archivo_base64
df2=pd.DataFrame(diccionario_leido)
df2.to_sql('clientes', conn, if_exists='replace', index=False)
#conn.execute("INSERT INTO clientes (Foto) VALUES (%s) WHERE ID = %s", (archivo_base64, 1))
#df.to_sql('Imagenes', conn, if_exists='replace')
#El string lo podemos enviar a una base de datos donde hay un campo tipo TEXT

archivo_decodificado = base64.b64decode(archivo_base64)
with open('archivoRestaurado.jpg', 'wb') as file:
    file.write(archivo_decodificado)




