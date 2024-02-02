import matplotlib.pyplot as plt
import numpy as np

if __name__=="__main__":
    x = np.linspace(0.0, 5.0, 501)
    #(Cantidad de filas, Cantidad de columnas)
    #Graf. 1
    fig, (ax1, ax2) = plt.subplots(2, 1)
    ax1.plot(x, np.cos(x), linestyle=(0, (1, 10)), linewidth=1.5, color='black')
    ax1.set_title('Grafico 1')
    #Graf 2.
    ax2.plot(x, np.log(x), linestyle=(0, (5, 1)), linewidth=4, color='red')
    ax2.set_title('Grafico 2')
    #Titulo de la gráfica
    fig.suptitle('2 graficas diferentes', fontsize=16)
    plt.show()
    
    