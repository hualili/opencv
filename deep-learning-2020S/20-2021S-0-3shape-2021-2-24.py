"""
Program: 2slicing.py
Coded by: HL
Date: Feb. 2019
Status: Debug
Version: 1.0
Note: NP shape and reshape 
ref: https://www.w3schools.com/python/numpy_array_shape.asp
Gives a new shape to an array without changing its data (reshape)
https://numpy.org/doc/stable/reference/generated/numpy.reshape.html
"""
import sys
import numpy as np
 
#================
# shape 1D tensor
x = np.array([5,6,13,-2.1,100])  
print ('x')
print (x)

print ('x shape')
print (x.shape)

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

print ('x shape')
print (x.shape)


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

print ('x shape')
print (x.shape)

#print ('step: [index2D, index1D(row), start:end:step] = [0,1, ::2]')
#print (x[0,::2])

y = x.ndim
print ('vector x dimension')
print (y)

print ('---------------------\n')
'''
Note: NumPy arrays iterate over the left-most axis first.
https://stackoverflow.com/questions/28010860/slicing-3d-numpy-arrays/28010900
'''
#====================
# reshape 
x = np.array([0,1,2,3,4,5])  
print ('x')
print (x)

print ('x shape')
print (x.shape)

print ('x.reshape((3,2))\n')
y = x.reshape((3, 2))

print ('y')
print (y)
print ('y shape')
print (y.shape)
 
