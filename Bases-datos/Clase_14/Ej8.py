#pip install tabulate
import pandas as pd
import requests

# Crear un DataFrame de ejemplo
df = pd.DataFrame({
    "fruta": ["Manzana", "Banano", "Piña", "Mango", "Manzana"],
    "cantidad": [50, 100, 30, 80, 20],
    "precio_unitario": [500, 200, 1000, 600, 550],
    "origen": ["Boyacá", "Urabá", "Meta", "Tolima", "Cundinamarca"]
})

# Convertir el DataFrame a texto
df_texto = df.to_markdown(index=False)

# Preparar el mensaje para la IA
mensaje = f"""Analice esta tabla de frutas. Calcule qué fruta tiene el mayor ingreso total (cantidad x precio_unitario) y deme un resumen.
{df_texto}
"""

url = "http://localhost:11434/api/chat"
payload = {
    "model": "llama3",
    "messages": [
        {"role": "user", "content": mensaje}
    ],
    "stream": False
}

response = requests.post(url, json=payload)

if response.ok:
    print("Análisis de la IA:\n")
    print(response.json()["message"]["content"])
else:
    print("Error:", response.text)
