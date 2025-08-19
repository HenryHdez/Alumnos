class Lista:
    def _init_(self):
        self.lista = []

    def buscar_maximo(self):
        return max(self.lista)
    
    def buscar_minimo(self):
        return min(self.lista)
    
    def multiplos_de_tres(self):
        return [x for x in self.lista if x % 3 == 0]
    
    
if __name__ == "__main__":
    primera = Lista()
    primera.lista = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    print(primera.buscar_maximo())
    print(primera.buscar_minimo())
    print(primera.multiplos_de_tres())