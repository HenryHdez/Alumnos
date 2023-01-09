import base64
import cv2
import zmq
import socket

Nombre_Socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
IP_Servidor = "127.0.0.1"
Puerto=1234
Nombre_Socket.bind((IP_Servidor, Puerto))
Clientes = 1
Nombre_Socket.listen(Clientes)
ID_Socket_Cliente, direccion = Nombre_Socket.accept()

camera = cv2.VideoCapture(0)  #iniciar camara

while True:
    try:
        grabbed, frame = camera.read()  # leer frame
        frame = cv2.resize(frame, (640, 480))  # redimensionar frame
        encoded, buffer = cv2.imencode('.jpg', frame)
        jpg_as_text = base64.b64encode(buffer)
        ID_Socket_Cliente.sendall(jpg_as_text)
    except KeyboardInterrupt:
        camera.release()
        cv2.destroyAllWindows()
        break
"""Cerrar instancias del socket"""
ID_Socket_Cliente.close()
Nombre_Socket.close()