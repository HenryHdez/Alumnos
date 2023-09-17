from tkinter import*
from tkinter import Tk
from tkinter import ttk
import matplotlib.pyplot as plt
from PIL import Image,ImageTk
import numpy as np
import time

def app1():
    plt.close('all')
    
    x=20
    x1=1
    x2=1
    x3=20
    cantidad1=[x,x1]
    cantidad2=[x2,x3]
    plt.ion()                         # gráfica asi un bucle este en ejecución
    figure, ax = plt.subplots()
    #linea1, = ax.plot(x, y, 'bo')
    #ax.plot(x, y, 'k')
    for s1 in range(2):
        for s in range(20):
            cantidad1=[x,x1]
            cantidad2=[x2,x3]
            if s1==0:
                
                x=x-1
                x1=x1+1
                x2=x2+1
                x3=x3-1
            else:
                x=x+1
                x1=x1-1
                x2=x2-1
                x3=x3+1
            fig, ax=plt.subplots()
            Hist=['hist1','hist2']
            ax.set_xlim([-0.5, 2])
            ax.set_ylim([0, 100])
            
        
            #plt.ion()
            vector_pos=np.arange(len(Hist))
            #vector_pos = np.arange(len(Marcas))
            ancho_barra=0.4
            ax.set_xticks(vector_pos, Hist)
            ax.set_xlabel('cantidad')
            ax.bar(vector_pos,cantidad1,ancho_barra,color='blue',edgecolor='black')
            ax.bar(vector_pos+ancho_barra,cantidad2,ancho_barra,color='red',edgecolor='black')
            ax.legend(Hist,loc=2)
            
            figure.canvas.draw()          # Dibujar valores actualizados
            figure.canvas.flush_events()  #Vaciar buffer
            time.sleep(0.1)
            
            #plt.update()
            
    
        
        #fig.canvas.draw()
        #fig.canvas.flush_events()
            time.sleep(0.01)

app1()