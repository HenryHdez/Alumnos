#Sistema operativo
FROM ubuntu
#Directorio de trabajo
WORKDIR /opt/app
#Copiar todos los archivos ..
COPY .. /opt/app/ 
#Instalar pip, PYTHON y librerías
RUN apt update && apt install -y python3-pip
RUN pip3 install -r requirements.txt
#Puerto definido por el usuario
EXPOSE 5000
#Ejecución del SCRIPT en el terminal
CMD ["python3", "Ejemplo_I.py"]

