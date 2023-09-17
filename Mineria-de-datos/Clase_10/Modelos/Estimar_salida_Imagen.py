#Importar librerías
import numpy as np
from keras.models import load_model
import tensorflow as tf       

if __name__ == "__main__":
    # Importar RNA
    Modelo_Importado = load_model('Mi_RNA')
    # Crear los arreglos de entrada y de salida
    Etiquetas=['Ambulancia', 'Ciclomotor', 'Moto', 'Policia', 'Taxi']
    # Seleccionar imagen
    Seleccion=Etiquetas.index(Etiquetas[4])
    X=[]
    # Leer imagenes desde una ubicación
    for i in Etiquetas:
        imagen = tf.keras.preprocessing.image.load_img('Imagenes/'+i+'.png')
        img = tf.keras.preprocessing.image.array_to_img(imagen)
        matriz = tf.keras.preprocessing.image.img_to_array(img)
        X.append(matriz[:,:,1])
    X = np.array(X, dtype = "uint8")
    X = X.astype("float32")/255.0
    X = X.reshape(5,-1)
    # Tomar imagen de acuerdo con la selección
    Imagen_Seleccionada = X[Seleccion:Seleccion+1,:]
    y = Modelo_Importado.predict(Imagen_Seleccionada).round()
    y = y.tolist()
    Imagen_encontrada=Etiquetas[y[0].index(1.0)-1]
    print (Imagen_encontrada)

