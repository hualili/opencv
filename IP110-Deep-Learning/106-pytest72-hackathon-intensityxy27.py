#!/usr/bin/python2.7

#input most likely is read from a file
#so it is okay put them in a list
#we will implement readfile in the future to read in data
inputImagelist  = [
                   [100,100,0,0,    100,100,0,0,    100,100,0,0,     100,100,0,0],
                   [100,100,100,0,  100,100,0,0,    100,100,0,0,     100,100,0,0],
                   [100,100,100,0,  100,100,100,0,  100,100,0,0,     100,100,0,0],
                   [100,100,100,0,  100,100,100,0,  100,100,100,0,   100,100,0,0],
                   [100,100,100,0,  100,100,100,0,  100,100,100,0,   100,100,100,0],
                   [0,100,100,0,    100,100,100,0,  100,100,100,0,   100,100,100,0],
                   [0,100,100,0,    0,100,100,0,    100,100,100,0,   100,100,100,0],
                   [0,100,100,0,    0,100,100,0,    0,100, 100, 0,   100,100,100,0],
                   [0,100,100,0,    0,100,100,0,    0,100, 100, 0,   0,  100,100,0]
    # [1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0],
    # [1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0],
    # [1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0],
    # [1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0],
    # [1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0],
    # [0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0],
    # [0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0],
    # [0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0],
    # [0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0]
                   ]
desiredValues = [
                 [0,1,1,0,  0,1,1,0, 0,1,1,0,  0,1,1,0],
                 [0,0,1,1,  0,1,1,0, 0,1,1,0,  0,1,1,0],
                 [0,0,1,1,  0,0,1,1, 0,1,1,0,  0,1,1,0],
                 [0,0,1,1,  0,0,1,1, 0,0,1,1,  0,1,1,0],
                 [0,0,1,1,  0,0,1,1, 0,0,1,1,  0,0,1,1],
                 [1,1,1,1,  0,0,1,1, 0,0,1,1,  0,0,1,1],
                 [1,1,1,1,  1,1,1,1, 0,0,1,1,  0,0,1,1],
                 [1,1,1,1,  1,1,1,1, 1,1,1,1,  0,0,1,1],
                 [1,1,1,1,  1,1,1,1, 1,1,1,1,  1,1,1,1]
                 ]

# set some variable. fix: will be parameters given by users.
imageSize = 4
kernelSize = 3
expandSize = 6   #imageSize + 2 * (kernelSize/2)
gain = 0.01
epoch = 100000


#we shall get 9 elements from image based on start position
def getsubImage(image, px, py):
    myElements = []
    startPosition = expandSize * py + px
    for i in range(kernelSize):
        for j in range(kernelSize):
            myElements.append(image[startPosition + i * expandSize + j])
    return myElements

def LinearFunc(W, X, b):
    Score = 0.0
    for i in range(len(W)):
        Score += float(W[i]) * float(X[i])
    Score = Score + b
    return Score

def Sign(Score):
    if Score > 0:
        return 1.0
    else:
        return 0.0

def Cost(D, Y):  #D: for desired value, Y: from Sign fucntion
    return (D-Y)

def updateW(W, X, gain, cost):
    for i in range(len(W)):
        W[i] = W[i] + gain * cost * X[i]

#expand image 4x4 to 6x6 so we can do convolution to get 4x4 output
#currently we can not do regular padding which only add 0 on the boundaries
#we need add correspoding intensity values
def expandImage(image):
    operationalInput = []
    inputImage = []
    #expand right and left intensity column
    for i in range(imageSize):
        for j in range(imageSize):
            if j == 0:
                operationalInput.append(image[i * imageSize + j])
            if j == imageSize - 1:
                operationalInput.append(image[i * imageSize + j])
            operationalInput.append(image[i * imageSize + j])
    #print operationalInput

    #expand first intensity row
    for i in range(expandSize):
        inputImage.append(operationalInput[i])
    #keep middle rows
    for i in range(imageSize):
        for j in range(expandSize):
            inputImage.append(operationalInput[i * expandSize + j])
    #add last row
    for i in range(expandSize):
        inputImage.append(operationalInput[(imageSize-1) * expandSize + i])

    return inputImage

if __name__ == "__main__":
    #initalization W and b
    # W has 27 elements, 9 for x0, x1 for location, 9 for intensity
    W = [0.5 for _ in range(27)]
    bias = 0.5

    updateCount = 0

    #create a intensity poistion x, y list (x0, x1)
    X0 = []
    X1 = []
    for i in range(expandSize):
        for j in range(expandSize):
            X0.append(j)
            X1.append(i)

    #create input list we need...
    imageTotal = len(inputImagelist)
    XList = []
    DList = []
    for imageNo in range(imageTotal):
        inputImage = expandImage(inputImagelist[imageNo])
        D = desiredValues[imageNo]
        print inputImage, D
        for i in range(imageSize):
            for j in range(imageSize):
                # will be (0,0), (0,1), (0,2),(0,3)
                myIntensity = getsubImage(inputImage, j, i)
                myX0 = getsubImage(X0, j, i)
                myX1 = getsubImage(X1, j, i)

                myX = []
                for a, b, c in zip(myX0, myX1, myIntensity):
                    myX.append(a)
                    myX.append(b)
                    myX.append(c)
                # it shall be able to match Dr. Li's notes
                desiredCost = D[i * imageSize + j]
                print "input Intensity =", myIntensity, "Desired = ", desiredCost
                XList.append(myX)
                DList.append(desiredCost)
    print "input XList",len(XList), "=", XList
    print "Desired = ",len(DList), "=", DList

    for _ in range(epoch):
        for Xij, d in zip(XList, DList):
            myScore = LinearFunc(W, Xij, bias)
            mySign = Sign(myScore)
            myCost = Cost(d, mySign)

            updateW(W, Xij, gain, myCost)

            if updateCount % 10000 == 0:
                print "update count:", updateCount, "gain=", gain, "W=", W

            # if updateCount % 1000000 == 0:
            #     if gain > 0.001:
            #         gain = 0.1 * gain
            #         print "make gain smaller", gain

            updateCount += 1
