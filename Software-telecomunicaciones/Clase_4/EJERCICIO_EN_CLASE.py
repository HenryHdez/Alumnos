# -*- coding: utf-8 -*-
'''Ejemplo de Hilo 2'''
'''Importar las librerias correspondientes'''
import threading
import socket

"""Funciones"""
def Cliente_1():
    ID_Socket_Cliente1, direccion1 = Nombre_Socket.accept()
    while True:
        mensaje_recibidol = ID_Socket_Cliente1.recv(1024)
        texto = mensaje_recibidol.decode("utf-8")
        if texto == 'cerrar':    
            break
        else:
            print (str(direccion1) + "Cliente 1 envió: ", texto)
    print ("Terminó la comunicación con el Cliente 1")
    ID_Socket_Cliente1.close()

def Cliente_2():
    ID_Socket_Cliente2, direccion2 = Nombre_Socket.accept()
    while True: 
        mensaje_recibido2 = ID_Socket_Cliente2.recv(1024)
        texto = mensaje_recibido2.decode("utf-8")
        if texto == 'cerrar':
             break
        else:       
            print (str(direccion2) + "Cliente 2 envió: ", texto)
    print ("Terminó la comunicación con el Cliente 2")
    ID_Socket_Cliente2.close()
    
'''Función principal'''
if __name__ == "__main__":
    """Socket"""
    Nombre_Socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    IP_Servidor = "127.0.0.1"
    Puerto = 1234
    Nombre_Socket.bind((IP_Servidor, Puerto))
    Clientes = 2
    Nombre_Socket.listen(Clientes)
    """Hilos"""
    Hilo_1=threading.Thread(target=Cliente_1)
    Hilo_1.start()
    Hilo_2=threading.Thread(target=Cliente_2)
    Hilo_2.start()