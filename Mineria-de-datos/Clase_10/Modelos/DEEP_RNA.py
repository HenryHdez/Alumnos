#Importar librerías
import numpy as np
from keras.models import Sequential
from keras.layers import Dense
from keras.utils import to_categorical
from keras.models import load_model
import tensorflow as tf

#Crear RNA       
class Red:
    def __init__(self,x,y):
        self.Entrada=x
        self.Objetivo=y
    def Entrenar(self):
        self.Modelo = Sequential()
        # Defina la cantidad de capas ocultas y las dimensiones de la entrada
        # En este caso es la longitud de la imagen vectorizada
        self.Modelo.add(Dense(100, activation='sigmoid', input_shape=(len(self.Entrada[1]),)))
        # Configure la capa de salida
        self.Modelo.add(Dense(len(self.Objetivo[1]), activation='softmax'))
        # Configure los parámetros de entrenamiento del modelo
        self.Modelo.compile(loss="categorical_crossentropy",
        optimizer="sgd",
        metrics = ['accuracy'])
        # Entrenar el modelo
        self.Modelo.fit(self.Entrada, self.Objetivo, batch_size=50, epochs=50)
        # Guardar RNA en una carpeta
        self.Modelo.save('Mi_RNA.h5')
    def Validar(self):
        # Importar RNA
        Modelo_Importado = load_model('Mi_RNA.h5')
        # Evaluar el modelo
        loss, acc = Modelo_Importado.evaluate(self.Entrada, self.Objetivo)
        print('Precisión:', acc)
        print (self.Modelo.predict(self.Entrada).round())        

if __name__ == "__main__":
    # Crear los arreglos de entrada y de salida
    Etiquetas=['Ambulancia', 'Ciclomotor', 'Moto', 'Policia', 'Taxi']
    # A cada etiqueta asigne un numero como identificador
    y=[1,2,3,4,5]
    X=[]
    # Leer imagenes desde una ubicación
    for i in Etiquetas:
        # Cargar imagen
        imagen = tf.keras.preprocessing.image.load_img('Imagenes/'+i+'.png')
        # Convertir imagen en una matriz de valores numéricos
        img = tf.keras.preprocessing.image.array_to_img(imagen)
        matriz = tf.keras.preprocessing.image.img_to_array(img)
        #Tomar de los componentes RGB el Rojo 1:Rojo, 2:Verde, 3:Azul
        X.append(matriz[:,:,1])
    # Convertir los valores de la matriz de rojos en enteros
    X = np.array(X, dtype = "uint8")
    # Normalizar el valor para procesarlo
    X = X.astype("float32")/255.0
    # Vectorizar los valores para entrenar la red
    X = X.reshape(5,-1)
    # Convetir los valores de salida en variables categoricas
    y = np.array(y, dtype = "uint8")
    y = to_categorical(y)
    # Crear la red
    RNA=Red(X,y)
    RNA.Entrenar()
    RNA.Validar()

