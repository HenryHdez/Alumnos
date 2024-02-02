import socket
import pyaudio

HOST = '127.0.0.1'  # Dirección IP del servidor
PORT = 1234  # Puerto del servidor
BUFFER_SIZE = 1024

# Conectar al servidor
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
# Abrir la conexión de audio y reproducir 
# los datos recibidos del servidor
p = pyaudio.PyAudio()
stream = p.open(format=pyaudio.paInt16,
                channels=1,
                rate=44100,
                output=True)

data = s.recv(BUFFER_SIZE)
while data:
    stream.write(data)
    data = s.recv(BUFFER_SIZE)

# Detener el stream y cerrar la conexión de 
# audio y el socket
stream.stop_stream()
stream.close()
p.terminate()
s.close()

