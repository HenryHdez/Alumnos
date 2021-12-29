import matplotlib.pyplot as plt
# Librería que contiene el dataset Iris
from sklearn.datasets import load_iris
# Arbol de clasificación
from sklearn.tree import DecisionTreeClassifier
from sklearn.tree import plot_tree

if __name__ == "__main__":
    iris = load_iris()
    #Presenta información de iris
    print(iris.DESCR) # información sobre del conjunto de datos iris
    # lo más relevante es:
    #    :Number of Instances: 150 (50 in each of three classes)
    #    :Number of Attributes: 4 numeric, predictive attributes and the class
    #    :Attribute Information:
    #        - sepal length in cm
    #        - sepal width in cm
    #        - petal length in cm
    #        - petal width in cm
    #        - class:
    #                - Iris-Setosa
    #                - Iris-Versicolour
    #                - Iris-Virginica
    # La clase 0 es Setosa, la 1 es Versicolor y la 2 es Virginica
    # Presente los predictores y los datos a predecir
    print(iris.data)
    print(iris.target)
    # Cree el arbol y defina sus caracteristicas
    Arbol = DecisionTreeClassifier(max_depth=5, random_state=42)
    # Entrene el arbol
    Arbol.fit(iris.data, iris.target)
    # Verifique los datos que proporciona el modelo
    print(Arbol.predict(iris.data))
    #Presente los resultados obtenidos
    fig, ax = plt.subplots(figsize=(13, 6))
    print(f"Profundidad del árbol: {Arbol.get_depth()}")
    print(f"Número de nodos terminales: {Arbol.get_n_leaves()}")
    plot = plot_tree(
                decision_tree = Arbol,
                class_names   = ['Iris-Setosa', 'Iris-Versicolor', 'Iris-Virginica'],
                filled        = True,
                impurity      = False,
                fontsize      = 7,
                ax            = ax
           )
    
    # Del ejemplo anterior
    from sklearn.metrics import accuracy_score
    from sklearn.metrics import confusion_matrix
    # Error de test del modelo
    #-------------------------------------------------------------------------------
    predicciones = Arbol.predict(X = iris.data,)
    
    print("Matriz de confusión")
    print("-------------------")
    Matriz = confusion_matrix(
        y_true    = iris.target,
        y_pred    = predicciones
    )
    
    accuracy = accuracy_score(
                y_true    = iris.target,
                y_pred    = predicciones,
                normalize = True
               )
    print(f"El accuracy de test es: {100 * accuracy} %")
    
    
    
    