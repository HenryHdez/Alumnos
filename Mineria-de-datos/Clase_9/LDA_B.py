from sklearn.datasets import load_iris
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score

# Cargar el conjunto de datos Iris
iris = load_iris()
X = iris.data
y = iris.target
# Dividir los datos en conjuntos de entrenamiento y prueba
X_train, X_test, y_train, y_test = train_test_split(X, y, 
                                   test_size=0.3, random_state=0)
# Ajustar el modelo LDA en el conjunto de entrenamiento
lda = LinearDiscriminantAnalysis()
lda.fit(X_train, y_train)
# Predecir las etiquetas de clase para los datos de prueba
y_pred = lda.predict(X_test)
# Evaluar el rendimiento del modelo utilizando la precisión
acc = accuracy_score(y_test, y_pred)
print("Precisión del modelo LDA:", acc)

