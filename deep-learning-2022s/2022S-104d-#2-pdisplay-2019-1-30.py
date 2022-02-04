"""
pdisplay.py
Demo read and display image
"""
import sys
import cv2
import numpy as np

#main(sys.argv[1:])
window_name = 'Display Image'
 
imageName = sys.argv[1] #get file name from command line 

src = cv2.imread(imageName, cv2.IMREAD_COLOR)

if src is None:
   print ('Error opening image!')
   print ('Usage: pdisplay.py image_name\n')
  
ind = 0

while True: 
    cv2.imshow(window_name, src)

    c = cv2.waitKey(500)
    if c == 27:  #ESC
       break

    ind += 1

 
