# -*- coding: utf-8 -*-
"""Importar librer�a socket"""
import socket
"""Crear una variable que almacena al socket"""
Nombre_Socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
"""socket.AF_INET: Es el dominio del conector. En este caso,
un conector IPv4"""
"""socket.SOCK_STREAM: Envia los paquetes en orden"""

"""La funci�n bind() crea un oyente que espera la conexi�n al servidor"""
IP_Servidor = "127.0.0.1"
Puerto=1234
Nombre_Socket.bind((IP_Servidor, Puerto))

"""Listen designa el numero de conexiones posibles que puede
aceptar el servidor"""
Clientes = 2
Nombre_Socket.listen(Clientes)
"""La funci�n .accep() crea dos objetos. En este caso la variable
ID_Socket_Cliente almacena la informaci�n que llega y drecci�n es
una lista de los clientes conectados"""
ID_Socket_Cliente, direccion = Nombre_Socket.accept()


while True:
    """La funci�n .recv() espera hasta que llegue un mensaje"""
    bytes_a_recibir = 1024
    mensaje_recibido = ID_Socket_Cliente.recv(bytes_a_recibir)
    """La instrucci�n decode permite realizar un cambio de formato
    (bytes-str)"""
    texto = mensaje_recibido.decode("utf8")
    """Pregunta si el tecto que llega es cerrar para terminar la 
    comunicac�n"""
    if texto == 'cerrar':
        break 
    else:
        print (str(direccion) + "envio: ", texto)   

print ('Termino la aplicaci�n')

"""Cerrar instancias del socket"""
ID_Socket_Cliente.close()
Nombre_Socket.close()
