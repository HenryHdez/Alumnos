import pandas as pd

datos = {'nombre': ['Miguel', 'Mario', 'Pedro', 'Lucy'],
        'edad': [32, 45, 38, 43],
        'ciudad': ['Medellín','Bogotá','San Andrés','Pasto']}

print(datos['nombre']) #Valores de la clave especifica
print(datos.keys()) #Claves del diccionario
print(datos.values()) #Valores del diccionario
print(datos.items()) #Claves y valores del diccionario

datos.update({'edad': [33, 46, 39, 44]}) #Actualizar el valor de una clave
print(datos) #Valores de la clave especifica

datos.pop('ciudad') #Eliminar una clave y su valor
print(datos) #Valores de la clave especifica

datos['profesion'] = ['Ingeniero', 'Abogado', 'Médico', 'Arquitecto'] #Agregar una nueva clave y su valor

df=pd.DataFrame(datos) #Convertir el diccionario a un DataFrame de pandas

df.to_csv('datos.csv', index=False) #Guardar el DataFrame en un archivo CSV sin el índice
df2 = pd.read_csv('datos.csv') #Leer el archivo CSV y convertirlo a un DataFrame        
print(df2) 
#Mostrar el DataFrame leído desde el archivo CSV

import pandas as pd
from sqlalchemy import create_engine 
conn = create_engine('mysql+pymysql://root:12345@localhost:3306/biblioteca')
#Ejecutar un query (1)
df=pd.read_sql("SELECT * FROM clientes", conn)
print(df)

df = pd.read_sql_query("SELECT Departamento, SUM(ID*Salario) AS ventas_totales FROM clientes WHERE Salario > 100 GROUP BY Departamento ORDER BY ventas_totales DESC", conn)

import pandas as pd
import matplotlib.pyplot as plt
# Crear un DataFrame de ejemplo
data = {'columna1': [1, 2, 3, 4, 5],      'columna2': [2, 4, 6, 8, 10]}
df = pd.DataFrame(data)
# Crear un histograma de la columna1
df['columna1'].hist()
# Agregar etiquetas al gráfico
plt.title('Histograma de columna1')
plt.xlabel('Valor')
plt.ylabel('Frecuencia')
# Mostrar el gráfico
plt.show()
