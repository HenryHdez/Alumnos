# -*- coding: utf-8 -*-
"""Ejemplo de temporizador 1"""
"""Importe libreria de ejecución de hilos"""
import threading
"""Defina la función que se va a asociar al temporizador"""
def Tempo_1():
    global bandera 
    print("\n Se activo el temporizador")
    bandera=False

"""Función principal"""
if __name__ == "__main__":
    global bandera
    bandera=True
    Tiempo_de_activacion=2.0
    t1 = threading.Timer(Tiempo_de_activacion, Tempo_1)
    t1.start()
    while(bandera):    
        print("Mientras no se active el temporizador haga esto")
    print("\n Fin de la aplicación")
