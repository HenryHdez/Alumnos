import numpy as np
#Defina la clase perceptrón
class Perceptron:
    def __init__(self, entradas, salidas):
        self.entradas_rna = np.array(entradas)
        self.salidas_rna = np.array(salidas)
    def Optimizar_pesos(self):
        # Defina dos variables
        # Epocas que es la cantidad de iteraciones que transcurren 
        # para obtener una red entrenada
        # num_entradas que es el numero de entradas
        epocas, num_entradas = 0, 0
        while num_entradas < 4:
            print('---------- iteración {} ---------- '.format(epocas))
            # Genere pesos de forma aleatoria para que se actualicen en la RNA
            # .shape le indica que se un vector de la misma dimensionalidad 
            # que la entrada
            pesos = np.array(np.random.uniform(-1, 1, self.entradas_rna.shape))
            
            for entrada_red, peso, salida_red in zip(self.entradas_rna, pesos, self.salidas_rna):
                """Nota la función zip() toma varios objetos iterables del mismo 
                tamaño y retorna una nueva variable con la misma cantidad de 
                elementos"""
                # @ Realiza la suma ponderada de las entradas y los pesos
                salida_generada = entrada_red@peso
                print(salida_generada)
                # Función sigmoide (Función de activación)
                salida_generada = 0 if salida_generada < 0 else 1
                #Si se cumple el criterio aumente en 1 las entradas encontradas
                if salida_generada == salida_red:
                    num_entradas +=1
                else:
                    num_entradas = 0

                print('entrada: ', entrada_red, 'pesos:', peso, 'salida esperada: ',
                      salida_red, 'salida obtenida: ', salida_generada)
            epocas +=1
        return True
    
#Definición de la función principal
if __name__ == '__main__':
    # Entradas
    #Las dos primeras columnas son las 
    #combinaciones de la compuerta AND
    #La tercer columna es el valor de bias
    Entradas = [
        [0,0,1],
        [0,1,1],
        [1,0,1],
        [1,1,1]
    ]
    # Salidas
    Salidas = [0,0,0,1]
    #Iniciar RNA y optimizarla
    perceptron = Perceptron(Entradas, Salidas)
    perceptron.Optimizar_pesos()
    
    
    