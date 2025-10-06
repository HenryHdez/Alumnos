import tkinter as tk

def abrir_ventana():
    nueva = tk.Toplevel(root)       # Crear una ventana secundaria
    nueva.title("Ventana secundaria")
    nueva.geometry("300x200")

    tk.Label(nueva, text="Esta es una ventana secundaria").pack(pady=20)
    tk.Button(nueva, text="Cerrar", command=nueva.destroy).pack()

root = tk.Tk()
root.title("Ventana principal")
root.geometry("400x300")

tk.Label(root, text="Ventana Principal").pack(pady=20)
tk.Button(root, text="Abrir ventana secundaria", command=abrir_ventana).pack()

root.mainloop()