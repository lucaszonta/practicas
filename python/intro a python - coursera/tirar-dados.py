 # -*- coding: utf-8 -*-

import random

def tirar_un_dado():
    numeros = [1,2,3,4,5,6]
    resultado = random.choice(numeros)
    return resultado

def tirada_de_dados():
     estado = 'Y'
     while estado == 'Y':
         dado1 = tirar_un_dado()
         dado2 = tirar_un_dado()
         print("Resultado:", dado1, "y", dado2,"\nSuma:", dado1 + dado2)
         estado = input("¿Tirar los dados otra vez? Y/N:\n")
     else:
         print("¡Hasta pronto!")
         
tirada_de_dados()