# -*- coding: utf-8 -*-
#Importar la líbertia os (Operating System)
import os
#Asigne a una variable la dirección IP
#del equipo con el que desee establecer una conexión
IP="192.168.0.1"
#Use el comando ping
Estado=os.system("ping "+IP)
print(Estado)
#Publicar estadp del equipo
if(Estado==0):
    print ("Conexión exitosa")
else:
    print ("No se pudó establecer una conexión")

"""NOTA: El comando solo determina si el equipo está 
conectado a la red. Es decir, si el equipo hace ping a 
una IP fuera del rango, es posible que detecte una 
conexión si el cable de red está conecta"""