from .basic_operations import ImageOperator
import matplotlib.pyplot as plt
import cv2


image = cv2.imread("leave.png")
grey_image = ImageOperator.grayscale(image)
plt.imshow(grey_image, cmap="gray")
plt.show()