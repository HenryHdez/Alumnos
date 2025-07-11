from pymongo import MongoClient
from datetime import datetime, timedelta

# Conexión a MongoDB (supone que Mongo está en localhost:27017)
client = MongoClient("mongodb://localhost:27017/")
db = client["empresa"]
empleados = db["empleados"]
departamentos = db["departamentos"]

# Limpieza previa (opcional)
empleados.delete_many({})       #{}: Borrar todo
departamentos.delete_many({})

# Insertar documentos en 'departamentos'
departamentos.insert_many([
    {"_id": 100, "nombre_dep": "Ingeniería"},
    {"_id": 200, "nombre_dep": "Administración"},
    {"_id": 300, "nombre_dep": "Diseño"}
])

# Insertar documentos en 'empleados'
empleados.insert_many([
    {"nombre": "Ana", "edad": 30, "ciudad": "Bogotá", "departamento_id": 100, "fecha_ingreso": datetime(2024, 12, 1)},
    {"nombre": "Luis", "edad": 45, "ciudad": "Medellín", "departamento_id": 200, "fecha_ingreso": datetime(2024, 12, 15)},
    {"nombre": "Laura", "edad": 29, "ciudad": "Cali", "departamento_id": 300, "fecha_ingreso": datetime(2024, 12, 10)},
    {"nombre": "Carlos", "edad": 50, "ciudad": "Bogotá", "departamento_id": 100, "fecha_ingreso": datetime.now()}
])

# Crear índice en 'ciudad' para acelerar búsquedas
empleados.create_index("ciudad")

# Búsqueda con filtro por fecha: empleados que ingresaron en los últimos 30 días
print("Empleados ingresados en los últimos 30 días:")
hace_30_dias = datetime.now() - timedelta(days=30)
for doc in empleados.find({"fecha_ingreso": {"$gte": hace_30_dias}}):
    print(doc)

# Relación entre empleados y departamentos usando $lookup
# $lookup es un comando de que permite hacer un JOIN como en SQL
print("\nEmpleados con nombre del departamento:")
pipeline = [
    {
        "$lookup": {
            "from": "departamentos",               # Nombre de la colección a unir
            "localField": "departamento_id",       # Campo de la colección actual
            "foreignField": "_id",                 # Campo de la colección externa
            "as": "detalle_departamento"           # Resultado
        }
    },
    {"$unwind": "$detalle_departamento"}           # Convertir el resultado en un documento único
]

for doc in empleados.aggregate(pipeline):
    print({
        "nombre": doc["nombre"],
        "departamento": doc["detalle_departamento"]["nombre_dep"],
        "ciudad": doc["ciudad"]
    })

# Actualización masiva
empleados.update_many(
    {"ciudad": "Medellín"},
    {"$set": {"ciudad": "Envigado"}}
)

# Eliminación masiva
resultado = empleados.delete_many({"edad": {"$gt": 45}})
print(f"\n Empleados eliminados con edad > 45: {resultado.deleted_count}")

# Visualizar colección final
print("\n Consulta final: ")
for doc in empleados.find():
    print(doc)