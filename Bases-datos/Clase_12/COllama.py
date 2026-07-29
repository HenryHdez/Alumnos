import pandas as pd
import ollama
from sklearn.datasets import load_iris

# 1. Crear el CSV Iris
iris = load_iris(as_frame=True)
df = iris.frame

df.rename(columns={
    "sepal length (cm)": "sepal_length",
    "sepal width (cm)": "sepal_width",
    "petal length (cm)": "petal_length",
    "petal width (cm)": "petal_width",
    "target": "species"
}, inplace=True)

df["species"] = df["species"].map({
    0: "setosa",
    1: "versicolor",
    2: "virginica"
})

df.to_csv("iris.csv", index=False)

# 2. Cargar el CSV
data = pd.read_csv("iris.csv")

# 3. Análisis básico
print("Primeras filas:")
print(data.head())

print("\nInformación general:")
print(data.info())

print("\nEstadísticas descriptivas:")
print(data.describe())

print("\nPromedios por especie:")
summary = data.groupby("species").mean()
print(summary)

# 4. Preparar resumen para Ollama
prompt = f"""
Analiza el siguiente resumen estadístico del dataset Iris.

El dataset contiene medidas de sépalos y pétalos de tres especies:
setosa, versicolor y virginica.

Estadísticas por especie:

{summary.to_string()}

Explica:
1. Qué variables diferencian mejor las especies.
2. Qué patrones se observan.
3. Qué conclusiones básicas se pueden obtener.
Usa un lenguaje académico y claro.
"""

# 5. Enviar a Ollama
response = ollama.chat(
    model="tinyllama",
    messages=[
        {
            "role": "user",
            "content": prompt
        }
    ]
)

print("\nAnálisis generado por Ollama:")
print(response["message"]["content"])