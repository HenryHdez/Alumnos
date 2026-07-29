#pip install PySimpleGUI
import PySimpleGUI as sg
# Diseño de la ventana
layout = [
    [sg.Input(key='-CAMPO-')],
    [sg.Button('Boton')]
]
# Crear ventana
ventana = sg.Window('Ejemplo PySimpleGUI', layout)
# Bucle de eventos
while True:
    evento, valores = ventana.read()
    if evento == sg.WINDOW_CLOSED:
        break
    if evento == 'Boton':
        ventana['-CAMPO-'].update("Hola mundo")
ventana.close()