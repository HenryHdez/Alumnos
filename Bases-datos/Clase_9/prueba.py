import pandas as pd
import matplotlib.pyplot as plt
from sqlalchemy import create_engine #(pip install --upgrade sqlalchemy<2.0)
#create_engine('tipo_de_base_de_datos://usuario:contraseña@host:puerto/base_de_datos')
conn = create_engine('mysql+pymysql://root:12345@localhost:3306/biblioteca')
#Ejecutar un query (1)
df=pd.read_sql("SELECT * FROM clientes", conn)
print(df.columns)
print(df.isnull().sum())
df.fillna(value=0, inplace=True)
print(df.describe())
print(df)
df['Nombre'].hist()

plt.title('Histograma de columna1')
plt.xlabel('Valor')
plt.ylabel('Frecuencia')
# Mostrar el gráfico
plt.show()


