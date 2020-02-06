#CTIONE
#Minh Duc Ong
#Date
#
import numpy as np
import cv2
import argparse
import time
import os
from datetime import datetime

Points = []
x_values = []
y_values = []
def togetROI(event,x,y,flags,param):
    	# grab references to the global variables
	global Points
	# if the left mouse button was clicked, record the starting
	# (x, y) coordinates and indicate that cropping is being
	# performed
	if event == cv2.EVENT_LBUTTONDOWN:
                Points.append ((x, y))
                x_values.append(x)
                y_values.append(y)
                print(Points)
	# check to see if the left mouse button was released
	elif event == cv2.EVENT_RBUTTONDOWN:
                Points.clear()
                x_values.clear()
                y_values.clear()

#cap = cv2.VideoCapture("rtsp://admin:admin123@192.168.1.65/1")
#cap = cv2.VideoCapture("parkinglot_1_480p.mp4")
cap = cv2.VideoCapture(0)
cv2.namedWindow("frame", cv2.WINDOW_NORMAL)
backGr_sub = cv2.createBackgroundSubtractorMOG2()

while(True):
    # Capture frame-by-frame
    ret, frame = cap.read()
    mask = np.zeros(frame.shape, np.uint8)
    ROI = np.zeros(frame.shape, np.uint8)
    cv2.setMouseCallback("frame",togetROI)
    # Select ROI and do background subtraction
    if len(Points)>=8:
        min_x = min(x_values)
        min_y = min(y_values)
        max_x = max(x_values)
        max_y = max(y_values)
        cv2.polylines(frame, np.int32([Points]), True, (0,255,0), 2, 8)
        #cv2.drawContours(frame, np.int32([Points]), 0, (0,255,0), 3)
        cv2.fillPoly(mask, np.int32([Points]), (255,255,255))
        # returning the image only where mask pixels are nonzero
        masked_image = cv2.bitwise_and(frame, mask, mask)
        masked_image_final = mask[min_y:max_y, min_x: max_x]
        #cv2.imshow("mask_image", masked_image)
        cv2.imshow("mask_image_final", masked_image_final)
    #ROI = cv2.bitwise_and(frame,frame,mask)
    else:
        temp_PointPre=None
        for temp_Point in Points:
            cv2.circle(frame, temp_Point, 5, (0,255,0), thickness=-1, lineType=8, shift=0)
            if temp_PointPre is not None:
                cv2.line(frame,temp_PointPre,temp_Point,(0,255,0),2,8)
            temp_PointPre = temp_Point
    cv2.imshow("frame", frame)

		

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()
