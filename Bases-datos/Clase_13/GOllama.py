from neo4j import GraphDatabase
from sklearn.datasets import load_iris
import pandas as pd
import ollama

# 1. Configuración
NEO4J_URI = "bolt://localhost:7687"
NEO4J_USER = "neo4j"
NEO4J_PASSWORD = "contrasena123"   
OLLAMA_MODEL = "llama3.2"

driver = GraphDatabase.driver(
    NEO4J_URI,
    auth=(NEO4J_USER, NEO4J_PASSWORD)
)

# 2. Cargar dataset Iris
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

print("Dataset cargado:")
print(df.head())

# ============================================================
# 3. Limpiar base de datos Neo4j
# ============================================================

with driver.session() as session:
    session.run("""
    MATCH (n)
    DETACH DELETE n
    """)

print("\nBase de datos Neo4j limpiada.")

# 4. Crear restricciones e índices
with driver.session() as session:
    session.run("""
    CREATE CONSTRAINT species_name_unique IF NOT EXISTS
    FOR (s:Species)
    REQUIRE s.name IS UNIQUE
    """)

print("Restricción creada para Species.")


# 5. Insertar datos en Neo4j usando Cypher desde Python
rows = df.to_dict("records")

query_insert = """
UNWIND $rows AS row

CREATE (f:Flower {
    sepal_length: row.sepal_length,
    sepal_width: row.sepal_width,
    petal_length: row.petal_length,
    petal_width: row.petal_width
})

MERGE (s:Species {name: row.species})

CREATE (f)-[:BELONGS_TO]->(s)
"""

with driver.session() as session:
    session.run(query_insert, rows=rows)

print("\nDatos insertados en Neo4j.")

# 6. Consultar estadísticas desde Neo4j

query_stats = """
MATCH (f:Flower)-[:BELONGS_TO]->(s:Species)
RETURN
    s.name AS species,
    count(f) AS total_samples,
    round(avg(f.sepal_length), 3) AS avg_sepal_length,
    round(avg(f.sepal_width), 3) AS avg_sepal_width,
    round(avg(f.petal_length), 3) AS avg_petal_length,
    round(avg(f.petal_width), 3) AS avg_petal_width,
    round(min(f.petal_length), 3) AS min_petal_length,
    round(max(f.petal_length), 3) AS max_petal_length
ORDER BY species
"""

with driver.session() as session:
    result = session.run(query_stats)
    stats = [record.data() for record in result]

print("\nEstadísticas consultadas desde Neo4j:")
for row in stats:
    print(row)


# 7. Consulta adicional: especies con pétalos más grandes
query_petal = """
MATCH (f:Flower)-[:BELONGS_TO]->(s:Species)
RETURN
    s.name AS species,
    round(avg(f.petal_length), 3) AS avg_petal_length,
    round(avg(f.petal_width), 3) AS avg_petal_width
ORDER BY avg_petal_length DESC
"""

with driver.session() as session:
    result = session.run(query_petal)
    petal_stats = [record.data() for record in result]

print("\nPromedios de pétalo:")
for row in petal_stats:
    print(row)


# 8. Interpretar resultados con Ollama
prompt = f"""
Se cargó el dataset Iris en una base de datos Neo4j.

Modelo del grafo:
- Nodo Flower: representa una flor medida.
- Nodo Species: representa la especie.
- Relación BELONGS_TO: conecta cada flor con su especie.

Estadísticas obtenidas desde Neo4j:

{stats}

Promedios de pétalo:

{petal_stats}

Realiza una interpretación técnica en español.

Incluye:
1. Diferencias principales entre especies.
2. Variables que mejor separan las especies.
3. Interpretación del uso de Neo4j para representar este dataset.
4. Conclusión breve.
"""

response = ollama.chat(
    model=OLLAMA_MODEL,
    messages=[
        {"role": "user", "content": prompt}
    ]
)

print("\nInterpretación generada por Ollama:")
print(response["message"]["content"])

# 9. Cerrar conexión
driver.close()