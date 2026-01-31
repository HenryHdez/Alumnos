import pandas as pd

datos = {'nombre': ['Miguel', 'Mario', 'Pedro', 'Lucy'],
               'edad': [32, 45, 38, 43],
               'ciudad': ['Medellín','Bogotá','San Andrés','Pasto']}
print(datos)

#Actualizar
datos.update({'edad':[28,32,11,22]})
print(datos)

#Eliminar índice
datos.pop('ciudad')
print(datos)

datos['apellido'] = ['Gómez', 'Ramírez', 'López', 'Martínez']

df = pd.DataFrame(datos)
print(df)

#Limpiar dataFrame
datos.clear()
print(datos)