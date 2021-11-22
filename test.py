
import cv2
import numpy as np
import forpy

bezier_curve = forpy.ForPyInterface()

bezier_curve.Setx1y1(90, 10)
bezier_curve.Setx2y2(10, 90)
image = bezier_curve.GetView().astype('uint8').reshape(200, 200, 1)

print(image.shape)
cv2.imwrite("../testimage.png", image)

print("end")
