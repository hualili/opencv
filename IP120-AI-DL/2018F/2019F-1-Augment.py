#---------------------------------------------------*
# program: 7-5augment_data.py;    coded by: CTI One *
# architect: Harry Li  ;    CTI One Corporation;    *
# date   : Oct 30, 2018;    status  : tested;       *
# purpose: resize any size input image to 28x28 for *
#          MNIST convnet use.                       *
#---------------------------------------------------*
import cv2
import numpy as np
#from matplotlib import pyplot as plt

#read the image in grayscale
img = cv2.imread('test.jpg',cv2.IMREAD_GRAYSCALE)

#gray = cv2.resize(gray, (28,28))
#cv2.imshow('image',img)

M = cv2.getRotationMatrix2D((img.shape[1] / 2, img.shape[0] / 2), 10, 1)
rotate1 = cv2.warpAffine(img, M, (img.shape[1], img.shape[0]))
M = cv2.getRotationMatrix2D((img.shape[1] / 2, img.shape[0] / 2), -10, 1)
rotate2 = cv2.warpAffine(img, M, (img.shape[1], img.shape[0]))

blur1 = cv2.GaussianBlur(img, (5, 5), 3)
blur2 = cv2.GaussianBlur(img, (7, 7), 5)
blur3 = cv2.GaussianBlur(img, (9, 9), 7)

rotate1_blur1 = cv2.GaussianBlur(rotate1, (5, 5), 3)
rotate1_blur2 = cv2.GaussianBlur(rotate1, (7, 7), 5)
rotate1_blur3 = cv2.GaussianBlur(rotate1, (9, 9), 7)

rotate2_blur1 = cv2.GaussianBlur(rotate2, (5, 5), 3)
rotate2_blur2 = cv2.GaussianBlur(rotate2, (7, 7), 5)
rotate2_blur3 = cv2.GaussianBlur(rotate2, (9, 9), 7)

cv2.imshow('36 rotate2_blur3',rotate2_blur3)

cv2.imwrite(f[0:-4] + "_rotate1.jpg", rotate1)

cv2.imwrite(f[0:-4] + "_rotate2.jpg", rotate2)

cv2.imwrite(f[0:-4] + "_blur1.jpg", blur1)

cv2.imwrite(f[0:-4] + "_blur2.jpg", blur2)

cv2.imwrite(f[0:-4] + "_blur3.jpg", blur3)

cv2.imwrite(f[0:-4] + "_rotate1_blur1.jpg", rotate1_blur1)

cv2.imwrite(f[0:-4] + "_rotate1_blur2.jpg", rotate1_blur2)

cv2.imwrite(f[0:-4] + "_rotate1_blur3.jpg", rotate1_blur3)

cv2.imwrite(f[0:-4] + "_rotate2_blur1.jpg", rotate2_blur1)

cv2.imwrite(f[0:-4] + "_rotate2_blur2.jpg", rotate2_blur2)

cv2.imwrite(f[0:-4] + "_rotate2_blur3.jpg", rotate2_blur3)


#end

#cv2.imwrite('resized_harryTest.jpg',gray, [int(cv2.IMWRITE_JPEG_QUALITY),90])

k = cv2.waitKey(0)
if k == 27:         # wait for ESC key to exit
    cv2.destroyAllWindows()



