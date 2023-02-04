# -*- coding: utf-8 -*-
"""Importar librería socket"""
import socket
"""Del ejemplo I, cree el Socket"""
Nombre_Socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
IP_Servidor = "127.0.0.1"
puerto = 1234
Nombre_Socket.bind((IP_Servidor, puerto))
clientes = 1
Nombre_Socket.listen(clientes)

"""Definir el tiempo de espera de la recepción en el socket"""
ID_Socket_Cliente, direccion = Nombre_Socket.accept()
ID_Socket_Cliente.settimeout(5.0)

"""El timeout y la función de recepción se pueden definir tanto en el
cliente como en el servidor"""
"""Cada cliente puede tener su propio timeout"""

while True:  
    """Está estructura permite la ejecución de la aplicación    
    asi no hayan llegado mensajes""" 
    try:    
        bytes_a_recibir = 1024
        mensaje_recibido = ID_Socket_Cliente.recv(bytes_a_recibir)
    except socket.timeout:
        mensaje_recibido = b'No llegaron mensajes' 
        """El resto de la recepción puede funcionar convencionalmente"""
    texto = mensaje_recibido.decode("utf-8")
    if texto == 'cerrar':
        break
    else:
        print (str(direccion) + " envio: ", texto)
print ('Termino la aplicación')
"""Cerrar instancias del socket"""
ID_Socket_Cliente.close()
Nombre_Socket.close()


