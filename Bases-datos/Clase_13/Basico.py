from neo4j import GraphDatabase

# Configuración de conexión
URI = "bolt://localhost:7687" 
USERNAME = "neo4j"             
PASSWORD = "contrasena123"         

# Clase para interactuar con Neo4j
class Neo4jConnection:
    def __init__(self, uri, user, password):
        self._driver = GraphDatabase.driver(uri, auth=(user, password))
    def close(self):
        self._driver.close()
    def execute_query(self, query, parameters=None):
        with self._driver.session() as session:
            result = session.run(query, parameters)
            return [record.data() for record in result]  
# Crear la conexión
conn = Neo4jConnection(URI, USERNAME, PASSWORD)

# ----------------Crear nodos y relaciones---------------------------
create_query = """
CREATE (a:Person {name: $name1, age: $age1}),
       (b:Person {name: $name2, age: $age2}),
       (a)-[:KNOWS]->(b)
"""
parameters = {"name1": "Alice", "age1": 30, "name2": "Bob", "age2": 25}
conn.execute_query(create_query, parameters)
print("Nodos y relaciones creados.")

# ----------------Consulta para Leer Nodos---------------------------
read_query = """
MATCH (p:Person)
RETURN p.name AS name, p.age AS age
"""
results = conn.execute_query(read_query)
for record in results:
    print(f"Nombre: {record['name']}, Edad: {record['age']}")

#----------------Actualizar un nodo ----------------
update_query = """
MATCH (p:Person {name: $name})
SET p.age = $new_age
RETURN p.name AS name, p.age AS age
"""
parameters = {"name": "Alice", "new_age": 35}
results = conn.execute_query(update_query, parameters)
for record in results:
    print(f"Actualizado: {record['name']} tiene ahora {record['age']} años.")

#---------------- Eliminar todos los nodos y relaciones ----------------
delete_query = """
MATCH (n)
DETACH DELETE n
"""
conn.execute_query(delete_query)
print("Todos los nodos y relaciones eliminados.")

conn.close()
