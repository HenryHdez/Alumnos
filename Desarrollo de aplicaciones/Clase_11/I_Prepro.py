#pip install orange3
#Ej 1 - Importar un repositorio
from Orange.data import Table
data = Table("titanic")
print(data)
print("Nombres de los atributos:", data.domain)

#Ej 2 - Reemplazar valores faltantes
from Orange.data import Table
from Orange.preprocess import Impute
import numpy as np
# Cargar el dataset Titanic
data = Table("titanic")
# Simular valores faltantes 
data[0, 2] = np.nan  # Columna 2 (Genero)
data[5, 0] = np.nan  # Columna 0 (Clase)
data[10, 1] = None   # Columna 1 (Edad)
# Mostrar datos originales (12 primeras filas)
print("\nDatos originales con valores faltantes:")
for row in data[:12]:  
    print(row)
# Reemplazar valores faltantes utilizando imputación
# Usa la media (numéricos) o la moda (categóricos)
#Moda hace referencia al dato categórico más común
imputer = Impute()  
data2 = imputer(data)
# Mostrar datos después de la imputación
print("\nDatos después de reemplazar los valores faltantes:")
for row in data2[:12]:  
    print(row)

#Ej 3 - Normalizar
import numpy as np
from Orange.data import Table, Domain, ContinuousVariable
from Orange.preprocess import Normalize
# Generar un vector aleatorio
random_vector = np.random.uniform(low=0, high=100, size=10)
# Crear un dataset a partir del vector aleatorio
domain = Domain([ContinuousVariable("random_value")])
data = Table.from_list(domain, [[value] for value in random_vector])
# Normalizar los datos (0-1)
normalizer = Normalize()
normalized_data = normalizer(data)
# Mostrar
print("Vector original (primeras 5 filas):")
for row in data[:5]:
    print(row)
print("\nVector normalizado (primeras 5 filas):")
for row in normalized_data[:5]:
    print(row)

#Ej 4 - Codificar
from Orange.data import Table
from Orange.preprocess import Continuize
data = Table("titanic")
# Crear un objeto Continuize para realizar el One-Hot Encoding
# Continuize convierte datos categoricos en numericos
continuizer = Continuize(multinomial_treatment=Continuize.Indicators)
data2 = continuizer(data)
# Mostrar los resultados
print("Datos originales (primera fila):", data.domain)
print("Datos codificados (primera fila):", data[0])
print("Datos originales (primera fila):", data2.domain)
print("Datos codificados (primera fila):", data2[0])

#Ej 5 - Segmentar 
import numpy as np
from Orange.data import Table, Domain, DiscreteVariable
data = Table("titanic")
print("Atributos originales:", data.domain)
# Extraer la columna "age"
ages = np.array([row["age"] for row in data], dtype=float)
# Eliminar valores faltantes antes de segmentar y filtrar valores no NaN para calcular bins
ages_no_nan = ages[~np.isnan(ages)]  
# Definir rangos de segmentación (3 segmentos iguales)
# 3 segmentos → 4 límites
bins = np.linspace(np.min(ages_no_nan), np.max(ages_no_nan), 4) 
labels = ["Low", "Medium", "High"]  

# Discretizar los valores de "age" usando NumPy
digitized_indices = np.digitize(ages, bins, right=False) - 1  
# Convertir índices a categorías
# Lista por compresión
segmented_ages = [
    labels[i] if not np.isnan(ages[idx]) and i < len(labels) else "Unknown"
    for idx, i in enumerate(digitized_indices)
]
# Crear un nuevo atributo discreto para "age"
new_age_var = DiscreteVariable("age_segmented", values=labels + ["Unknown"])
# Crear un nuevo dominio con el atributo segmentado
new_attributes = []
for attr in data.domain.attributes:
    if attr.name == "age":
        # Reemplazar "age" con la versión segmentada
        new_attributes.append(new_age_var)  
    else:
        new_attributes.append(attr)
new_domain = Domain(new_attributes, data.domain.class_vars)
# Crear una nueva tabla con los datos segmentados
segmented_data = Table.from_table(new_domain, data)
# Reemplazar los valores de "age" en el dataset con los segmentados
for idx, row in enumerate(segmented_data):
    row["age_segmented"] = segmented_ages[idx]
# Mostrar resultados
print("\nValores originales de 'age' (primeras 5 filas):")
print(ages[:5])
print("\nSegmentos definidos:")
print(bins)
print("\nValores segmentados de 'age' (primeras 5 filas):")
print(segmented_ages[:5])
print("\nDatos originales (primeras 5 filas):")
for row in data[:5]:
    print(row)
print("\nDatos segmentados (primeras 5 filas):")
for row in segmented_data[:5]:
    print(row)

#Ej 6 - Dividir
from Orange.data import Table
from sklearn.model_selection import train_test_split
data = Table("titanic")
# Dividir datos (70% entrenamiento, 15% validación, 15% prueba)
# 70% entrenamiento
train, temp = train_test_split(data, test_size=0.3, random_state=42)  
# 15% validación y 15% prueba
validation, test = train_test_split(temp, test_size=0.5, random_state=42) 
# Mostrar el tamaño de los subconjuntos
print("Tamaño del conjunto de entrenamiento:", len(train))
print("Tamaño del conjunto de validación:", len(validation))
print("Tamaño del conjunto de prueba:", len(test))

#------------------Otros ejemplos-------------------
#Ej 7 - Transformación logarítmica
import numpy as np
# Vector aleatorio
random_vector = np.random.uniform(low=0.1, high=10.0, size=10)
# Mostrar
print("Vector original:")
print(random_vector)
# Aplicar transformación logarítmica
log_vector = np.log(random_vector)
# Mostrar el vector transformado
print("\nVector transformado (logarítmico):")
print(log_vector)

#Ej 8 - Filtrado por clase
from Orange.data import Table
data = Table("titanic")
# Filtrar instancias donde la clase sea 'survived'
filtered_data = [row for row in data if row.get_class() == "yes"]
# Mostrar 
print("Instancias filtradas (primeras 5 filas):")
for row in filtered_data[:5]:
    print(row)