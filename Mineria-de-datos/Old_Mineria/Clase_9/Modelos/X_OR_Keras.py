#Importe las librerías
import numpy as np
from keras.models import Sequential
from keras.layers.core import Dense
 
# Cree las entradas X
X = np.array([[0,0],[0,1],[1,0],[1,1]])
 
# Cree la salida esperada y
y = np.array([[0],[1],[1],[0]])

#Defina la red neuronal
Modelo = Sequential()
#Defina la cantidad de neuronas de la capa oculta
#Defina la cantidad de elementos de entrada
#Defina la función de activación
Modelo.add(Dense(16, input_dim=2, activation='relu'))
#Defina la cantidad de elementos esperado y la función de activación
Modelo.add(Dense(1, activation='sigmoid'))

#Defina:
#La función para el calculo del error
#La función de optimización de los pesos
#La metrica para estimarla diferencia entre lo esperado y lo obtenido
Modelo.compile(loss='mean_squared_error',
              optimizer='adam',
              metrics=['binary_accuracy'])

#Entrene el Modelo
Modelo.fit(X, y, epochs=1000)
 
#Evalue el rendimiento del Modeloo
scores = Modelo.evaluate(X, y)

#Imprima el margen de error del Modeloo
print("\n%s: %.2f%%" % (Modelo.metrics_names[1], scores[1]*100))
#Muestre el valor predecido por el Modeloo
print (Modelo.predict(X).round())


