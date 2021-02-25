"""
Program: 1-pythonTF.py
Coded by: HL
Date: Feb. 2019
Status: Debug
Version: 1.0
Note: Tensors and their dimension for NN
Ref: Deep Learning with Python by F. Chollet
"""
import sys
import cv2
import numpy as np

#================
# scalar, float 32 or float 64 for np
x = np.array(5)  
print ('scalr x')
print (x)
y = x.ndim
print ('scalr x dimension')
print (y)

#================
# 1D tensor, float 32 or float 64 for np
x = np.array([5,6,13,-2.1])  
print ('1D tensor x')
print (x)
y = x.ndim
print ('vector x dimension')
print (y)

#================
# 2D tensor, float 32 or float 64 for np
x = np.array([[5,6,13,-2.1],
              [0,1,-1.1,0.1],
              [2,1,-1, 0.15]])   
print ('2D tensor x')
print (x)
y = x.ndim
print ('vector x dimension')
print (y)

#================
# 3D tensor, float 32 or float 64 for np
x = np.array([[[5,6,13,-2.1],
              [0,1,-1.1,0.1],
              [2,1,-1, 0.15]],
             [[5,6,20,-2.1],
              [0,1,-1.1,0.1],
              [2,1,-1, 0.15]], 
             [[5,6,40,-2.1],
              [0,1,-2.1,0.1],
              [2,1,-6,0.15]]])  
print ('3D tensor x')
print (x)
y = x.ndim
print ('vector x dimension')
print (y)



#if src is None:
#   print ('Error opening image!')
#   print ('Usage: pdisplay.py image_name\n')

#while True: 
#    c = cv2.waitKey(500)
#    if c == 27:
#       break

 
