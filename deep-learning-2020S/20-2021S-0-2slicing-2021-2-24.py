"""
Program: 2slicing.py
Coded by: HL
Date: Feb. 2019
Status: Debug
Version: 1.0
Note: NP slicing 
Slicing arrays, e.g., taking elements from one given index to another given index.
(1) pass slice instead of index as: [start:end].
(2) define the step like: [start:end:step].
(3) if we don't pass start its considered 0, and 
If we don't pass end its considered length of array in that dimension, and
If we don't pass step its considered 1
ref: https://www.w3schools.com/python/numpy_array_slicing.asp 
"""
import sys
import numpy as np
 
#================
# Slicing 1D tensor, float 32 or float 64 for np
x = np.array([5,6,13,-2.1,100])  
print ('x')
print (x)

print ('slicing: [start:end] = [1:3]')
print (x[1:3])

print ('Negative slicing: [-start:-end] start counting from the end = [-3:-1]')
print (x[-3:-1])

print ('step: [start:end:step] = [1:5:2]')
print (x[1:5:2])
print ('step: [start:end:step] = [::2]')
print (x[::2])

y = x.ndim
print ('vector x dimension')
print (y)

print ('---------------------\n')
#================
# Slicing 2D tensor, float 32 or float 64 for np
x = np.array([[5,6,13,-2.1],
              [0,1,-1.1,0.1],
              [2,1,-1, 0.15]])   
print ('2D tensor x')
print (x)

print ('slicing:  [row, start:end] = [0, 1:3]')
print (x[0,1:3]) 
 
print ('step: [row, start:end:step] = [0, ::2]')
print (x[0,::2])

y = x.ndim
print ('vector x dimension')
print (y)

print ('---------------------\n')

#================
# 3D tensor, float 32 or float 64 for np
x = np.array([[[0,1,2,3],
               [4,5,6,7],
               [8,9,10,11]],
             [[12,13,14,15],
              [16,17,18,19],
              [20,21,22,23]], 
             [[24,25,26,27],
              [28,29,30,31],
              [32,33,34,35]]])  
print ('3D tensor x')
print (x)

print ('slicing:  [index2D, index1D(row), start:end] = [0,1, 1:3]')
print (x[0,1,1:3]) 
 
''' 
now, [::1] to select all matrices, and all rows, and col 1
'''
print ('slicing:  [index2D, index1D(row), start:end] = [::2]')
print (x[::2]) 

print ('slicing:  [index2D, index1D(row), start:end] = [::,2]')
print (x[::,2]) 

''' 
now, [::1] to select all matrices, and all rows, and col
'''

#print ('step: [index2D, index1D(row), start:end:step] = [0,1, ::2]')
#print (x[0,::2])

y = x.ndim
print ('vector x dimension')
print (y)

'''
Note: NumPy arrays iterate over the left-most axis first.
https://stackoverflow.com/questions/28010860/slicing-3d-numpy-arrays/28010900


'''

#if src is None:
#   print ('Error opening image!')
#   print ('Usage: pdisplay.py image_name\n')

#while True: 
#    c = cv2.waitKey(500)
#    if c == 27:
#       break

 
