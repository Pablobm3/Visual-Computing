import numpy as np
import cv2
print("OpenCV-Version: " + cv2.__version__)


# Cargar la imagen "yoshi.png"
img = cv2.imread("yoshi.png")

# Mostrar el ancho, alto y número de canales de color
altura, ancho, canales = img.shape
print("Ancho:", ancho)
print("Alto:", altura)
print("Número de canales de color:", canales)

# Cambiar el formato de los datos de la imagen a coma flotante
img_float = img.astype(float)

# Mostrar la imagen original hasta que se pulse una tecla (uint8)
cv2.imshow("Imagen (uint8)", img)
cv2.waitKey(0)

# Mostrar la imagen en coma flotante hasta que se pulse una tecla
cv2.imshow("Imagen (float)", img_float / 255.0)
cv2.waitKey(0)

# Dibujar un cuadrado rojo de 10x10 píxeles en el centro de la imagen
centro_x = ancho // 2
centro_y = altura // 2
cv2.rectangle(img, (centro_x - 5, centro_y - 5), (centro_x + 5, centro_y + 5), (0, 0, 255), -1)

# Reemplazar cada 5 líneas con píxeles negros
img[::5, :] = 0


mask = cv2.imread("mask.png", cv2.IMREAD_GRAYSCALE)

# Convertir la imagen Yoshi al espacio de color HSV
img_yoshi_hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

# Obtener los píxeles blancos de la máscara
white_pixels = np.where(mask == 255)

# Cambiar el valor H de la imagen Yoshi para los píxeles blancos
img_yoshi_hsv[white_pixels[0], white_pixels[1], 0] = 60  # Cambiar el valor H a 60 (verde)

# Convertir la imagen HSV de nuevo a BGR
img_yoshi_modified = cv2.cvtColor(img_yoshi_hsv, cv2.COLOR_HSV2BGR)






# Mostrar la imagen modificada hasta que se pulse una tecla
cv2.imshow("Imagen modificada", img)
cv2.waitKey(0)

# Guardar la imagen en el disco duro
cv2.imwrite("yoshi_modificado.png", img)

# Mostrar la nueva imagen en la pantalla
cv2.imshow("Nueva imagen Yoshi", img_yoshi_modified)
cv2.waitKey(0)

# Opcional: Construir un deslizador para ajustar manualmente el valor H
def on_trackbar_change(value):
    # Actualizar el valor H de la imagen Yoshi
    img_yoshi_hsv[white_pixels[0], white_pixels[1], 0] = value
    # Convertir la imagen HSV de nuevo a BGR
    img_yoshi_modified = cv2.cvtColor(img_yoshi_hsv, cv2.COLOR_HSV2BGR)
    # Mostrar la imagen actualizada en la pantalla
    cv2.imshow("Nueva imagen Yoshi", img_yoshi_modified)

# Crear una ventana con un deslizador para ajustar el valor H
cv2.namedWindow("Nueva imagen Yoshi")
cv2.createTrackbar("Valor H", "Nueva imagen Yoshi", 60, 179, on_trackbar_change)

cv2.waitKey(0)

# Cerrar todas las ventanas abiertas
cv2.destroyAllWindows()
