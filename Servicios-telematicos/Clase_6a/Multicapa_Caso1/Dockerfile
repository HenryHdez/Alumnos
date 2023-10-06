# Imagen de node versión 14
FROM node:14
# Directorio de trabajo
WORKDIR /usr/src/app
# Copiamos el package.json
COPY package*.json ./
# Instalar dependencias
RUN npm install
# Copiar archivos de la aplicación
COPY . .
# Exponer el puerto 5000
EXPOSE 5000
# Ejecutar el servidor
CMD ["node", "servidor.js"]
