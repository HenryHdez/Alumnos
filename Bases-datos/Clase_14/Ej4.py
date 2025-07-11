from pymongo import MongoClient

# Conexión a MongoDB
client = MongoClient("mongodb://localhost:27017/")
db = client["tienda"]
inventario = db["inventario"]

# Limpiar la colección (opcional para pruebas)
inventario.delete_many({})

# Insertar documentos
inventario.insert_many([
    { "nombre": "Manzana", "categoria": "Fruta", "cantidad": 50, "precio_unitario": 500, "origen": "Boyacá" },
    { "nombre": "Banano", "categoria": "Fruta", "cantidad": 100, "precio_unitario": 200, "origen": "Urabá" },
    { "nombre": "Piña", "categoria": "Fruta", "cantidad": 30, "precio_unitario": 1000, "origen": "Meta" },
    { "nombre": "Mango", "categoria": "Fruta", "cantidad": 80, "precio_unitario": 600, "origen": "Tolima" },
    { "nombre": "Manzana", "categoria": "Fruta", "cantidad": 20, "precio_unitario": 550, "origen": "Cundinamarca" }
])

# Agrupar por nombre y sumar cantidad total
print("\n Cantidad total por fruta:")
pipeline = [
    { "$group": { "_id": "$nombre", "cantidad_total": { "$sum": "$cantidad" } } }
]
for doc in inventario.aggregate(pipeline):
    print(doc)

# Agrupar por origen y calcular valor total
print("\ Valor total por origen:")
# {Origen incluye el campo tan como es, y guarda el resultado en valor total}
# {Agrupa todos los documentos por origen}
pipeline = [
    { "$project": { "origen": 1, "valor_total": { "$multiply": ["$cantidad", "$precio_unitario"] } } },
    { "$group": { "_id": "$origen", "valor_total_origen": { "$sum": "$valor_total" } } }
]
for doc in inventario.aggregate(pipeline):
    print(doc)

# Frutas con precio_unitario > 500 ordenadas descendente
print("\n Frutas con precio_unitario > 500:")
pipeline = [
    { "$match": { "precio_unitario": { "$gt": 500 } } }, #Primero este
    { "$sort": { "precio_unitario": -1 } }               #Luego este
]
for doc in inventario.aggregate(pipeline):
    print(doc)

# Mostrar nombre, cantidad y valor_total
print("\n Frutas con valor total calculado:")
pipeline = [
    {
        "$project": {
            "_id": 0,
            "nombre": 1,
            "cantidad": 1,
            "valor_total": { "$multiply": ["$cantidad", "$precio_unitario"] }
        }
    }
]
for doc in inventario.aggregate(pipeline):
    print(doc)

# Precio promedio por fruta
print("\n Precio promedio por tipo de fruta:")
pipeline = [
    { "$group": { "_id": "$nombre", "precio_promedio": { "$avg": "$precio_unitario" } } }
]
for doc in inventario.aggregate(pipeline):
    print(doc)
