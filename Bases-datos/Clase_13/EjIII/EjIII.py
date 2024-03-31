from neo4j import GraphDatabase

uri = "neo4j://localhost:7687"
user = "neo4j"
password = "contrasena123"

driver = GraphDatabase.driver(uri, auth=(user, password))

def print_greeting(message):
    with driver.session() as session:
        greeting = session.write_transaction(create_and_return_greeting, message)
        print(greeting)

def create_and_return_greeting(tx, message):
    result = tx.run("CREATE (a:Greeting) "
                    "SET a.message = $message "
                    "RETURN a.message + ', from the Neo4j database!' AS greeting", message=message)
    return result.single()[0]

if __name__ == "__main__":
    print_greeting("Hello, world")

driver.close()
