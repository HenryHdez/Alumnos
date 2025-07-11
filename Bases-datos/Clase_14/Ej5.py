from pymongo import MongoClient
import pandas as pd

# Conexión a MongoDB
client = MongoClient("mongodb://localhost:27017/")
db = client["tienda"]
coleccion = db["inventario"]

# Obtener todos los documentos como lista
documentos = list(coleccion.find({}))

# Convertir a DataFrame
df = pd.DataFrame(documentos)

# Ver las primeras filas
print("Primeras filas del DataFrame:")
print(df.head())

# Eliminar columnas no necesarias (_id)
df = df.drop(columns=["_id"], errors="ignore")

# Agregar columna de valor total
df["valor_total"] = df["cantidad"] * df["precio_unitario"]

# Agrupar por 'origen' y calcular suma y promedio del valor_total
agrupado = df.groupby("origen").agg(
    total_frutas=("cantidad", "sum"),
    valor_total=("valor_total", "sum"),
    valor_promedio=("valor_total", "mean")
).reset_index()

print("\n Agrupación por origen:")
print(agrupado)

# Filtrar frutas con precio mayor a 600
print("\nFrutas con precio_unitario > 600:")
print(df[df["precio_unitario"] > 600])

# Exportar a Excel 
agrupado.to_excel("Inventario.xlsx", index=False)
