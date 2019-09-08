import numpy as np
import cv2
import argparse
import time
import os
from datetime import datetime


#cap = cv2.VideoCapture(1)
cap = cv2.VideoCapture("parkinglot_1_480p.mp4")
cv2.namedWindow("frame", cv2.WINDOW_NORMAL)

#define 2 Points
Point1 = (300,300)
Point2 = (370,370)

while(True):
    # Capture frame-by-frame
    ret, frame = cap.read()

    #Draw ROI	
    frame_ROI=frame[Point1[0]:Point2[0], Point1[1]:Point2[1]]
    cv2.rectangle(frame, Point1, Point2, (0, 255, 0), 2)
     
    #Show Image
    cv2.imshow("frame_ROI",frame_ROI)
    cv2.imshow("frame", frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()
