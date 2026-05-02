import pandas as pd
import numpy as np
import ollama
from sklearn.datasets import load_iris
from io import StringIO

# 1. Cargar dataset Iris limpio
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

# 2. Crear errores artificiales
df_err = df.copy()
np.random.seed(42)

numeric_cols = [
    "sepal_length",
    "sepal_width",
    "petal_length",
    "petal_width"
]

# Valores negativos
idx_neg = np.random.choice(df_err.index, size=5, replace=False)
df_err.loc[idx_neg, "sepal_length"] *= -1

# Valores extremos
idx_out = np.random.choice(df_err.index, size=5, replace=False)
df_err.loc[idx_out, "petal_length"] *= 10

# Valores faltantes
idx_nan = np.random.choice(df_err.index, size=5, replace=False)
df_err.loc[idx_nan, "sepal_width"] = np.nan

# Errores de tipo
idx_str = np.random.choice(df_err.index, size=3, replace=False)
df_err.loc[idx_str, "petal_width"] = "error"

df_err.to_csv("iris_sucio.csv", index=False)

print("\nDataset con errores guardado como iris_sucio.csv")
print(df_err.head(15))

# 3. Detectar errores con pandas
df_check = df_err.copy()

for col in numeric_cols:
    #Convierte a numero
    #"raise" → lanza error
    #"ignore" → deja el valor como está
    #"coerce" → convierte valores inválidos a NaN
    df_check[col] = pd.to_numeric(df_check[col], errors="coerce")
errores = []

for col in numeric_cols:
    reporte = f"""
Columna: {col}
Valores faltantes o no numéricos: {df_check[col].isna().sum()}
Valores negativos: {(df_check[col] < 0).sum()}
Valores extremos mayores a 10: {(df_check[col] > 10).sum()}
"""
    errores.append(reporte)

print("\nErrores detectados:")
print("\n".join(errores))

# 4. Crear resumen para Ollama
resumen_por_especie = df_check.groupby("species")[numeric_cols].mean()

prompt = f"""
Tienes un dataset Iris con errores.

Columnas:
- sepal_length
- sepal_width
- petal_length
- petal_width
- species

Errores detectados:
{chr(10).join(errores)}

Medias por especie calculadas con los datos disponibles:
{resumen_por_especie.to_string()}

Dataset completo con errores:
{df_err.to_csv(index=False)}

Tarea:
Corrige el dataset siguiendo estas reglas:
1. Devuelve únicamente el CSV corregido, sin texto adicional.
"""

# 5. Enviar solicitud a Ollama

response = ollama.chat(
    model="llama3.2",
    messages=[
        {"role": "user", "content": prompt}
    ]
)

csv_corregido = response["message"]["content"]

print("\nCSV corregido por Ollama:")
print(csv_corregido[:1000])

# 6. Convertir respuesta de Ollama a DataFrame
try:
    df_ollama = pd.read_csv(StringIO(csv_corregido))
    df_ollama.to_csv("iris_corregido_ollama.csv", index=False)

    print("\nArchivo guardado como iris_corregido_ollama.csv")
    print(df_ollama.head(15))

except Exception as e:
    print("\nNo fue posible convertir la respuesta de Ollama en DataFrame.")
    print("Error:", e)