# -*- coding: utf-8 -*-
"""Importar librería socket"""
import socket

"""Crear una variable que almacena al socket"""
Nombre_Socket = socket.socket()

"""Llamar al metodo connect para establecer una 
conexión con el servidor. Teniendo en cuenta que
tiene dos parametros la direccion IP y el puerto"""
IP_Servidor='127.0.0.1'
Puerto=1234

"""Está estructura intenta establecer una conexión"""
try:
    Bandera=True
    Nombre_Socket.connect((IP_Servidor, Puerto))
except ConnectionRefusedError:
    Bandera=False 
    print('Intente conectarse al servidor nuevamente')

"""En este caso la estructra while mantiene la conexión"""
while Bandera:
    """Solicitud del mensaje a enviar"""
    texto = input("Mensaje a enviar >> ")
    """Cambio de formato del paquete a enviar (str-byte)"""
    paquete = texto.encode()
    """Intente enviar un paquete si no termine la conexión"""
    try:
       Nombre_Socket.send(paquete)
       if(texto=='cerrar'):
           break
    except ConnectionResetError:
        break
print('Termino la aplicación')
"""Cerrar el socket"""
Nombre_Socket.close()
