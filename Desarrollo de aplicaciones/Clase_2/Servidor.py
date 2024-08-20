# -*- coding: utf-8 -*-
import socket

Nombre_Socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
IP_Servidor = "127.0.0.1"
Puerto=1234
Nombre_Socket.bind((IP_Servidor, Puerto))
Nombre_Socket.listen(1)
ID_Socket_Cliente, direccion = Nombre_Socket.accept()
print('Esperando...')
while True:
    print("Espere un mensaje")
    bytes_a_recibir = 1024
    mensaje_recibido = ID_Socket_Cliente.recv(bytes_a_recibir)
    texto = mensaje_recibido.decode("utf8")
    if texto == 'cerrar':
        break 
    else:
        print (str(direccion) + "envio: ", texto)   
print ('Termino la aplicación')

ID_Socket_Cliente.close()
Nombre_Socket.close()