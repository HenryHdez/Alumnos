import numpy as np

#Defina las funciones de activación
def Fun_activacion(x):
    #Función Tangente hiperbolica
    return np.tanh(x)

def Fun_activacion_prima(x):
    #Función derivada (aproximada para simplificar el cálculo)
    return 1.0 - x**2

class Red_neuronal:
    def __init__(self, capas):
        self.activacion       = Fun_activacion
        self.activacion_prima = Fun_activacion_prima
        # Iniciar vector de pesos
        self.pesos = []
        # capas = [2,2,1]
        # Los rangos de los pesos están entre (-1,1)
        # Entrada y capas ocultas = capas - random((2+1, 2+1)) : 3 x 3
        # Este for inicializa los pesos
        for i in range(1, len(capas)-1):
            r = 2*np.random.random((capas[i-1]+1, capas[i] + 1))-1
            self.pesos.append(r)
        # Capa de salida capa - random((2+1, 1)) : 3 x 1
        r = 2*np.random.random((capas[i]+1, capas[i+1]))-1
        self.pesos.append(r)
    
    def Optimizar_pesos(self, X, y, taza_aprendizaje=0.7, actualizaciones=200000):
         # Agregue una capa de unos a X que representa el bias
         ones = np.atleast_2d(np.ones(X.shape[0]))
         X = np.concatenate((ones.T, X), axis=1)      
         #Función de entrenamiento de la red
         for k in range(actualizaciones):
             #Publica cada 1000 iteraciones
             if k % 10000 == 0: 
                 print ('Actualizaciones:', k)
             #Tomar los valores de entrada
             i = np.random.randint(X.shape[0])
             a = [X[i]]
             #Realice el producto punto entre la entrada y la función de 
             #Activación
             for l in range(len(self.pesos)):
                     producto_punto = np.dot(a[l], self.pesos[l])
                     activacion = self.activacion(producto_punto)
                     a.append(activacion)
             # Estime el valor del error esperado entre la salida deseada
             # y el valor calculado
             error = y[i] - a[-1]
             # Multiplique su resultado por la derivada de la función de 
             # activación (a[-1] es el valor de salida calculado el -1
             # indica que es el último valor de la lista)
             deltas = [error * self.activacion_prima(a[-1])]
             # Calcule el valor del error por la derivada de la función de 
             # activación (a es la capa antes de la etapa de salida)
             for l in range(len(a) - 2, 0, -1): 
                 deltas.append(deltas[-1].dot(self.pesos[l].T)*self.activacion_prima(a[l]))
             # Mueva el valor calculado a la capa correspondiente             
             deltas.reverse()
             # Algoritmo de propagación hacia atras
             # 1. multiplique delta y la función de activación 
             #    para obtener el gradiente del peso.
             # 2. Actualice los pesos de acuerdo con el gradiente 
             for i in range(len(self.pesos)):
                 capa = np.atleast_2d(a[i])
                 delta = np.atleast_2d(deltas[i])
                 self.pesos[i] += taza_aprendizaje * capa.T.dot(delta)
    
    def predecir(self, x):   
        #Agregue bias a X
        a = np.concatenate((np.ones(1).T, np.array(x)))  
        #Realice un producto punto con los pesos de la red
        for l in range(0, len(self.pesos)):
            a = self.activacion(np.dot(a, self.pesos[l]))
        return a

if __name__ == "__main__":
    #Defina la cantidad de capas de la red
    #2 entradas, 2 capas ocultas, 1 capa de salida
    RNA = Red_neuronal([2,2,1])
    #Vectores de entrenamiento
    X = np.array([[0, 0],
                  [0, 1],
                  [1, 0],
                  [1, 1]])
    y = np.array([0, 1, 1, 0])
    RNA.Optimizar_pesos(X, y)
    #Prediga el valor de salida
    for e in X:
        print(e, RNA.predecir(e))