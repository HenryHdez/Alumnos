# Importar la librería PySimpleGUI
import PySimpleGUI as sg

layout = [
    #Fila 1: Texto y campo de entrada
    [sg.Text('Ingrese un número:'), sg.Input(key='-NUM-', size=(10,1))],
    #Fila 2: Checkbox y Radio
    [sg.Checkbox('A'), sg.Radio('B', 'grupo1'), sg.Radio('C', 'grupo1')],
    #Fila 3: Lista desplegable
    [sg.Combo(['Opción 1', 'Opción 2', 'Opción 3'], key='-COMBO-')],
    #Fila 4: Slider (control deslizante)
    [sg.Slider(range=(0,100), orientation='h', key='-SLIDER-')],
    #Fila 5: Botones (generan eventos)
    [sg.Button('Calcular'), sg.Button('Salir')],
    #Fila 6: Texto de salida (resultado)
    [sg.Text('Resultado:', key='-RES-')]
]

ventana = sg.Window('Ejemplo completo', layout)
while True:
    evento, valores = ventana.read()
    if evento == sg.WINDOW_CLOSED or evento == 'Salir':
        break
    # Evento del botón calcular
    if evento == 'Calcular':
        try:
            # Leer valor del input
            numero = float(valores['-NUM-'])
            resultado = numero * 10
            # Actualizar texto de salida
            ventana['-RES-'].update(f'Resultado: {resultado}')
        except:
            # Manejo de error si no es número
            ventana['-RES-'].update('Entrada inválida')
ventana.close()

