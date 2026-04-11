import PySimpleGUI as sg
import matplotlib.pyplot as plt
from PIL import Image
import io

sg.theme('LightBlue')
layout = [
    [sg.Text('Mostrar gráfica')],
    [sg.Image(key='-IMG-')],
    [sg.Button('Generar gráfica'), sg.Button('Salir')]
]
ventana = sg.Window('Ejemplo2', layout)

while True:
    evento, valores = ventana.read()
    if evento == sg.WINDOW_CLOSED or evento == 'Salir':
        break
    if evento == 'Generar gráfica':
        # Crear gráfica
        plt.figure()
        plt.plot([1, 2, 3], [1, 4, 9])
        plt.title('Ejemplo de gráfica')
        # Guardar en memoria
        buffer = io.BytesIO()
        plt.savefig(buffer, format='PNG')
        plt.close()
        ventana['-IMG-'].update(data=buffer.getvalue())
ventana.close()