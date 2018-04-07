#------------------------------------------#
# Program: moments.py; coded by: HL;       #
# Date:    March 2017; Version: 0x0.1;     #
# Status:  Debug;                          #
# Purpose: Demonstrate contours and moment #
#          computation.                    #
#------------------------------------------# 
# Python 2/3 compatibility
from __future__ import print_function

import cv2
import numpy as np
  
img = cv2.imread('1track.jpg')  #'0' to read color as gray scale 
cv2.imshow('color image',img) 

img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
cv2.imshow('gray image', img_gray)

ret,thresh = cv2.threshold(img_gray,200,255,0) #threshold=220
cv2.imshow('thresholded binary',thresh) 

img2,contours,hierarchy = cv2.findContours(thresh, 1, 2)


cv2.drawContours(img2, contours, -1, (0,255,255), 5)
#1st argument: source image
#2nd argument: contours as a Python list
#3rd argument: index of contours for individual contour. 
#4-5-6:        color,
#7th argument: thickness.
cv2.imshow('findContours',thresh) 

cnt = contours[0]
M = cv2.moments(cnt)
print (M)
 

cv2.waitKey(0)
cv2.destroyAllWindows()
