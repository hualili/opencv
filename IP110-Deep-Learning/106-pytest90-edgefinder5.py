# with differentiating 100 from -100 and 0, we actually make data set more separable by a simpler function.
# it is easier to make them apart and so this model converges
import numpy as np
learning_rate = 0.001
momentum = 0.9

epochs = 10000 # Number of iterations
stopError = 0.00001
#define layout of network.
inputLayerSize, hiddenLayerSize, outputLayerSize = 27, 200, 2

imageSize = 4
kernelSize = 3
expandSize = 6   #imageSize + 2 * (kernelSize/2)

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
                   ]
desiredValues = [
                 [0,-1,-1,0,  0,-1,-1,0, 0,-1,-1,0,  0,-1,-1,0],
                 [0,0,-1,-1,  0,-1,-1,0, 0,-1,-1,0,  0,-1,-1,0],
                 [0,0,-1,-1,  0,0,-1,-1, 0,-1,-1,0,  0,-1,-1,0],
                 [0,0,-1,-1,  0,0,-1,-1, 0,0,-1,-1,  0,-1,-1,0],
                 [0,0,-1,-1,  0,0,-1,-1, 0,0,-1,-1,  0,0,-1,-1],
                 [1,1,-1,-1,  0,0,-1,-1, 0,0,-1,-1,  0,0,-1,-1],
                 [1,1,-1,-1,  1,1,-1,-1, 0,0,-1,-1,  0,0,-1,-1],
                 [1,1,-1,-1,  1,1,-1,-1, 1,1,-1,-1,  0,0,-1,-1],
                 [1,1,-1,-1,  1,1,-1,-1, 1,1,-1,-1,  1,1,-1,-1]
                 ]

#we shall get 9 elements from image based on start position
def getsubImage(image, px, py):
    myElements = []
    startPosition = expandSize * py + px
    for i in range(kernelSize):
        for j in range(kernelSize):
            myElements.append(image[startPosition + i * expandSize + j])
    return myElements

# set some variable. fix: will be parameters given by users.

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

#activation function sigmoid
def sigmoid (x): 
	return 1/(1 + np.exp(-x))     

# derivative of sigmoid 
def sigmoid_derivative(x): 
	return x * (1 - x)

if __name__ == "__main__":
    #create a intensity poistion x, y list (x0, x1)
    X0 = []
    X1 = []
    for i in range(expandSize):
        for j in range(expandSize):
            X0.append(j)
            X1.append(i)
    # input data preprocessing. normalize them.
    minX0 = min(X0)
    maxX0 = max(X0)
    midX = (maxX0-minX0)/2.0
    X0 = [(x-midX)/midX for x in X0]
    X1 = [(x-midX)/midX for x in X1]

    minIntensity = min(inputImagelist[0])
    maxIntensity = max(inputImagelist[0])
    midIntensity = (maxIntensity - minIntensity) / 2.0

    # create input list we need...
    imageTotal = len(inputImagelist)
    XList = []
    DList = []
    for imageNo in range(imageTotal):
        inputImage = expandImage(inputImagelist[imageNo])
        inputImage = [(x- midIntensity)/midIntensity for x in inputImage]
        DV = desiredValues[imageNo]
        for i in range(imageSize):
            for j in range(imageSize):
                # will be (0,0), (0,1), (0,2),(0,3)
                myIntensity = getsubImage(inputImage, j, i)
                myX0 = getsubImage(X0, j, i)
                myX1 = getsubImage(X1, j, i)

                myX = []
                for xp, yp, intensity in zip(myX0, myX1, myIntensity):
                    myX.append(xp)
                    myX.append(yp)
                    myX.append(intensity)

                desiredOutput = DV[i * imageSize + j]
                if desiredOutput == 1:
                    desiredOutput2bits = [1, 0]
                elif desiredOutput == -1:
                    desiredOutput2bits = [0, 1]
                else:
                    desiredOutput2bits = [0, 0]
                # print "input Intensity =", myIntensity, "Desired = ", desiredCost
                XList.append(myX)
                DList.append(desiredOutput2bits)

    #print "input XList", len(XList), "=", XList
    #print "Desired = ", len(DList), "=", DList

    X = np.array(XList)
    #print X
    #mid_array = np.array([2.5, 2.5, 50,2.5, 2.5, 50,2.5, 2.5, 50,2.5, 2.5, 50,2.5, 2.5, 50,2.5, 2.5, 50,2.5, 2.5, 50,2.5, 2.5, 50,2.5, 2.5, 50])
    #X = (X - mid_array)/mid_array
    #print "X=", X

    D = np.array(DList)
    #print "D=", D

    #init weights and old weights
    Weightsi_h = np.random.uniform(-1, 1, size=(inputLayerSize, hiddenLayerSize))
    lastdeltaWeightsi_h =np.zeros(shape=(inputLayerSize, hiddenLayerSize))

    Weightsh_o = np.random.uniform(-1, 1, size=(hiddenLayerSize,outputLayerSize))
    lastdeltaWeightsh_o = np.zeros(shape=(hiddenLayerSize,outputLayerSize))

    for i in range(epochs):
        #forward path
        hiddenLayerOutput = sigmoid(np.dot(X, Weightsi_h))
        #print "hidden=", hiddenLayerOutput
        outputLayerOutput = sigmoid(np.dot(hiddenLayerOutput, Weightsh_o))
        #print "output=", outputLayerOutput

        #error (delta error) /cost /loss
        E = D - outputLayerOutput
        #determine if we have reached desired accuracy
        currentError = np.sum(np.square(E)) /float(len(X))
        if (currentError < stopError):
            print "Reach to desired accuracy at epoch:", i
            break

        #step 1, output layer's error
        dEatoutputLayer = E * sigmoid_derivative(outputLayerOutput)
        #print dEatoutputLayer

        #step 2, determine delta weights between hidden layer and output layer
        dWeightsh_o = learning_rate * hiddenLayerOutput.T.dot(dEatoutputLayer) + momentum * lastdeltaWeightsh_o
        #print dWeightsh_o
        #save current to be old
        lastdeltaWeightsh_o = dWeightsh_o

        #step 3, caculate delta E for hidden layers
        dEathiddenLayer = dEatoutputLayer.dot(Weightsh_o.T) * sigmoid_derivative(hiddenLayerOutput)
        #print dEathiddenLayer

        #determine delta weights between hidden layer and input layer
        dWeightsi_h = learning_rate * X.T.dot(dEathiddenLayer) + momentum * lastdeltaWeightsi_h
        lastdeltaWeightsi_h = dWeightsi_h

        #update output and hidden layer weights
        Weightsh_o +=  dWeightsh_o
        Weightsi_h +=  dWeightsi_h

    print "Error =", currentError

    #test result
    testImage = [100,100,0,0,    100,100,0,0,    100,100,0,0,     100,100,0,0]
    print "test image:"
    print testImage
    ExpandedtestImage = expandImage(testImage)
    RealtestImage = [(x - midIntensity) / midIntensity for x in ExpandedtestImage]
    testXList = []
    for i in range(imageSize):
        for j in range(imageSize):
            # will be (0,0), (0,1), (0,2),(0,3)
            testIntensity = getsubImage(RealtestImage, j, i)
            testX0 = getsubImage(X0, j, i)
            testX1 = getsubImage(X1, j, i)

            myX = []
            for xp, yp, intensity in zip(testX0,testX1,testIntensity):
                myX.append(xp)
                myX.append(yp)
                myX.append(intensity)
            testXList.append(myX)
    #print testXList
    X = np.array(testXList)
    
    # forward path
    hiddenLayerOutput = sigmoid(np.dot(X, Weightsi_h))
    # print "hidden=", hiddenLayerOutput
    outputLayerOutput = sigmoid(np.dot(hiddenLayerOutput, Weightsh_o))
    # print "output=", outputLayerOutput

    # we can use allclose instead of this, but I want to see if there is any data in between
    for i in range(outputLayerOutput.shape[0]):  #16
        for j in range(outputLayerOutput.shape[1]): # 2
            if outputLayerOutput[i][j] > 0.98:
                outputLayerOutput[i][j] = 1
            if outputLayerOutput[i][j] < 0.02:
                outputLayerOutput[i][j] = 0
    print outputLayerOutput

    outputList = []
    for i in range(outputLayerOutput.shape[0]):  # 16
        if (outputLayerOutput[i] == np.array([1., 0.])).all():
            outputList.append(100)
            continue
        if (outputLayerOutput[i] == np.array([0., 1.])).all():
            outputList.append(-100)
            continue
        outputList.append(0)

    #print outputList
    outputimage = np.array(outputList)
    outputimage = outputimage.reshape(4,4)
    print outputimage