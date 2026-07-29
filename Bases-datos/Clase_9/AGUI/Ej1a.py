import PySimpleGUI as sg
#Ver temas disponibles
print(sg.theme_list())

sg.theme('DarkBlue9')
# Definir layout
layout = [
    [sg.Text('Ingrese un número:', font=('Arial', 14), text_color='yellow')],
    [sg.Input(key='-NUM-', font=('Courier New', 14), size=(15,1))]]

# Crear ventana con tamaño definido y fondo personalizado
ventana = sg.Window(
    'Ejemplo PySimpleGUI', layout, size=(400, 250),
    resizable=True, finalize=True
)

while True:
    evento, valores = ventana.read()
    if evento == sg.WINDOW_CLOSED:
        break
ventana.close()

