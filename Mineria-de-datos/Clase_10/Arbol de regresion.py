import numpy as np 
import matplotlib.pyplot as plt
# árbol de decisión para regresión
from sklearn.tree import DecisionTreeRegressor 
from sklearn.model_selection import train_test_split
from sklearn.tree import plot_tree

#función y = 0.1x^2 + 0.2(Ruido Gaussiano) para generar los valores de y
def f(x):
    y = 0.1*np.square(x) + 0.2*np.random.randn(x.size)
    return y

if __name__ == "__main__":
    np.random.seed(42)
    # Genere los datos de x e y
    x = np.arange(-2,2,0.1) # x = [-2, -1.9, -1.8, ... 1.8, 1.9, 2]
    y = f(x) 
    # Cree el arbol de desición
    # max_depth = Cantidad de nodos del arbol
    # random_state = Fijar la semilla del generador de números aleatorios
    Arbol = DecisionTreeRegressor(max_depth=2, random_state=42) 
    # Cree los datos de prueba y entrenamiento
    xt, xp, yt, yp = train_test_split(x, y, train_size=0.75)
    #Transformación de los vectores de (dimension,) a 1D
    x_entrenamiento=xt.reshape(-1,1)
    y_entrenamiento=yt.reshape(-1,1)
    x_prueba=xp.reshape(-1,1)
    y_prueba=yp.reshape(-1,1)
    # Entrene el árbol
    Arbol.fit(x_entrenamiento, y_entrenamiento) 
    print(x_prueba) 
    a=Arbol.predict(x_prueba)
    print(Arbol.predict(x_prueba))   
    # Presente una descripción del arbol
    fig, ax = plt.subplots(figsize=(13, 6))
    print(f"Profundidad del árbol: {Arbol.get_depth()}")
    print(f"Número de nodos terminales: {Arbol.get_n_leaves()}")
    plot = plot_tree(
                decision_tree = Arbol,
                class_names   = 'Ejemplo_1',
                filled        = True,
                impurity      = False,
                fontsize      = 7,
                ax            = ax
           )
    
    
    