# -*- coding: utf-8 -*-
#Importar la l�beria os y time
import os
from time import time
#Asigne a una variable la direcci�n IP
#del equipo con el que se desee establecer una conexi�n
IP="192.168.0.1"

tiempo_inicio = time()
Estado=os.system("ping "+IP)
tiempo_transcurrido = time() - tiempo_inicio
print(tiempo_transcurrido)