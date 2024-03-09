#PARTE 1
#Descargar imagen de Nodejs
FROM node:14 AS build
WORKDIR /app
#Copiar e instalar dependencias
COPY package*.json ./
RUN npm install
#Copiar el resto de archivos
COPY . .
#Construir la aplicación para producción
RUN npm run build
#PARTE 2
#Incoporar un servidor WEB
FROM nginx:alpine
#Corpiar versión de producción al servidor
COPY --from=build /app/build /usr/share/nginx/html
#Publicar en el puerto 80 (por defecto de nginx)
EXPOSE 80 
#Iniciar el servidor en segundo plano
CMD ["nginx", "-g", "daemon off;"]

#docker build -t pagina .
#docker run -p 3000:80 pagina