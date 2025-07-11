# En el terminal >>>>>>>>>>> Haz esto<<<<<<<<<<<<<<<<<<<
# Clonar imagen de ollama que es una IA similar a chatGPT
# docker run -d --name ollama -p 11434:11434 ollama/ollama

# Espera a que iniciela imagen
# En powershell, instala el modelo
# Invoke-RestMethod -Uri http://localhost:11434/api/pull -Method POST -Body '{"name":"llama3"}' -ContentType "application/json"

import requests
import json

# URL de la API de Ollama
url = "http://localhost:11434/api/chat"

# Mensaje del usuario
mensaje = "¿Cuál es la capital de Colombia?"

# Solicitud tipo chat
# Instrucción para el modelo de lenguaje
payload = {
    "model": "llama3",
    "messages": [
        {"role": "user", "content": mensaje}
    ],
    "stream": False 
}
#stream es respuesta tipo streaming, parte por parte o todo de una vez

# Enviar y procesar respuesta
try:
    response = requests.post(url, json=payload)
    response.raise_for_status()

    data = response.json()
    print(f"\nChat local dice:\n{data['message']['content']}")

#Manejo de errores
except requests.exceptions.RequestException as e:
    print(f"Error en la conexión: {e}")
except json.JSONDecodeError as e:
    print(f"Error al decodificar JSON: {e}")