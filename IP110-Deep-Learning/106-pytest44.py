#!/usr/bin/python2.7
MyFirstKernel = [[1.0, 1.0, 1.0], [0., 0., 0.], [-1.0, -1.0, -1.0]]
MyTestImage = [[100,101,100,100,100], [100,100,100,100,100],[100,100,100,100,100],[100,100,100,100,100],[100,100,100,100,100]]

KernelHight = len(MyFirstKernel)
KernelWidth = len(MyFirstKernel[0])

for i in range(KernelHight):
    for j in range(KernelWidth):
        print i,j, "=", MyFirstKernel[i][j]


ImageHight = len(MyTestImage)
ImageWidth = len(MyTestImage[0])

for i in range(ImageHight):
    for j in range(ImageWidth):
        print i,j, "=", MyTestImage[i][j]




