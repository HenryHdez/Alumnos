"""GRADIENTE DESCENDENTE
Es un algoritmo de optimización que permite encontrar el mínimo de una función. 
Utiliza el gradiente (generalización multivariable de la derivada) de la función 
para acercarse de forma progresiva al mínimo ideal de dicha función.
En el aprendizaje de máquina se utiliza para hallar los valores que deben 
tomar los parámetros del modelo para minimizar el error entre la predicción y la realidad.
Ejemplo

Un modelo de aprendizaje de máquina representa su aprendizaje mediante el parámetro w.
El error entre el valor predicho por el modelo y el valor real se puede expresar en función de w mediante la ecuación: e = w^2 + 1.
El reto es encontrar el valor de w que minimice el error e usando el gradiente descendente."""

import matplotlib.pyplot as plt
from numpy.random import randint
from numpy import linspace

w_inicial = randint(10)


n_iteraciones = 50
iteraciones = []
e = []
w = w_inicial

alpha = 0.1
# alpha es el factor que define la tasa de actualización de w a partir del gradiente (w = w - alpha*gradiente),
# debe ser un valor entre 0 y 1, si es pequeño la convergencia va a ser lenta (pero segura), si es alto se corre el riego de pasarse del mínimo.

for i in range(n_iteraciones):
    print('------------------------')
    print('iteración ', str(i+1))

    # Calcular gradiente (d(e)/dw = d(w^2 + 1)/dw = 2*w )
    gradiente = 2*w

    # Actualizar "w" usando gradiente descendente
    w = w - alpha*gradiente

    # Almacenar iteración y valor correspondiente
    e.append(w**2 + 1)
    iteraciones.append(i+1)

    # Imprimir resultados
    print('w = ', str(w), ', e = ', str(w**2+1))

plt.subplot(1,2,1)
plt.plot(iteraciones,e)
plt.xlabel('Iteración')
plt.ylabel('e')

W = linspace(-5,5,100)
E = W**2 + 1
plt.subplot(1,2,2)
plt.plot(W,E,0.0,1.0,'ro')
plt.xlabel('w')
plt.ylabel('e')

plt.show()