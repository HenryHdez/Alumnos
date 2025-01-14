import matplotlib.pyplot as plt
import numpy as np
if __name__=="__main__":
    Marcas=['Mazda', 'Toyota', 'Mercedez', 'FIAT']
    Cantidad_Hombres=[40, 100, 30, 55]
    Cantidad_Mujeres=[20, 150, 10, 80]
    Genero=['Hombre','Mujer']
    vector_pos = np.arange(len(Marcas))
    #Caracteristicas de las barras y gráfica
    Ancho_barra = 0.4
    fig, ax = plt.subplots()
    #Barras 1 y 2
    ax.bar(vector_pos,Cantidad_Hombres,Ancho_barra,color='blue',edgecolor='black')
    ax.bar(vector_pos+Ancho_barra,Cantidad_Mujeres,Ancho_barra,color='red',edgecolor='black')
    #Etiquetas del eje x
    ax.set_xticks(vector_pos, Marcas)
    ax.set_xlabel('Marca', fontsize=16)
    ax.set_ylabel('Vehiculos * genero', fontsize=16)
    ax.set_title('Compras de vehiculos',fontsize=18)
    #Etiquetas de la leyenda del gráfico
    ax.legend(Genero,loc=2)
    plt.show()
    
    

"""    fig, ax = plt.subplots()
    #Etiquetas, valores y colores
    Marcas   = ['Mazda', 'Toyota', 'Mercedez', 'FIAT']
    Cantidad = [40, 100, 30, 55]
    Colores = ['tab:red', 'tab:blue', 'tab:green', 'tab:orange']
    #Construir gráfico
    ax.bar(Marcas, Cantidad, color=Colores)
    ax.set_ylabel('Cantidad')
    ax.set_title('Nivel de ocupación')
    plt.show()"""
    
    