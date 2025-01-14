from flask import Flask, render_template, request
import Orange
import matplotlib
# Permite el procesamiento de datos en segundo plano
matplotlib.use('Agg')  
import matplotlib.pyplot as plt
import pandas as pd
import os

app = Flask(__name__)
STATIC_DIR = os.path.join(os.getcwd(), 'static')

# Página principal
@app.route('/')
def index():
    return render_template('index.html')

# Cargar y analizar el archivo .csv
@app.route('/upload', methods=['POST'])
def upload_file():
    if 'file' not in request.files:
        return "Archivo no cargado", 400
    file = request.files['file']
    if file.filename == '':
        return "Archivo no seleccionado", 400
    # Verifica que la carpeta /static existe o la crea
    if not os.path.exists(STATIC_DIR):
        os.makedirs(STATIC_DIR)
    # Guarda el archivo .csv en la carpeta 'static'
    file_path = os.path.join(STATIC_DIR, file.filename)
    file.save(file_path)

    # Análisis con Orange
    data = Orange.data.Table(file_path)
    domain = data.domain 
    feature_names = [attr.name for attr in domain.attributes]
    # Calcular promedios
    df = pd.DataFrame([[d[attr.name] for attr in domain.attributes] for d in data], columns=feature_names)
    means = df.mean().to_dict()
    # Crear gráfico
    plt.figure(figsize=(8, 4))
    plt.bar(means.keys(), means.values(), color='blue')
    plt.title("Promedio de Atributos")
    plt.xticks(rotation=45)
    graph_path = os.path.join('static', 'graph.png')
    plt.savefig(graph_path)
    if os.path.exists(graph_path):
        print(f"Gráfica guardada como: {graph_path}")
    else:
        print("Gráfico no guardado!")
    return render_template('result.html', graph_path=graph_path, means=means)

# Ejecutar la aplicación
if __name__ == '__main__':
    app.run(debug=True)
