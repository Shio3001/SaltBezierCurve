
import cv2
import numpy as np
import forpy_saltbeziercurve

bezier_curve = forpy_saltbeziercurve.ForPyInterface(1000, 1000)

bezier_curve.Setx1y1(50, 100)
bezier_curve.Setx2y2(100, 50)
image = bezier_curve.GetView().astype('uint8').reshape(1000, 1000, 1)

print(image.shape)
cv2.imwrite("../testimage.png", image)

print("end")
