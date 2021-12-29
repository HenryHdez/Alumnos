# -*- coding: utf-8 -*-
"""
Created on Mon Jan 11 20:29:19 2021

@author: hahernandez
"""

from sklearn.neural_network import MLPClassifier
import pandas as pd
import numpy as np

#Definición de la función principal
if __name__ == '__main__':
    # Cargue el dataset
    df = pd.read_csv("iris.data", header=None)
    # Extraer las caracteristicas de interes.
    X = df.iloc[0:100, [0, 2]].values
    # Seleccionar Setosa y Versicolor.
    y = df.iloc[0:100, 4].values
    y = np.where(y == 'Iris-setosa', -1, 1)
    #Clasificador(Numero de capas, valores iniciales, función de activación)
    modelo = MLPClassifier((2, ), random_state = 0,
                           learning_rate_init = 0.1, activation = "logistic")
    modelo.fit(X, y)
    #Datos predecidos
    print(modelo.predict(X))
    #Nivel de correlación
    print(modelo.score(X, y))
    #Pesos
    print(modelo.coefs_)
    #Valor de activación
    print(modelo.intercepts_)
    
    