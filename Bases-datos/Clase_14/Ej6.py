import pandas as pd

# Crear el DataFrame
df = pd.DataFrame([
    {"nombre": "Manzana", "cantidad": 50, "precio_unitario": 500, "origen": "Boyacá"},
    {"nombre": "Banano", "cantidad": 100, "precio_unitario": 200, "origen": "Urabá"},
    {"nombre": "Piña", "cantidad": 30, "precio_unitario": 1000, "origen": "Meta"},
    {"nombre": "Mango", "cantidad": 80, "precio_unitario": 600, "origen": "Tolima"},
    {"nombre": "Manzana", "cantidad": 20, "precio_unitario": 550, "origen": "Cundinamarca"}
])

# Agregar columna 'valor_total'
df["valor_total"] = df["cantidad"] * df["precio_unitario"]

# Mostrar estructura y primeras filas
print(" Primeras filas del DataFrame:")
print(df.head(), "\n")

print("Información general:")
print(df.info(), "\n")

# Filtrar frutas con precio > 500
filtro_precio = df[df["precio_unitario"] > 500]
print("Frutas con precio_unitario > 500:")
print(filtro_precio, "\n")

# Agrupar por 'origen' y sumar 'cantidad'
# reset.index() Convierte el índice actual en una columna normal
agrupado_origen = df.groupby("origen")["cantidad"].sum().reset_index()
print(" Total de frutas por origen:")
print(agrupado_origen, "\n")

# Promedio de precio por fruta
promedio_precio = df.groupby("nombre")["precio_unitario"].mean().reset_index()
print(" Precio promedio por fruta:")
print(promedio_precio, "\n")

# Ordenar por valor_total 
ordenado = df.sort_values(by="valor_total", ascending=False)
print(" Frutas ordenadas por valor_total:")
print(ordenado[["nombre", "valor_total"]], "\n")

# Aumentar precio de Manzanas en 10%
df.loc[df["nombre"] == "Manzana", "precio_unitario"] *= 1.10
print(" Precio de Manzanas ajustado en un 10%:")
print(df[df["nombre"] == "Manzana"], "\n")

# Eliminar columna 'origen'
df = df.drop(columns=["origen"])
print(" DataFrame sin columna 'origen':")
print(df.head(), "\n")