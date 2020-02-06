'''
'''
import numpy as np
import cv2

cap = cv2.VideoCapture(0)

while(True):

    ret, frame = cap.read() 

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    edges = cv2.Canny(gray,100,200)

    cv2.imshow('original',frame)
    cv2.imshow('gray scale',gray)
    cv2.imshow('Canny edges',edges)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
 
cap.release()
cv2.destroyAllWindows()
