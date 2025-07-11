from pymongo import MongoClient

# Conectar a MongoDB
client = MongoClient("mongodb://localhost:27017/")
db = client["empresa"]
coleccion = db["empleados"]

# Insertar varios documentos
empleados = [
    {"nombre": "Ana", "edad": 30, "cargo": "Ingeniera", "ciudad": "Bogotá"},
    {"nombre": "Luis", "edad": 40, "cargo": "Gerente", "ciudad": "Medellín"},
    {"nombre": "Laura", "edad": 25, "cargo": "Diseñadora", "ciudad": "Bogotá"},
    {"nombre": "Carlos", "edad": 35, "cargo": "Ingeniero", "ciudad": "Cali"},
    {"nombre": "Marta", "edad": 45, "cargo": "Contadora", "ciudad": "Bogotá"}
]
coleccion.insert_many(empleados)
print("Documentos insertados.")

# Buscar todos los empleados de Bogotá
print("\nEmpleados en Bogotá:")
for doc in coleccion.find({"ciudad": "Bogotá"}):
    print(doc)

# Actualizar cargo de todos los de Bogotá a "Analista"
coleccion.update_many(
    {"ciudad": "Bogotá"},
    {"$set": {"cargo": "Analista"}}
)
print("\nCargos actualizados para empleados de Bogotá.")

# Eliminar todos los empleados mayores de 40 años
resultado = coleccion.delete_many({"edad": {"$gt": 40}})
print(f"\n{resultado.deleted_count} empleados eliminados con edad > 40")

# Ver todos los documentos
print("\nEmpleados restantes:")
for doc in coleccion.find():
    print(doc)
