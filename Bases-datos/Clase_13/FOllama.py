import pandas as pd
import ollama

df = pd.read_csv("iris.csv")

prompt = f"""
Genera un reporte técnico del dataset Iris:

- descripción general
- variables importantes
- posibles aplicaciones

Datos:
{df.describe().to_string()}
"""

response = ollama.chat(
    model="llama3.2",
    messages=[{"role": "user", "content": prompt}]
)

print(response["message"]["content"])