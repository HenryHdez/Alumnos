import socket
import json
import time
import platform
import os
from datetime import datetime

HOST = "ubuntu1"
PORT = 5000

def obtener_datos():
    data = {
        "hostname": socket.gethostname(),
        "plataforma": platform.system().lower(),
        "cpu": os.cpu_count(),
        "memoria_total": os.sysconf('SC_PAGE_SIZE') * os.sysconf('SC_PHYS_PAGES'),
        "memoria_libre": os.sysconf('SC_PAGE_SIZE') * os.sysconf('SC_AVPHYS_PAGES'),
        "uptime": time.time(),  # tiempo desde epoch (aproximación)
        "timestamp": datetime.utcnow().isoformat()
    }
    return data

def main():
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect((HOST, PORT))

    print("Conectado al servidor")

    try:
        while True:
            datos = obtener_datos()
            mensaje = json.dumps(datos)
            client.sendall(mensaje.encode())

            print("Enviado:", datos)

            time.sleep(5)

    except KeyboardInterrupt:
        print("Cerrando conexión")
        client.close()

if __name__ == "__main__":
    main()