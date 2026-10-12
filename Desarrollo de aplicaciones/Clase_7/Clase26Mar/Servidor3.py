from flask import render_template, Flask, request

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/bienvenida', methods=['POST'])
def bienvenida():
    if request.method == 'POST':
        print(request.form)
        entrada = request.form['Campoentrada']
        return render_template('bienvenida.html', nombre=entrada)
    else:
        return "Error 404"

if __name__ == '__main__':
    app.run(debug=True)