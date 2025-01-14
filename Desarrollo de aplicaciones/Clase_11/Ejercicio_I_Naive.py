from Orange.data import Table, Domain, DiscreteVariable
import numpy as np

# Crear el dataset
color = DiscreteVariable("Color", values=["Rojo", "Naranja"])
tamaño = DiscreteVariable("Tamaño", values=["6", "7", "8"])
clase = DiscreteVariable("Clase", values=["Manzana", "Naranja"])

# Datos
data_table = [
    ["Rojo", "7", "Manzana"],
    ["Naranja", "8", "Naranja"],
    ["Rojo", "6", "Manzana"],
    ["Naranja", "7", "Naranja"],
    ["Rojo", "8", "Naranja"]
]

# Crear dominio y tabla
domain = Domain([color, tamaño], clase)
data = Table(domain, data_table)

# Visualizar el dataset cargado
print("Dataset Original:")
for row in data:
    print(row)

# Calcular probabilidades previas P(Clase)
class_counts = np.bincount([row.get_class() for row in data], minlength=len(clase.values))
total_count = len(data)
priors = class_counts / total_count
print("\nProbabilidades previas P(Clase):")
for i, c in enumerate(clase.values):
    print(f"P({c}) = {priors[i]:.2f}")

# Calcular probabilidades condicionales P(Atributo | Clase)
print("\nProbabilidades Condicionales P(Atributo | Clase):")
conditional_probs = {}
for attr in domain.attributes:  # Para cada atributo
    conditional_probs[attr.name] = {}
    for class_idx, class_name in enumerate(clase.values):  # Para cada clase
        class_data = [row[attr.name] for row in data if row.get_class() == class_idx]
        value_counts = {value: class_data.count(value) for value in attr.values}
        total_class_count = sum(value_counts.values())
        conditional_probs[attr.name][class_name] = {v: count / total_class_count for v, count in value_counts.items()}

# Mostrar probabilidades condicionales
for attr, values in conditional_probs.items():
    print(f"Atributo: {attr}")
    for class_name, probs in values.items():
        print(f"  Clase {class_name}: {probs}")

# Predecir para una fruta con Color = Rojo y Tamaño = 7
query = {"Color": "Rojo", "Tamaño": "7"}
print("\nPredicción para:", query)

# Calcular P(Clase | Atributos) para cada clase
posterior_probs = []
for class_idx, class_name in enumerate(clase.values):
    likelihood = priors[class_idx]
    for attr_name, attr_value in query.items():
        likelihood *= conditional_probs[attr_name][class_name].get(attr_value, 0)
    posterior_probs.append((class_name, likelihood))

# Normalizar las probabilidades (opcional para este ejemplo, ya que solo comparamos)
total_likelihood = sum(prob for _, prob in posterior_probs)
posterior_probs = [(class_name, prob / total_likelihood) for class_name, prob in posterior_probs]

# Mostrar resultado
for class_name, prob in posterior_probs:
    print(f"P({class_name} | {query}) = {prob:.2f}")

# Predicción final
predicted_class = max(posterior_probs, key=lambda x: x[1])[0]
print(f"\nClase predicha: {predicted_class}")
