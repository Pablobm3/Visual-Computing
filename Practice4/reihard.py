import numpy as np
import cv2

print("OpenCV-Version: " + cv2.__version__)

# Leer las imágenes de entrada y objetivo
img = cv2.imread("Practice4\entrada.jpg")
img2 = cv2.imread("Practice4\objetivo.jpg")

# Obtener las dimensiones de las imágenes
altura, ancho, canales = img.shape
altura2, ancho2, canales2 = img2.shape

# Convertir las imágenes a formato float
img_float = img.astype(float)
img2_float = img2.astype(float)

img_uint8 = cv2.convertScaleAbs(img_float)
img_lab = cv2.cvtColor(img_uint8, cv2.COLOR_BGR2LAB)

img2_uint8 = cv2.convertScaleAbs(img2_float)
img2_lab = cv2.cvtColor(img2_uint8, cv2.COLOR_BGR2LAB)

# Función para procesar un canal de color
def process_channel(channel, mean_input, std_input, mean_target, std_target):
    # Convertir el canal a tipo float64
    channel = channel.astype(np.float64)

    # Restar el valor medio de la entrada
    channel -= mean_input

    # Dividir por la desviación típica de la entrada
    channel /= std_input

    # Multiplicar por la desviación típica del objetivo
    channel *= std_target

    # Añadir el valor medio del objetivo
    channel += mean_target

    # Asegurarse de que los valores estén dentro del rango válido
    channel = np.clip(channel, 0, 255)

    # Convertir a tipo uint8
    channel = channel.astype(np.uint8)

    return channel


# Procesar cada canal de color por separado en las imágenes LAB
for i in range(canales):
    img_lab[:, :, i] = process_channel(img_lab[:, :, i], np.mean(img_lab[:, :, i]), np.std(img_lab[:, :, i]), np.mean(img2_lab[:, :, i]), np.std(img2_lab[:, :, i]))

# Convertir las imágenes de vuelta a formato BGR
img_result = cv2.cvtColor(img_lab, cv2.COLOR_LAB2BGR)

# Mostrar la imagen resultante
cv2.imshow("Imagen resultante", img_result)
cv2.waitKey(0)
cv2.destroyAllWindows()
