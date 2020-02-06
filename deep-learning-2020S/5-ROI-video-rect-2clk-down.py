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
	elif event == cv2.EVENT_LBUTTONUP:
                Points.append ((x, y))
                x_values.append(x)
                y_values.append(y)
                print(Points)

#cap = cv2.VideoCapture("rtsp://admin:admin123@192.168.1.62/1")
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
    if len(Points)>=2:
        cv2.rectangle(frame, Points[0], Points[1], (0, 255, 0), 2)
        if (Points[1][1]-Points[0][1]>=0 and Points[1][0]-Points[0][0] >=0):
           frame_ROI=frame[Points[0][1]:Points[1][1], Points[0][0]:Points[1][0]]
        if (Points[1][1]-Points[0][1]>=0 and Points[1][0]-Points[0][0] <0):
           frame_ROI=frame[Points[0][1]:Points[1][1], Points[1][0]:Points[0][0]]
        if (Points[1][1]-Points[0][1]<0 and Points[1][0]-Points[0][0] >=0):
           frame_ROI=frame[Points[1][1]:Points[0][1], Points[0][0]:Points[1][0]]
        if (Points[1][1]-Points[0][1]<0 and Points[1][0]-Points[0][0] <0):
           frame_ROI=frame[Points[1][1]:Points[0][1], Points[1][0]:Points[0][0]]
        cv2.imshow("frame_ROI",frame_ROI)
    #ROI = cv2.bitwise_and(frame,frame,mask)
    cv2.imshow("frame", frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything done, release the capture
cap.release()
toWriteVideo.release()
cv2.destroyAllWindows()
