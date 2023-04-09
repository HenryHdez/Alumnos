import pandas as pd

# Creamos un DataFrame de ejemplo
Ej = {'Nombre': ['Juan', 'Pedro', 'María', 'Ana'], 
      'Edad': [25, 30, 27, 23], 
      'País': ['México', 'España', 'Colombia', 'Argentina']}
df = pd.DataFrame(Ej)

# Guardamos el DataFrame en formato JSON
df.to_json('data.json')

# Guardamos el DataFrame en formato XLS
df.to_excel('data.xls', index=False)

# Guardamos el DataFrame en formato TXT
df.to_csv('data.txt', sep='\t', index=False)



