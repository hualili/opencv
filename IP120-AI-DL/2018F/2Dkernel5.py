#!/usr/bin/python2.7
# demo for stride, padding, and convolution dimension 
MyFirstKernel = [[1.0, 1.0, 1.0], [0., 0., 0.], [-1.0, -1.0, -1.0]]
MyTestImage = [[100,100,100,100,100], [100,100,100,100,100],[100,100,100,100,100],[100,100,100,100,100],[100,100,100,100,100]]

KernelHight = len(MyFirstKernel)
KernelWidth = len(MyFirstKernel[0])

ImageHight = len(MyTestImage)
ImageWidth = len(MyTestImage[0])

#create a 2d array in python, please see slides
# output size = ((input size - kernel size) + 2 padding size)/stride size + 1
# padding size = 0, stride size = 1
# output size = ((input size - kernel size) + 1
output = [[0 for x in range(ImageWidth - KernelWidth + 1)] for y in range(ImageHight - KernelHight + 1)]

print (output) 
