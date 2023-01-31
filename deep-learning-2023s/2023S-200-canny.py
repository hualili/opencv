# OpenCV program to perform Edge detection in real time 
# import libraries of python OpenCV  
# where its functionality resides 
import cv2  
  
# np is an alias pointing to numpy library 
import numpy as np

img = input('Enter image file name:')

frame = cv2.imread(img, cv2.IMREAD_COLOR)

if frame is None:
    print('Error opening image!')
    print('Usage: pdisplay.py image_name\n')

# capture frames from a camera 
# cap = cv2.VideoCapture(0)

# loop runs if capturing has been initialized 
while(1): 
  
    # reads frames from a camera 
    # ret, frame = cap.read()
  
    # Display an original image 
    cv2.imshow('Original',frame) 
  
    # finds edges in the input image image and 
    # marks them in the output map edges 
    edges = cv2.Canny(frame,100,200) 
  
    # Display edges in a frame 
    cv2.imshow('Edges',edges) 
  
    # Wait for Esc key to stop 
    k = cv2.waitKey(5) & 0xFF
    if k == 27: 
        break

# Close the window 
cap.release() 
  
# De-allocate any associated memory usage 
cv2.destroyAllWindows()  

