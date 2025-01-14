import scipy.io.wavfile as wav
import scipy.stats as stats

# Leer los datos de audio de los archivos WAV
fs1, data1 = wav.read('archivo1.wav')
fs2, data2 = wav.read('archivo2.wav')

# Calcular el coeficiente de correlación
corr_coef = stats.pearsonr(data1, data2)[0]
#El primer elemento es el coeficiente de correlación 
#El segundo es el valor p de la prueba de hipótesis

# Imprimir el coeficiente de correlación
print("El coeficiente de correlación entre "+
      "los dos archivos es:", corr_coef)

