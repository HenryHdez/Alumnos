# Importar libreria scapy
# sr1 es una función que envía un paquete a la dirección indicada.
# ICMP es el protocolo seleccionado
# IP es la dirección
from scapy.all import sr1,IP,ICMP
# Definir la dirección de prueba o del dispositivo
Direccion_IP="10.28.0.1"
# Direccion_IP="10.28.0.1"
# Llamado a la función sr1, timeout es un tiempo maximo de espera
informacion_recibida=sr1(IP(dst=Direccion_IP)/ICMP(),timeout=2)
#La función show permite visualizar los datos recibidos 
informacion_recibida.show()


