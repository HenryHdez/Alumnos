FROM python:3.9-slim

WORKDIR /app
COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt
COPY . .
EXPOSE 8080
CMD ["python", "aplicacion.py"]

#docker build -t zodb .
#docker run -p 8080:8080 zodb