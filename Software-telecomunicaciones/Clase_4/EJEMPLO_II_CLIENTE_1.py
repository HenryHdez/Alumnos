# -*- coding: utf-8 -*-
"""Importar librer�a socket"""
import socket

"""Crear una variable que almacena al socket"""
Nombre_Socket = socket.socket()

"""Llamar al metodo connect para establecer una 
conexi�n con el servidor. Teniendo en cuenta que
tiene dos par�metros la direcci�n IP y el puerto"""
IP_Servidor='127.0.0.1'
Puerto=1234

"""Est� estructura intenta establecer una conexi�n"""
try:
    Bandera=True
    Nombre_Socket.connect((IP_Servidor, Puerto))
except ConnectionRefusedError:
    Bandera=False 
    print('Intente conectarse al servidor nuevamente')

"""En este caso la estructra while mantiene la conexi�n"""
while Bandera:
    """Solicitud del mensaje a enviar"""
    texto = input("Mensaje a enviar >> ")
    """Cambio de formato del paquete a enviar (str-byte)"""
    paquete = texto.encode()
    """Intente enviar un paquete si no termine la conexi�n"""
    try:
       Nombre_Socket.send(paquete)
       if(texto=='cerrar'):
           break
    except ConnectionResetError:
        break
print('Termino la aplicaci�n')
"""Cerrar el socket"""
Nombre_Socket.close()
