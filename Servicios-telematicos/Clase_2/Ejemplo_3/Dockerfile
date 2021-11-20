FROM node:16
#Crear directorio para la aplicación
WORKDIR /usr/src/app
#Importar el archivo json del proyecto
COPY package*.json ./
#Instalar complementos del archivo
RUN npm install
#Copiar todos los archivos del proyecto
COPY . .
#Publicar puerto
EXPOSE 5000
CMD [ "node", "Servidor.js" ]
