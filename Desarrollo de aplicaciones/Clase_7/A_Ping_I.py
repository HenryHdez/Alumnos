# -*- coding: utf-8 -*-
#Importar la l�bertia os (Operating System)
import os
#Asigne a una variable la direcci�n IP
#del equipo con el que desee establecer una conexi�n
IP="192.168.0.1"
#Use el comando ping
Estado=os.system("ping "+IP)
print(Estado)
#Publicar estadp del equipo
if(Estado==0):
    print ("Conexi�n exitosa")
else:
    print ("No se pud� establecer una conexi�n")

"""NOTA: El comando solo determina si el equipo est� 
conectado a la red. Es decir, si el equipo hace ping a 
una IP fuera del rango, es posible que detecte una 
conexi�n si el cable de red est� conecta"""