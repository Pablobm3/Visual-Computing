import cv2
import numpy as np

imagen = cv2.imread('Practice5/Material/kante.png')

F1 = np.array([[0, 0, 0],
               [-1, 1, 0],
               [0, 0, 0]])

resultado = cv2.filter2D(imagen, -1, F1, delta=128)

F2 = np.array([[0, 0, 0],
               [0, -1, 1],
               [0, 0, 0]])

resultado_2 = cv2.filter2D(resultado, -1, F2, delta=128)

F3 = np.array([[0, 0, 0],
               [1, -2, 1],
               [0, 0, 0]])

resultado_3 = cv2.filter2D(imagen, -1, F3, delta=128)

F4 = np.array([[0, 0, 0],
               [0.333, 0.333, 0.333],
               [0, 0, 0]])

resultado_4 = cv2.filter2D(imagen, -1, F4, delta=128)

F5 = np.array([[0, 0, 0],
               [0, 1, 0],
               [0, 0, 0]])

resultado_5 = cv2.filter2D(imagen, -1, F5, delta=128)

F6 = np.array([[0, 0, 0],
               [0.333, -0.666, 0.333],
               [0, 0, 0]])

resultado_6 = cv2.filter2D(imagen, -1, F6, delta=128)

cv2.imshow('Imagen original', imagen)
cv2.imshow('Resultado de la primera convolución', resultado)
cv2.imshow('Resultado 2', resultado_2)
cv2.imshow('Resultado 3', resultado_3)
cv2.imshow('Resultado 4', resultado_4)
cv2.imshow('Resultado 5', resultado_5)
cv2.imshow('Resultado 6', resultado_6)
cv2.waitKey(0)
cv2.destroyAllWindows()
