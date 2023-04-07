import pandas as pd
# Conexión a la base de datos 
from sqlalchemy import create_engine
#Instale sqlalchemy con pip install --upgrade 'sqlalchemy<2.0'

#engine = create_engine('tipo_de_base_de_datos://usuario:contraseña@host:puerto/base_de_datos')
conn = create_engine('mysql+pymysql://root:12345@localhost:3306/biblioteca')
#Ejecutar un query (1)
df=pd.read_sql("SELECT * FROM clientes", conn)
#print(df)
#Ejecutar un query (2)
df=pd.read_sql_query("SELECT NOMBRE, SUM(2*CODIGO_AUTOR) AS AUTO FROM AUTOR WHERE CODIGO_AUTOR > 1 GROUP BY NOMBRE ORDER BY NOMBRE DESC", conn)
#print(df)
# Leer tabla usando SQL
df = pd.read_sql_table("autor", conn)
#Exportar tabla
df.to_sql('clientes', conn, if_exists='replace')
#Actualizar mediante query
#query = 'UPDATE nombre_de_tu_tabla SET columna1 = 4, columna2 = "d" WHERE id = 1'
#conn.execute(query)
df['NOMBRE'].hist()
import base64
with open('SQL.py', 'rb') as file:
    archivo = file.read()
archivo_base64 = base64.b64encode(archivo)
print(archivo_base64)
archivo_decodificado = base64.b64decode(archivo_base64)
print(archivo_decodificado)

