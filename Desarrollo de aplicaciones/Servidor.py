import base64
import cv2
import zmq

context = zmq.Context()
footage_socket = context.socket(zmq.PUB)
footage_socket.connect('tcp://192.168.0.13:5555') #Poner ip del servidor 

camera = cv2.VideoCapture(0)  #iniciar camara

while True:
    try:
        grabbed, frame = camera.read()  # leer frame
        frame = cv2.resize(frame, (640, 480))  # redimensionar frame
        encoded, buffer = cv2.imencode('.jpg', frame)
        jpg_as_text = base64.b64encode(buffer)
        footage_socket.send(jpg_as_text)

    except KeyboardInterrupt:
        camera.release()
        cv2.destroyAllWindows()
        break