import pyaudio
import wave
#Definir características del equipo
Equipo=[pyaudio.paInt16, 1, 44100, 1024]
Duracion = 5
Nombre_Archivo = "archivo2.wav"

audio = pyaudio.PyAudio()

# Configurar el microfono
Mic = audio.open(format=Equipo[0], channels=Equipo[1],
                    rate=Equipo[2], input=True,
                    frames_per_buffer=Equipo[3])
print("Grabando...")

# Grabar audio en un buffer
frames = []
for i in range(0, int(Equipo[2] / Equipo[3] * Duracion)):
    datos = Mic.read(Equipo[3])
    frames.append(datos)
print("Grabación finalizada.")

# Detener y cerrar el flujo de audio                         
Mic.stop_stream()
Mic.close()
audio.terminate()

# Guardar la grabación de audio en un archivo WAV
wavArch = wave.open(Nombre_Archivo, 'wb')
wavArch.setnchannels(Equipo[1])
wavArch.setsampwidth(audio.get_sample_size(Equipo[0]))
wavArch.setframerate(Equipo[2])
wavArch.writeframes(b''.join(frames))
wavArch.close()

