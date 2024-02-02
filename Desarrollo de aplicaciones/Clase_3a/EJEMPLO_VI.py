# -*- coding: utf-8 -*-
'''Ejemplo de Hilo 1'''
'''Importar las librerias correspondientes'''
import threading
import time
def funcion_hilo_1():
    print ("\n Hilo 1 en ejecución")  
    time.sleep(4)
    print ("\n Fin del hilo 1")

def funcion_hilo_2():
    print ("\n Hilo 2 en ejecución")
    time.sleep(4)
    print ("\n Fin del hilo 2")

'''Función principal'''
if __name__ == "__main__":
    """Creación de un hilo 1 y asignación de su rutina de trabajo"""
    Hilo_1=threading.Thread(target=funcion_hilo_1)
    Hilo_1.start()
    """Creación de un hilo 2 y asignación de su rutina de trabajo"""
    Hilo_2=threading.Thread(target=funcion_hilo_2)
    Hilo_2.start()

