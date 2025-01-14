import matplotlib.pyplot as plt
import numpy as np
import time
if __name__=="__main__":
    #Valores de x e y
    x = np.linspace(0, 10, 100)
    y = np.sin(x)
    plt.ion()                         # gráfica asi un bucle este en ejecución
    figure, ax = plt.subplots()
    linea1, = ax.plot(x, y, 'bo')
    ax.plot(x, y, 'k')
    for i in range(len(x)):
        # Nuevos valores de x e y
        new_y = np.zeros(len(x))
        new_y[i] = y[i]
        linea1.set_xdata(x)           # Actualizar x
        linea1.set_ydata(new_y)       # Actualizar y
        figure.canvas.draw()          # Dibujar valores actualizados
        figure.canvas.flush_events()  #Vaciar buffer
        time.sleep(0.1)


        