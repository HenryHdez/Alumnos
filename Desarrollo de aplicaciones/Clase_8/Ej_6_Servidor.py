import cv2
import socket
import struct

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(('127.0.0.1', 5000))
s.listen(1)
conn, addr = s.accept()
cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()
    # Comprimir la imagen
    _, data = cv2.imencode('.jpg', frame, [cv2.IMWRITE_JPEG_QUALITY, 80])
    # Empaquetar los datos (Convertir los datos a bytes, Q=Formato)
    # y enviarlos a traves de la red
    msg = struct.pack('Q', len(data)) + data.tobytes()
    # Enviar los datos al cliente
    conn.sendall(msg)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
cap.release()
cv2.destroyAllWindows()

