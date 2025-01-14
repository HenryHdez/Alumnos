#>>>>>>>>>>>>>>>>>>>>Ej-I Naive Bayes<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
from Orange.data import Domain, Table, DiscreteVariable
from Orange.classification import NaiveBayesLearner
# Definir variables
color = DiscreteVariable("Color", values=["Rojo", "Naranja"])
tamaño = DiscreteVariable("Tamaño", values=["6", "7", "8"])
clase = DiscreteVariable("Clase", values=["Manzana", "Naranja"])
# Tabla de datos
data_table = [
    ["Rojo", "7", "Manzana"],
    ["Naranja", "8", "Naranja"],
    ["Rojo", "6", "Manzana"],
    ["Naranja", "7", "Naranja"],
    ["Rojo", "8", "Naranja"]
]
# Crear dominio y tabla
dominio = Domain([color, tamaño], clase)
datos = Table(dominio, data_table)
print("Conjunto de datos original:")
for row in datos:
    print(row)
# Crear y entrenar el modelo de Naive Bayes
nb_model = NaiveBayesLearner()(datos)
# Predicción de una fruta con Color = Rojo y Tamaño = 7
X = Table(dominio, [["Rojo", "7"]])
# Devuelve el índice de la clase predicha
predicted_class_index = nb_model(X)[0]  
# Obtener el nombre de la clase
Salida = dominio.class_var.values[int(predicted_class_index)]  
# Mostrar la predicción
print("\nPredicción para [Color = Rojo, Tamaño = 7]:")
print(f"Clase predicha: {Salida}")
# Obtener las probabilidades de las clases
# ret=1 devuelve las probabilidades de las clases
probabilities = nb_model(X, ret=1)  
print("\nProbabilidades de las clases:")
for cls, prob in zip(dominio.class_var.values, probabilities[0]):
    print(f"P({cls}) = {prob:.2f}")

#>>>>>>>>>>>>>>>>>>>>Ej-II KMeans<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
from Orange.data import Domain, Table, ContinuousVariable
from Orange.clustering import KMeans
# Crear tabla
x1 = ContinuousVariable("X1")  # Eje X
x2 = ContinuousVariable("X2")  # Eje Y
domain = Domain([x1, x2])
data_table = [
    [1, 1],
    [2, 1],
    [4, 3],
    [5, 4]
]
data = Table(domain, data_table)
# Visualizar los datos originales
print("Datos Originales:")
for row in data:
    print(row)
# Aplicar K-Means con 2 clústeres
kmeans = KMeans(n_clusters=2)
clusters = kmeans(data)  # Asignar puntos a clústeres
# Mostrar los resultados
print("\nResultados de Clúster:")
for i, row in enumerate(data):
    print(f"Punto {row} -> Clúster {clusters[i]+1}")
