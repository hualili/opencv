'''
HL 
display video from file
'''
import sys
import cv2
import numpy as np

#main(sys.argv[1:])
window_name = 'video_gray'
window_name = 'video_color'
 
videoName = sys.argv[1] #get file name from command line 

#cap = cv2.VideoCapture('vtest.avi')
cap = cv2.VideoCapture(videoName)

import time

while(cap.isOpened()):
    ret, frame = cap.read()

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    cv2.imshow('video_color',frame)
    cv2.imshow('video_gray',gray)

    time.sleep(.03)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
