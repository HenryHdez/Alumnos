# Usa la imagen oficial de Neo4j
FROM neo4j:latest

# Establece la contraseña por defecto de Neo4j
#Usuario por defecto: neo4j
#Contraseña: contrasena123
ENV NEO4J_AUTH=neo4j/contrasena123

# (Opcional) Instala plugins o realiza configuraciones adicionales
# COPY plugins/* /plugins/

# Exponer los puertos para el protocolo Bolt y la interfaz web
EXPOSE 7474 7687

# El punto de entrada y comando por defecto ya están configurados en la imagen de Neo4j,
# por lo que no es necesario especificarlos aquí.

#docker build -t neo4jimg .
#docker run -p 7474:7474 -p 7687:7687 -d neo4jimg

