#------------------------------------------#
# Program: moments.py; coded by: HL, et al # 
# Date:    April 2018; Version: 0x0.1;     #
# Status:  Debug;                          #
# Purpose: Demonstrate contours and moment #
#          computation and other features  #
#------------------------------------------# 
# Python 2/3 compatibility
from __future__ import print_function

import cv2
import numpy as np

img = np.zeros((256,256,3), np.uint8) 
#image buffer, 256-by-256 with BGR color  

#---create test image with known pattern to check computation
for i in range(22):
    img = cv2.line(img,(32,32+i),(96,32+i),(255, 255, 255),1)
    
for i in range(20):
    img = cv2.line(img,(32,54+i),(64,54+i),(255, 255, 255),1)

for i in range(22):
    img = cv2.line(img,(32,74+i),(96,74+i),(255, 255, 255),1)

#---Gaussian blur 
img_blr0 = cv2.GaussianBlur(img, (3, 3), 2, 3) 
#5 by 5 kernel, sigma-x 2 and sigma-y 3\
img_blr1 = cv2.GaussianBlur(img, (5, 5), 3, 3)  
img_blr2 = cv2.GaussianBlur(img, (7, 7), 3, 7) 
img_blr3 = cv2.GaussianBlur(img, (19, 19), 23, 31)
img_blr4 = cv2.GaussianBlur(img, (21,21), 36, 47)

#cv2.namedWindow('gaussian1',0)\
#cv2.resizeWindow('gaussian1',256,256)\
#cv2.imshow('gaussian1',img_blr1)
#cv2.imshow('gaussian2',img_blr2)
#cv2.imshow('gaussian3',img_blr3)
#cv2.imshow('gaussian4',img_blr4) 

#img_diff \
#img_diff1 = img - img_blr1 
#img_diff2 = img - img_blr2 
#img_diff3 = img - img_blr3
#img_diff4 = img - img_blr4

#cv2.imshow('diff1', img_diff1) 
#cv2.imshow('diff2', img_diff2)
#cv2.imshow('diff3', img_diff3)
#cv2.imshow('diff4', img_diff4)

#img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
cv2.imshow('gray image', img_gray)

ret,thresh = cv2.threshold(img_gray,200,255,0) #threshold=220
cv2.imshow('thresholded binary',thresh)

_,contours,hierarchy = cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
contours = [cv2.approxPolyDP(cnt, 3, True) for cnt in contours]

_, _, angle = cv2.fitEllipse(contours[0])
print('angle= ',angle,end='\n')

M = cv2.moments(contours[0])
print('moments= ',M,end='\n')

cx = int(M['m10']/M['m00'])
cx = int(M['m01']/M['m00'])

perimeter = cv2.arcLength(contours[0],True)

print('perimeter= ', perimeter,end='\n')

area = cv2.contourArea(contours[0])

print('area= ',area,end='\n')

print('contour convex= ',cv2.isContourConvex(contours[0]), end='\n')

#print ('contours')
#print (contours)

epsilon = 0.1*cv2.arcLength(contours[0],True) 
approx = cv2.approxPolyDP(contours[0],epsilon,True) 

#hull = cv2.convexHull(cnt)
cv2.drawContours(img, contours, -1, (0,255,255),4) #draw contours on original image\
#1st argument: source image
#2nd argument: contours as a Python list\
#3rd argument: index of contours for individual contour. \
#4-5-6:        color,\
#7th argument: thickness.\

#cv2.drawContours(img, hull, -1, (0,0,255),3)\
cv2.imshow('findContours',img) 

# new code addition\

#ellipse = cv2.fitEllipse(cnt)\
#cv2.ellipse('EllipsCountours',img) \

mask = np.zeros(thresh.shape,np.uint8)
#cv2.drawContours(mask,contours[0],0,255,-1)
pixelpoints = np.transpose(np.nonzero(mask))
print ('[cnt]')
print("number of contours =", len(contours))
print ("background =", contours[0])

cnt = contours[0]
M = cv2.moments(cnt)
print (M)

x,y,w,h = cv2.boundingRect(contours[0])
cv2.rectangle(img, (x,y), (x+w, y+h), (0,0,255), 2)

cv2.imshow("brect", img)

#minized rectangle
Rect = cv2.minAreaRect(cnt)
box = cv2.boxPoints(Rect)
box = np.int0(box)
cv2.drawContours(img, [box], 0, (0,255,0), 2)

cv2.imshow("mArect", img)

#circle
(x,y),radius = cv2.minEnclosingCircle(cnt)
center = (int(x),int(y))
radius = int(radius)
cv2.circle(img,center,radius,(0,255,0),2)

ellipse = cv2.fitEllipse(cnt)
cv2.ellipse(img,ellipse,(0,255,0),2)

cv2.imshow("circle", img)

#fit line
rows,cols = img.shape[:2]
[vx,vy,x,y] = cv2.fitLine(cnt, cv2.DIST_L2,0,0.01,0.01)
lefty = int((-x*vy/vx) + y)
righty = int(((cols-x)*vy/vx)+y)
cv2.line(img,(cols-1,righty),(0,lefty),(0,255,0),2)

cv2.imshow("line", img)

#contour on the masked image
mask = np.zeros(img_gray.shape,np.uint8)
cv2.drawContours(mask,[cnt],0,255, -1)
print("\\ncontours object", [cnt])

#pixel points in a contour\
pixelpoints1 = np.transpose(np.nonzero(mask))
print ('\\npixelpoints  mask') 
print (pixelpoints1)

cv2.imshow("mask1", mask)


min_val, max_val, min_loc, max_loc = cv2.minMaxLoc(img_gray,mask = mask)
print("\\nminMaxValLoc")
print("minVal =",min_val)
print("maxVal =", max_val)
print("MinLocation =", min_loc)
print("minLocation =", max_loc)

mean_val = cv2.mean(img,mask = mask)

print("\\nmean =", mean_val)

cv2.circle(img_gray, min_loc, 5, (0,122,0), 2)
cv2.circle(img_gray, max_loc, 5, (0,255,0), 2)
cv2.imshow("min_loc_max_loc_ImgGray", img_gray)

cv2.waitKey(0)
cv2.destroyAllWindows()
