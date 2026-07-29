import ollama
response = ollama.generate(model='tinyllama', prompt='define ingeniero en español')
print(response['response'])
