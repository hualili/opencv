#!/usr/bin/python2.7

#input image
MyTestImage = [[100,100,100], [100,100,100], [100,100,100]]
ImageHight = len(MyTestImage)
ImageWidth = len(MyTestImage[0])

#refer to slide about padding size
#padding size is (k-1)/2
def paddingimage(image, ksize):
    assert(ksize % 2 != 0)  #ensure k is odd number
    paddingsize = (ksize - 1)/2
    #assure image is 2D list
    ImageWidth = len(image)
    ImageHeight = len(image[0])

    output = [[0 for x in range(ImageWidth + 2 * paddingsize)] for y in range(ImageHight + 2 * paddingsize)]

    for i in range(ImageWidth):
        for j in range(ImageHeight):
             output[i + paddingsize][ j + paddingsize] = image[i][j]
    return output

Myoutput = paddingimage(MyTestImage, 3)
print Myoutput


