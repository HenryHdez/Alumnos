# pip install pillow
import PySimpleGUI as sg
from PIL import Image
import io
import os

sg.theme('LightBlue')
layout = [
    [sg.Text('Cargar imagen')],
    [sg.Image(key='-IMG-')],
    [sg.Button('Mostrar Imagen'), sg.Button('Salir')]
]
ventana = sg.Window('Ejemplo1', layout)

while True:
    evento, valores = ventana.read()
    if evento == sg.WINDOW_CLOSED or evento == 'Salir':
        break
    if evento == 'Mostrar Imagen':
        try:
            ruta = os.path.abspath('Prueba.jpg')
            # Abrir imagen
            img = Image.open(ruta)
            img = img.resize((200, 200))
            # Convertir a bytes
            buffer = io.BytesIO()
            img.save(buffer, format='PNG')
            ventana['-IMG-'].update(data=buffer.getvalue())
        except Exception as e:
            sg.popup_error(f'Error: {e}')

ventana.close()