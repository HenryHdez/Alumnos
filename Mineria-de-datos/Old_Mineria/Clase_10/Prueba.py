#Importar librerías
import sklearn.datasets
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
#Tomar un conjunto de datos del repositorio de pruebas
Conjunto_datos = sklearn.datasets.load_iris()
#Tomar los predictores y datos a predecir
X, y = Conjunto_datos['data'], Conjunto_datos['target']
#Segmentar la cantidad de datos para crear conjuntos de etrenamiento y prueba
X_Entrenamiento, X_Prueba, y_Entrenamiento, y_Prueba = train_test_split(X, y, train_size=0.75) 
#Entrenar y probar el clasificador
Clasificador = KNeighborsClassifier(n_neighbors=3)
Clasificador.fit(X_Entrenamiento, y_Entrenamiento)
#Presentar el resultado
print(Clasificador.score(X_Prueba, y_Prueba))

from sklearn.model_selection import cross_val_score
Resultados = cross_val_score(Clasificador, X, y, cv=5)
print(Resultados)
print ("Precisión: %0.2f (+/- %0.2f)" % (Resultados.mean(), Resultados.std()))

