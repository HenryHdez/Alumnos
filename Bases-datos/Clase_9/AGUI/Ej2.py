import PySimpleGUI as sg

# Pestaña 1
tab1_layout = [
    [sg.Text('Pestaña 1')],
    [sg.Input(key='-IN1-')],
    [sg.Button('Mostrar', key='-BTN1-')]
]

# Pestaña 2
tab2_layout = [
    [sg.Text('Pestaña 2')],
    [sg.Input(key='-IN2-')],
    [sg.Button('Multiplicar x10', key='-BTN2-')],
    [sg.Text('', key='-OUT2-')]
]

# Pestaña 3
tab3_layout = [
    [sg.Text('Configuración')],
    [sg.Checkbox('Opción 1')],
    [sg.Radio('A', 'grupo')],
    [sg.Radio('B', 'grupo')]
]

layout = [
    [sg.TabGroup([
        [
            sg.Tab('Entrada', tab1_layout),
            sg.Tab('Cálculo', tab2_layout),
            sg.Tab('Opciones', tab3_layout)
        ]
    ])],
    [sg.Button('Salir')]
]

ventana = sg.Window('Ejemplo 2', layout)

while True:
    evento, valores = ventana.read()

    if evento == sg.WINDOW_CLOSED or evento == 'Salir':
        break

    # Evento en pestaña 1
    if evento == '-BTN1-':
        print("Valor Tab 1:", valores['-IN1-'])
    # Evento en pestaña 2
    if evento == '-BTN2-':
        print("Valor Tab 2:", valores['-IN2-'])
ventana.close()