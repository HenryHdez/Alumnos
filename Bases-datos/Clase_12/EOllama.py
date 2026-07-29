import pandas as pd
import ollama

df = pd.read_csv("iris.csv")
summary = df.groupby("species").mean()

prompt = f"""
Analiza las siguientes estadísticas del dataset Iris:

{summary.to_string()}

Indica:
- variables más discriminantes
- patrones entre especies
- conclusiones
"""

response = ollama.chat(
    model="llama3.2",
    messages=[{"role": "user", "content": prompt}]
)

print(response["message"]["content"])