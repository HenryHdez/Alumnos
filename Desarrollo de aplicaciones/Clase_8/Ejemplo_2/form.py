import pandas as pd

datos = {'nombre': ['Miguel', 'Mario', 'Pedro', 'Lucy'],
               'edad': [32, 45, 38, 43],
               'ciudad': ['Medellín','Bogotá','San Andrés','Pasto']}
print(datos)
df = pd.DataFrame(datos)
print(df)
