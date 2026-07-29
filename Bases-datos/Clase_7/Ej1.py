# Crear imagen de mongo 
# docker run -d --name mongo-python -p 27017:27017 mongo:6.0

# Instalar pymongo
# pip install pymongo

from pymongo import MongoClient
# Crear enlace con el gestor de mongo
client = MongoClient("mongodb://localhost:27017/")
# Ver bases de datos existentes
print(client.list_database_names())

# Conexión al contenedor MongoDB
db = client["mi_base"]
coleccion = db["mi_coleccion"]

# Insertar documento
nuevo_doc = {
    "nombre": "Henry",
    "profesion": "Ingeniero",
    "proyecto": "Docker + MongoDB + Python"
}
coleccion.insert_one(nuevo_doc)

# Actualizar
coleccion.update_one({"nombre": "Henry"}, {"$set": {"profesion": "Docente"}})

# Buscar documentos
print("Documentos almacenados:")
for doc in coleccion.find():
    print(doc)

# Eliminar
coleccion.delete_one({"nombre": "Henry"}) 