#-*- coding: utf-8 -*-
"""Importar libreria socket"""
import socket
Nombre_Socket = socket.socket()
IP_Servidor='127.0.0.1'
Puerto=1234

try:
    Bandera=True
    Nombre_Socket.connect((IP_Servidor, Puerto))
except ConnectionRefusedError:
    Bandera=False 
    print('Intente conectarse al servidor nuevamente')

while Bandera:
    texto = input("Mensaje a enviar >> ")
    paquete = texto.encode()
    try:
       Nombre_Socket.send(paquete)
       if(texto=='cerrar'):
           break
    except ConnectionResetError:
        break
print('Termino la aplicación')
Nombre_Socket.close()
