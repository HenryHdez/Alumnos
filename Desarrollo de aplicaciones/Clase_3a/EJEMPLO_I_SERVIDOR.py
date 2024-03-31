# -*- coding: utf-8 -*-
"""Importar librería socket"""
import socket
"""Crear una variable que almacena al socket"""
Nombre_Socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
"""socket.AF_INET: Es el dominio del conector. En este caso,
un conector IPv4"""
"""socket.SOCK_STREAM: Envia los paquetes en orden"""

"""La función bind() crea un oyente que espera la conexión al servidor"""
IP_Servidor = "127.0.0.1"
Puerto=1234
Nombre_Socket.bind((IP_Servidor, Puerto))

"""Listen designa el numero de conexiones posibles que puede
aceptar el servidor"""
Clientes = 1
Nombre_Socket.listen(Clientes)
"""La función .accep() crea dos objetos. En este caso la variable
ID_Socket_Cliente almacena la información que llega y drección es
una lista de los clientes conectados"""
ID_Socket_Cliente, direccion = Nombre_Socket.accept()


while True:
    """La función .recv() espera hasta que llegue un mensaje"""
    bytes_a_recibir = 1024
    mensaje_recibido = ID_Socket_Cliente.recv(bytes_a_recibir)
    """La instrucción decode permite realizar un cambio de formato
    (bytes-str)"""
    texto = mensaje_recibido.decode("utf8")
    """Pregunta si el tecto que llega es cerrar para terminar la 
    comunicación"""
    if texto == 'cerrar':
        break 
    else:
        print (str(direccion) + "envio: ", texto)   
    """Enviar mensaje al cliente"""
    Mensaje_Envio="Enviado"
    ID_Socket_Cliente.send(Mensaje_Envio.encode())
print ('Termino la aplicación')

"""Cerrar instancias del socket"""
ID_Socket_Cliente.close()
Nombre_Socket.close()
