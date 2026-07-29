#pip install PySimpleGUI
import requests
import PySimpleGUI as sg

#Consulta
def consultar_clientes(url):
    respuesta = requests.get(url, timeout=10)
    respuesta.raise_for_status()

    datos = respuesta.json()

    if isinstance(datos, dict):
        datos = [datos]

    filas = []
    for fila in datos:
        filas.append([
            fila.get("id", ""),
            fila.get("nombre", ""),
            fila.get("correo", ""),
            fila.get("ciudad", "")
        ])

    return filas

#Funcion principal

def main():

    URL_DEFAULT = "http://localhost:5678/webhook/clientesget"

    layout = [
        [
            sg.Text("URL:"),
            sg.Input(URL_DEFAULT, key="-URL-", size=(60, 1)),
            sg.Button("Consultar")
        ],
        [
            sg.Table(
                values=[],
                headings=["ID", "Nombre", "Correo", "Ciudad"],
                key="-TABLA-",
                auto_size_columns=False,
                col_widths=[8, 20, 30, 15],
                justification="left",
                num_rows=15,
                expand_x=True,
                expand_y=True
            )
        ],
        [
            sg.Text("Estado: listo", key="-ESTADO-")
        ]
    ]

    window = sg.Window("Consulta de clientes", layout, resizable=True, size=(900, 450))

    while True:
        event, values = window.read()

        if event == sg.WIN_CLOSED:
            break

        if event == "Consultar":
            url = values["-URL-"].strip()

            if not url:
                window["-ESTADO-"].update("Estado: URL vacía")
                sg.popup_error("Debe ingresar una URL")
                continue

            try:
                window["-ESTADO-"].update("Estado: consultando...")

                filas = consultar_clientes(url)

                window["-TABLA-"].update(values=filas)

                window["-ESTADO-"].update(
                    f"Estado: consulta exitosa. Registros: {len(filas)}"
                )

            except requests.exceptions.RequestException as e:
                window["-ESTADO-"].update("Estado: error de conexión")
                sg.popup_error(f"Error de conexión o HTTP:\n{e}")

            except ValueError:
                window["-ESTADO-"].update("Estado: respuesta inválida")
                sg.popup_error("La respuesta no es un JSON válido")

    window.close()


if __name__ == "__main__":
    main()