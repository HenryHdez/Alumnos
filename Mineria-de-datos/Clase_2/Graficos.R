#Graficos en R
#Defina la variable a graficar.
t<-seq(-pi,pi,0.1)
y=tan(t)
#El comando plot se encarga
plot(t,y)
#Si desea asignar rotulos use las palabras main, ylab y xlab
plot(t,y,
     main='titulo',
     ylab='Amplitud',
     xlab='tiempo')

#Hay varios tipos de linea (type) y se designan con letras
#l=línea continua, p=puntos, b=puntos y lineas, o=subrayar circulos
#s=escalonado, h=lineas verticales
#lwd= ancho de la linea
#col=color en ingles
plot(t,y,
     main='titulo',
     ylab='Amplitud',
     xlab='tiempo',
     type='l',
     col='red',
     lwd='2'
)

#R también imprime grupos de datos alfanumericos clasificandolos
Frutas=c('Banano','Fresa','Coco','Fresa','Coco','Coco')
#El comando factor los agrupa
F=factor(Frutas)
plot(F) #En este caso se imprime un histograma
#Level me indica cuales son las eqtiquetas disponibles 
#dentro del vector
print(levels(F))
#str le indica que nivel ocupa cada etiqueta dentro del 
#arreglo. Ej. Banano es el 1, Fresa es el 3 y Coco el 2
str(F)
#Es decir convierte un dato categorico a número