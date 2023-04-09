import pandas as pd
from fpdf import FPDF

# Creamos un DataFrame de ejemplo
Ej = {'Nombre': ['Juan', 'Pedro', 'María', 'Ana'], 
      'Edad': [25, 30, 27, 23], 
      'País': ['México', 'España', 'Colombia', 'Argentina']}
df = pd.DataFrame(Ej)
pdf = FPDF()
#Agregar página
pdf.add_page()
pdf.set_font('Times', '', 12)
pdf.cell(30, 10, 'Datos')
#Salto de línea
pdf.ln()
for i in range(df.shape[0]):
    for j in range(df.shape[1]):
        pdf.cell(45, 10, str(df.iloc[i,j]), border=1)
    pdf.ln()
#Guardar pdf
pdf.output('data.pdf', 'F')

