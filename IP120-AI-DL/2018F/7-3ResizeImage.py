#---------------------------------------------------*
# program: resizeimg.py;    coded by: Minh Ong;     *
# architect: Harry Li  ;    CTI One Corporation;    * 
# date   : Oct 30, 2018;    status  : tested;       * 
# purpose: resize any size input image to 28x28 for * 
#          MNIST convnet use.                       * 
#---------------------------------------------------* 
import cv2
import numpy as np
#from matplotlib import pyplot as plt

#read the image in grayscale
gray = cv2.imread('test.png',cv2.IMREAD_GRAYSCALE)
#resize the image to (28,28)
gray = cv2.resize(gray, (28,28))
#show the image
cv2.imshow('image',gray)
#save the image
cv2.imwrite('resized_harryTest.jpg',gray, [int(cv2.IMWRITE_JPEG_QUALITY),90])

k = cv2.waitKey(0)
if k == 27:         # wait for ESC key to exit
    cv2.destroyAllWindows()

