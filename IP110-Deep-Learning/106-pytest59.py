#!/usr/bin/python2.7
import math

def LoG2d(x, y, sigma):
    xyp2 = x ** 2 + y ** 2
    LoG = ((xyp2 - 2 * sigma**2) /(math.sqrt(2 * math.pi) * math.pow(sigma, 5))) * math.pow(math.e, -xyp2 / (2 * sigma**2))
    return LoG

#since it is symetric kernel, we can reduce caculation
def KernelLoG2(sigma, size, kernel):
    assert ((size % 2) != 0)
    for i in range(size/2 + 1):
        for j in range(i + 1):
            kernel[i + size/2 ][j + size/2] = LoG2d(i,j,sigma)

            if (i == 0):  # seed position.
                continue

            if (j != 0):  # need to change sign of j
                kernel[-i + size / 2][-j + size / 2] = kernel[i + size / 2][j + size / 2]
                kernel[i + size / 2][-j + size / 2] = kernel[i + size/2 ][j + size/2]

            kernel[-i + size / 2][j + size / 2] = kernel[i + size / 2][j + size / 2]

            if (i != j):  # need to exchange the place
                kernel[j + size / 2][i + size / 2] = kernel[i + size / 2][j + size / 2]
                kernel[j + size / 2][-i + size / 2] = kernel[i + size / 2][j + size / 2]

                if (j != 0):
                    kernel[-j + size / 2][i + size / 2] = kernel[i + size / 2][j + size / 2]
                    kernel[-j + size / 2][-i + size / 2] = kernel[i + size / 2][j + size / 2]

# refer to slide about padding size
# padding size is (k-1)/2
def paddingimage(image, ksize):
    assert (ksize % 2 != 0)  # ensure k is odd number
    paddingsize = (ksize - 1) / 2
    # assure image is 2D list
    ImageWidth = len(image)
    ImageHeight = len(image[0])

    output = [[0 for x in range(ImageWidth + 2 * paddingsize)] for y in
              range(ImageHeight + 2 * paddingsize)]

    for i in range(ImageWidth):
        for j in range(ImageHeight):
            output[i + paddingsize][j + paddingsize] = image[i][j]
    return output


#define a function to return a convolution result with kernel.
#we give start point of input image, we do the convolution with a Kernel
def elementmult(startx, starty, image, kernel):
    result = 0
    for i in range(len(kernel)):   # row
        for j in range(len(kernel[0])): #col
            result += float(image[startx+i][starty+j]) * kernel[i][j]
    return result

if __name__ == "__main__":
    KernelSize = 3
    MyKernel = [[0 for x in range(KernelSize)] for y in range(KernelSize)]
    Sigma = 1.8
    #create LoG Kerenl
    KernelLoG2(Sigma, KernelSize, MyKernel)
    print MyKernel

    KernelHight = len(MyKernel)
    KernelWidth = len(MyKernel[0])

    #input image
    InputImage = [[0,100,100], [0,100,100], [0,100,100]]

    MyTestImage = paddingimage(InputImage, KernelSize)

    ImageHight = len(MyTestImage)
    ImageWidth = len(MyTestImage[0])


    #create a 2d array in python, please see slides
    # output size = ((input size - kernel size) + 2 padding size)/stride size + 1
    # padding size = 0, stride size = 1
    # output size = ((input size - kernel size) + 1
    output = [[0 for x in range(ImageWidth - KernelWidth + 1)] for y in range(ImageHight - KernelHight + 1)]

    for i in range(ImageHight - KernelHight + 1):
        for j in range(ImageWidth - KernelWidth + 1):
            output[i][j] = elementmult(i, j, MyTestImage, MyKernel)

    print output


    '''
    [[-0.06946788034149066, -0.09915333938923544, -0.06946788034149066], 
    [-0.09915333938923544, -0.13681148161914702, -0.09915333938923544], 
    [-0.06946788034149066, -0.09915333938923544, -0.06946788034149066]]

    [[-16.86212197307261, -40.458604073910855, -40.458604073910855], 
    [-23.808910007221677, -57.32072604698347, -57.320726046983474], 
    [-16.86212197307261, -40.458604073910855, -40.45860407391086]]

    '''