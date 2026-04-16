# pip install tkhtmlview
import PySimpleGUI as sg
from tkhtmlview import HTMLLabel

# Contenido HTML
texto = """
<h1>Título</h1>
<p>Este es un ejemplo de texto largo.</p>
<b>Negrita</b><br>
<i>Cursiva</i><br>
<font color="red">Texto en rojo</font>
"""
numero = 5
resultado = numero * 10
texto2=f"""
            <p>Valor ingresado: <b>{numero}</b></p>
            <p>Resultado x10: <span style="color:red;">{resultado}</span></p>
            """
            
layout = [
    [sg.Text('Visualización HTML')],
    [sg.Canvas(key='-CANVAS-', size=(400,200))],
    [sg.Button('Salir')]
]

ventana = sg.Window('Ejemplo 3', layout, finalize=True)
canvas = ventana['-CANVAS-'].TKCanvas
# Crear widget HTML
html_widget = HTMLLabel(canvas, html=texto)
html_widget.pack(fill="both", expand=True)

while True:
    evento, valores = ventana.read()
    if evento == sg.WINDOW_CLOSED or evento == 'Salir':
        break
ventana.close()