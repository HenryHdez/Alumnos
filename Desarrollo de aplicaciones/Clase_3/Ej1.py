# -*- coding: utf-8 -*-

a=10

def funcion1():
    # a es una variable global
    #Variables locales (b,c)
    global a
    b=3
    c=a+b
    print(c)

def funcion2(t,u):
    r=t+u
    return r

if __name__=="__main__":
    print("Funcion principal en PYTHON")
    a=8
    funcion1()
    var=funcion2(4,5)
    print(var)
    