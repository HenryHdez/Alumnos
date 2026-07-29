import ollama

modelo = "tinyllama"

prompt = """
En español, tengo el siguiente diccionario:
datos = {'nombre': 'Ana', 'edad': 28, 'ciudad': 'Bogotá'}

¿Cómo puedo agregar una nueva llave llamada 'profesion' con el valor 'Ingeniera'?
Muéstrame el código completo.
"""

respuesta = ollama.generate(model=modelo, prompt=prompt)

print(respuesta["response"])