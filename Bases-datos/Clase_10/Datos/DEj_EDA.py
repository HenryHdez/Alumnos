# Paso 1
import pandas as pd
# Paso 2
df = pd.read_csv('archivo.csv')
df = pd.read_sql("SELECT * FROM clientes", conn)
#Paso 3
# Ver las primeras filas del dataframe
df.head()
# Ver las últimas filas del dataframe
df.tail()
# Ver la forma del dataframe (número de filas y columnas)
df.shape
# Ver información sobre las columnas del dataframe (tipo de datos, número de valores no nulos, etc.)
df.info()
# Ver estadísticas resumidas para cada columna numérica del dataframe
df.describe()
#Paso 4
# Ver el número de valores faltantes por columna
df.isnull().sum()
# Eliminar las filas con valores faltantes
df.dropna(inplace=True)
# Rellenar los valores faltantes con un valor específico
df.fillna(value=0, inplace=True)
#Paso 5
# Histograma de una columna
df['columna'].hist()
# Diagrama de cajas de una columna
df.boxplot(column='columna')
# Gráfico de dispersión de dos columnas
df.plot.scatter(x='columna1', y='columna2')
#Paso 6
# Agrupar los datos por una columna y calcular la media de otra columna
df.groupby('columna1')['columna2'].mean()
# Calcular la correlación entre dos columnas
df['columna1'].corr(df['columna2'])
