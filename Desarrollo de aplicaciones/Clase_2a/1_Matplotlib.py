import matplotlib.pyplot as plt
import numpy as np

if __name__=="__main__":
    #np.linspace retorna un intervalo de números
    #(inicio, fin, cantidad de valores)
    x = np.linspace(0, 2 * np.pi, 200)
    y = np.tan(x)
    #subplots crea un conjunto de gráficas y
    #una figura para presentar
    fig, ax = plt.subplots()
    #Graficar
    ax.plot(x, y)
    #Cuadricula encendida
    ax.grid(True)
    #Etiqueta en X
    ax.set_xlabel("Tiempo")
    #Etiqueta en Y 
    ax.set_ylabel("Amplitud")
    #Presentar en pantalla
    plt.show()
    
    