import cv2
import base64
import numpy as np
import socket

Nombre_Socket = socket.socket()
IP_Servidor='127.0.0.1'
Puerto=1234

try:
    Bandera=True
    Nombre_Socket.connect((IP_Servidor, Puerto))
except ConnectionRefusedError:
    Bandera=False 
    print('Intente conectarse al servidor nuevamente')

while True:
    try:
        frame = Nombre_Socket.recv(65507)
        img = base64.b64decode(frame)
        npimg = np.fromstring(img, dtype=np.uint8)
        source = cv2.imdecode(npimg, 1)
        cv2.imshow("Stream", source)
        cv2.waitKey(1)
        print("conectado")
    except KeyboardInterrupt:
        cv2.destroyAllWindows()
        break
    