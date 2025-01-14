# !/usr/bin/env python 
# -*- coding: utf-8 -*-
from flask import Flask, render_template

#Generación de la interfaz WEB
app = Flask(__name__)

#Directorio raíz (página principal)
@app.route('/')
def index():
    return render_template('index.html')

#Función principal    
if __name__ == '__main__':
    app.run(host='0.0.0.0', debug=True)