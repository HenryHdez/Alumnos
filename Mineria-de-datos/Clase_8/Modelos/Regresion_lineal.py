import matplotlib.pyplot as plt
from sklearn import datasets
from sklearn.linear_model import LinearRegression

if __name__=="__main__":
    #Cargue el conjunto de datos
    dataset = datasets. load_boston()
    #Tome la variable a predecir y el predictor
    y = dataset['target']
    x = dataset['data']
    #Defina el modelo o técnica de aprendizaje
    modelo = LinearRegression()
    #Entrene el modelo
    modelo.fit(X=x, y=y)
    #Mostrar los datos predecidos por el modelo
    predicciones = modelo.predict(x)
    for y1, y_pred in list(zip(y, predicciones)) [:5]:
        print("Valor Real: (:.3f) Valor Estimado: (:.5f)".format(y1, y_pred))
    #Presentar los datos en la gráfica
    plt.plot(predicciones, "r", y, "g")
    plt.grid(linewidth="2")
    plt.grid(linewidth="2")
    plt.grid(None)
    plt.show()
    