from flask import Flask, render_template
import pandas as pd

app = Flask(__name__)

# Creamos un DataFrame de ejemplo
Ej = {'Nombre': ['Juan', 'Pedro', 'María', 'Ana'], 
      'Edad': [25, 30, 27, 23], 
      'País': ['México', 'España', 'Colombia', 'Argentina']}
df = pd.DataFrame(Ej)
# Convertimos el DataFrame a una tabla HTML
html_table = df.to_html(index=False)
# Creamos una página web con la tabla incrustada
@app.route("/")
def index():
    return render_template("index.html", table=html_table)

if __name__ == "__main__":
    app.run()

