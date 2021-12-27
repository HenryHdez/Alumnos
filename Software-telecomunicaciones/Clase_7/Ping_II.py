# Importar libreria scapy
# sr1 es una funci�n que env�a un paquete a la direcci�n indicada.
# ICMP es el protocolo seleccionado
# IP es la direcci�n
from scapy.all import sr1,IP,ICMP
# Definir la direcci�n de prueba o del dispositivo
Direccion_IP="10.28.0.1"
# Direccion_IP="10.28.0.1"
# Llamado a la funci�n sr1, timeout es un tiempo maximo de espera
informacion_recibida=sr1(IP(dst=Direccion_IP)/ICMP(),timeout=2)
#La funci�n show permite visualizar los datos recibidos 
informacion_recibida.show()


