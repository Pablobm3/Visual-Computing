import cv2
from matplotlib import pyplot as plt
import numpy as np


def plotHistogram(image, cumulative=False):
    hist = cv2.calcHist([image], [0], None, [256], [0, 256])
    if cumulative:
        hist = hist.cumsum()
    hist /= hist.sum()

    plt.figure()
    plt.plot(hist)
    plt.show()
    return hist

def histogramEqualization(image):
    # Paso 1: Cálculo del histograma
    hist = cv2.calcHist([image], [0], None, [256], [0, 256])

    # Paso 2: Cálculo del histograma acumulativo
    cumulative_hist = hist.cumsum()

    # Paso 3: Cálculo de la función de distribución acumulativa (CDF)
    cdf = cumulative_hist / float(image.size)

    # Paso 4: Multiplicar la función de distribución por la intensidad máxima de píxel posible
    max_intensity = 255
    cdf_scaled = (cdf * max_intensity).round().astype(np.uint8)

    # Paso 5: Aplicar la asignación a cada píxel de la imagen de entrada
    equalized_image = cv2.LUT(image, cdf_scaled)

    return equalized_image

#Cargar la imagen a escala de grises
img = cv2.imread('schrott.png',0)


#Valor mínimo y máximo de los valores de gris
min_val = np.min(img)
max_val = np.max(img)


new_min = 100
new_max = 150

#Escalar los valores de gris
scaled_img = cv2.convertScaleAbs(img, alpha=(new_max - new_min) / (max_val - min_val), beta=(new_min - min_val))

#Transformación para maximizar el rango de contraste
normalized_img = cv2.normalize(scaled_img, None, alpha=0, beta=255, norm_type=cv2.NORM_MINMAX)

equalized_img = histogramEqualization(img)



#Calcular y mostrar histogramas
hist = plotHistogram(img, False)

transformed_hist = plotHistogram(normalized_img)

equalized_hist = plotHistogram(equalized_img, cumulative=True)


