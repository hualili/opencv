#!/usr/bin/python2.7

MyFirstKernel = [[1.0, 1.0, 1.0], [0., 0., 0.], [-1.0, -1.0, -1.0]]
MyTestImage = [[100,101,100,100,100], [100,100,100,100,100],[100,100,100,100,100],[100,100,100,100,100],[100,100,100,100,100]]

KernelHight = len(MyFirstKernel)
KernelWidth = len(MyFirstKernel[0])

ImageHight = len(MyTestImage)
ImageWidth = len(MyTestImage[0])

#create a 2d array in python, please see slides
# output size = ((input size - kernel size) + 2 padding size)/stride size + 1
# padding size = 0, stride size = 1
# output size = ((input size - kernel size) + 1
output = [[0 for x in range(ImageWidth - KernelWidth + 1)] for y in range(ImageHight - KernelHight + 1)]

#define a function to return a convolution result with kernel.
#we give start point of input image, we do the convolution with a Kernel

def conv(startx, starty):
    result = 0
    for i in range(KernelHight):
        for j in range(KernelWidth):
            result += float(MyTestImage[startx+i][starty+j]) * MyFirstKernel[i][j]
    return result

#don't forget do this in order to share you functions with others
if __name__ == "__main__":
    for i in range(ImageHight - KernelHight + 1):
        for j in range(ImageWidth - KernelWidth + 1):
            output[i][j] = conv(i, j)
    print output


