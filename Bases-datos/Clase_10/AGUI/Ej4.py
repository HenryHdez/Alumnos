# pip install pandas
import PySimpleGUI as sg
import pandas as pd
from tkhtmlview import HTMLLabel

sg.theme('LightBlue')

layout = [
    [sg.Text('Tabla de datos')],
    [sg.Button('Mostrar tabla'), sg.Button('Salir')],
    [sg.Canvas(key='-CANVAS-', size=(500, 250))]
]

ventana = sg.Window('Ejemplo 4', layout, finalize=True)
canvas = ventana['-CANVAS-'].TKCanvas
html_widget = None

while True:
    evento, valores = ventana.read()
    if evento == sg.WINDOW_CLOSED or evento == 'Salir':
        break

    if evento == 'Mostrar tabla':
        # Crear diccionario con los datos
        datos = {
            'nombre': ['Miguel', 'Mario', 'Pedro', 'Lucy'],
            'edad': [32, 45, 22, 38],
            'ciudad': ['Bogotá', 'Cali', 'Medellín', 'Pasto']
        }
        # Crear DataFrame
        df = pd.DataFrame(datos)
        # Convertir DataFrame a HTML
        tabla_html = df.to_html()
        # Guardar archivo CSV
        df.to_csv('resultados.csv', sep=',', index=True, header=True)

        if html_widget is not None:
            html_widget.destroy()
        html_widget = HTMLLabel(canvas, html=tabla_html)
        html_widget.pack(fill='both', expand=True)

ventana.close()