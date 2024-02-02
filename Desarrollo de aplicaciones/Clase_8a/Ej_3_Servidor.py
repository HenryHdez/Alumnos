import socket
import pyaudio
import wave

HOST = '127.0.0.1'      # Dirección IP del servidor
PORT = 1234             # Puerto del servidor
BUFFER_SIZE = 1024      # Tamaño del buffer

Nombre_Arch = 'archivo1.wav'

# Crear un socket TCP
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# Asociar el socket al puerto y escuchar las conexiones entrantes
s.bind((HOST, PORT))
s.listen(1)
print(f"Servidor escuchando en {HOST}:{PORT}")
# Aceptar la conexión entrante del cliente
conn, addr = s.accept()

# Abrir el archivo WAV y obtener sus parámetros
wf = wave.open(Nombre_Arch, 'rb')
p = pyaudio.PyAudio()
stream = p.open(format=p.get_format_from_width(wf.getsampwidth()),
                channels=wf.getnchannels(),
                rate=wf.getframerate(),
                output=True)
# Leer los datos del archivo y enviarlos al cliente
data = wf.readframes(BUFFER_SIZE)
while data:
    conn.send(data)
    stream.write(data)
    data = wf.readframes(BUFFER_SIZE)
print(f"Archivo enviado: {Nombre_Arch}")
# Detener el stream y cerrar la conexión de audio y el socket
stream.stop_stream()
stream.close()
p.terminate()
conn.close()
s.close()

