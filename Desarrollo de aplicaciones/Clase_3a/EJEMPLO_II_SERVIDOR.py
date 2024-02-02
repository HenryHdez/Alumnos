# -*- coding: utf-8 -*-
import socket
"""Cree el socket"""
Nombre_Socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
IP_Servidor = "127.0.0.1"
Puerto=1234
Nombre_Socket.bind((IP_Servidor, Puerto))

"""Esta estructura de código permite conectar más de un cliente"""
Clientes = 2
Nombre_Socket.listen(Clientes)
conexiones = 2
Lista_ID_Socket_Clientes=[]
Lista_direcciones=[]
"""donde este for anida la cantidad de clientes que se conecten"""
for conexiones in range (Clientes):
    paquete, direccion = Nombre_Socket.accept()
    Lista_ID_Socket_Clientes.append(paquete)
    Lista_direcciones.append(direccion)

while True:
    bytes_a_recibir = 1024
    conexiones = 2
    texto=' '
    """Este for escanea de manera secuencial el socket."""
    for conexiones in range (Clientes):
        mensaje_recibido = Lista_ID_Socket_Clientes[conexiones]
        mensaje_recibido = mensaje_recibido.recv(bytes_a_recibir)
        texto = mensaje_recibido.decode("utf-8") 
        print(str(Lista_direcciones[conexiones]) + " envio: ", texto)
    if (texto == 'cerrar'):
        break
print ("Termino la aplicación")

"""Cerrar instancias del socket (En este caso se realiza con un for dada 
la cantidad de clientes)"""
conexiones = 2
for conexiones in range (Clientes):
    Lista_ID_Socket_Clientes[conexiones].close()
Nombre_Socket.close()


 
