#FROM node:16
FROM node:10-alpine
#Crear directorio para la aplicación
WORKDIR /app
#Importar el archivo json del proyecto
COPY package.json .
#Instalar complementos del archivo
RUN npm install
#Copiar todos los archivos del proyecto
COPY . .
#Publicar aplicación
CMD [ "node", "Correo.js" ]

docker network create cualquiera
docker network ls
docker network inspect cualquiera
docker run -dit --name container3 --network cualquiera alpine ash 
