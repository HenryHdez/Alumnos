from neo4j import GraphDatabase

# Conectar a Neo4j
uri = "bolt://neo4j:7687"
user = "neo4j"
password = "test"

# Inicializar la conexión
driver = GraphDatabase.driver(uri, auth=(user, password))

def create_database(tx):
    # Crear nodos
    tx.run("CREATE (a:Person {name: 'Alice', age: 32})")
    tx.run("CREATE (b:Person {name: 'Bob', age: 45})")

    # Crear una relación
    tx.run("MATCH (a:Person {name: 'Alice'}), (b:Person {name: 'Bob'}) "
           "CREATE (a)-[r:FRIENDS_WITH]->(b)")

def print_friends(tx, name):
    result = tx.run("MATCH (a:Person)-[:FRIENDS_WITH]->(b) WHERE a.name = $name "
                    "RETURN b.name", name=name)
    for record in result:
        print(f"{name} is friends with {record['b.name']}")

with driver.session() as session:
    # Ejecutar función para crear la base de datos
    session.write_transaction(create_database)
    
    # Ejecutar función para mostrar amigos de Alice
    session.read_transaction(print_friends, 'Alice')

# Cerrar la conexión
driver.close()
