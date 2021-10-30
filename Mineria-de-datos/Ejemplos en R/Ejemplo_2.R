#Si (Nota: R es jerarquico asi que respete las tabuaciones)
x<-4
#Condicional
if(x<5){
  print('correcto')
}else{
    print('incorrecto')
  }
#Condicional anidado
if(x<0){
  print('uno')
  }else if((x<0) && (x>7)){ #Función AND
    print('dos')
    }else if((x<1) || (x>2)){ #Función OR
      print('fal')
    } else{
        print('tres')
    }

#Bucles o iterativas
#For
for (i in 1:100){
  print(i)
}
#Implementar formas de recorrer vectores
Vec=c('a','b','c','fin')
for(i in Vec){
  print(i)
}
#While
conta<-0
while(conta<10){
  print('aún no termina')
  conta<-conta+1
}

#indexación lógica
#si tiene dos vectores
a=c(1,2,3,4)
b=c(6,8,0,5)
#Puede generar un vector nuevo comparando dos
#vectores posición a posición
c<-a<b
print(c)
