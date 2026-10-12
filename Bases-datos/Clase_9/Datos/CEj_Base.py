import pandas as pd
from sqlalchemy import create_engine 
#(pip install --upgrade sqlalchemy<2.0)
#create_engine('tipo_de_base_de_datos://usuario:contraseña@host:puerto/base_de_datos')
conn = create_engine('mysql+pymysql://root:12345@localhost:3306/BIBLIOTECA')
#Ejecutar un query (1)
df=pd.read_sql("SELECT * FROM Clientes", conn)
print(df)

df = pd.read_sql_query("""
    SELECT Departamento, COUNT(*) AS total_clientes
    FROM Clientes
    GROUP BY Departamento
    ORDER BY total_clientes DESC;
""", conn)
print(df)

df = pd.read_sql_query("""
    SELECT Departamento, Nombre, COUNT(*) AS total_clientes
    FROM Clientes
    GROUP BY Departamento, Nombre
    HAVING total_clientes > 2
    ORDER BY total_clientes DESC
""", conn)
print(df)



