# -*- coding: utf-8 -*-
"""Ejemplo de temporizador 2"""
"""Importe la librería de ejecución de hilos"""
import threading

"""Defina la función que se va a asociar al temporizador"""
def Tempo_1():
    global bandera1 
    print('\n Se activo el temporizador 1')
    bandera1=False

def Tempo_n():
    global bandera2
    print('\n Se activo el temporizador n')
    bandera2=False

"""Función principal"""
if __name__=="__main__":
    global bandera1
    global bandera2    
    bandera1=True
    bandera2=True
    Tiempo_de_activacion1=2.0 
    Tiempo_de_activacion2=4.0
    t1 = threading.Timer(Tiempo_de_activacion1, Tempo_1)
    t1.start()   
    tn = threading.Timer(Tiempo_de_activacion2, Tempo_n)
    tn.start()
    while(bandera1 or bandera2):
       print("Mientras temporizadores activos")
    print('\n Fin de la aplicación')

 
    
 
