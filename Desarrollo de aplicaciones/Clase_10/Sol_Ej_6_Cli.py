import cv2
import socket
import struct
import numpy as np

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('127.0.0.1', 5000))

#####----------Mover---------#########
# Recibir los datos del servidor
datos = b""
#Calcula el tamaño del arreglo que llega
Cargautil = struct.calcsize("Q")
#####----------Mover---------#########

try: #######Extra######
    while True:
        while len(datos) < Cargautil:
            paquete = s.recv(4*1024)
            if not paquete: break
            datos += paquete
        Tam_paquete = datos[:Cargautil]
        datos = datos[Cargautil:]
        
        #Desempaquetar el arreglo que llega a traves de la red
        Tam_msg = struct.unpack("Q", Tam_paquete)[0]
        #Reconstruir el mensaje
        while len(datos) < Tam_msg:
            datos += s.recv(4*1024)
        frame_datos = datos[:Tam_msg]
        datos = datos[Tam_msg:]

        # Decodificar la imagen
        frame = cv2.imdecode(np.frombuffer(frame_datos, np.uint8),
                            cv2.IMREAD_COLOR)

        cv2.imshow('Client', frame)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
except Exception as e:
    print(f"Error durante la recepción: {e}")
finally:  
    cv2.destroyAllWindows()
    s.close()

