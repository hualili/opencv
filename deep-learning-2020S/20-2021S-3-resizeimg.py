#---------------------------------------------------*
# program: resizeimg.py;    coded by: HL, MO;       * 
# date   : Oct 30, 2018;    status  : tested;       * 
# purpose: resize any size input image to 28x28 for * 
#          MNIST convnet use.                       * 
#---------------------------------------------------* 
import cv2
import numpy as np
#from matplotlib import pyplot as plt

#read the image in grayscale
gray = cv2.imread('one.jpeg',cv2.IMREAD_GRAYSCALE)
#resize the image to (28,28)
gray = cv2.resize(gray, (150,150))
#show the image
cv2.imshow('image',gray)
#save the image
cv2.imwrite('1.jpg',gray, [int(cv2.IMWRITE_JPEG_QUALITY),90])

k = cv2.waitKey(0)
if k == 27:         # wait for ESC key to exit
    cv2.destroyAllWindows()

