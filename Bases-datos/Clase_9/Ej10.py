#Instale la librería request
import requests

BASE_URL = "http://localhost:5678/"
GET_ENDPOINT = f"{BASE_URL}/webhook-test/clientesget"
POST_ENDPOINT = f"{BASE_URL}/webhook-test/clientespost"

# FUNCIÓN GET (CONSULTAR)
def obtener_clientes():
    try:
        response = requests.get(GET_ENDPOINT)

        print("Status:", response.status_code)

        if response.status_code == 200:
            data = response.json()
            print("Respuesta GET:")
            print(data)
        else:
            print("Error:", response.text)

    except Exception as e:
        print("Error en GET:", e)

# FUNCIÓN POST (INSERTAR)
def crear_cliente():
    payload = {
        "nombre": "Carlos Python",
        "correo": "carlos@python.com",
        "ciudad": "Bogotá"
    }

    try:
        response = requests.post(POST_ENDPOINT, json=payload)

        print("Status:", response.status_code)

        if response.status_code in [200, 201]:
            print("Respuesta POST:")
            print(response.text)
        else:
            print("Error:", response.text)

    except Exception as e:
        print("Error en POST:", e)

if __name__ == "__main__":
    print("----- GET CLIENTES -----")
    obtener_clientes()

    #print("\n----- CREAR CLIENTE -----")
    #crear_cliente()