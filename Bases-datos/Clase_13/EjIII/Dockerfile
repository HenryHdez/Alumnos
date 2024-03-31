FROM python:3.9-slim

# Establecer el directorio de trabajo
WORKDIR /app

# Copiar los archivos del proyecto al contenedor
COPY . .

# Instalar las dependencias de Python
RUN pip install neo4j

# Ejecutar el script de Python cuando se inicie el contenedor
CMD ["python", "EjIV.py"]

#docker build -t db4img .
#docker run db4img