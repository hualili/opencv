#hidden outputs are 1's, so we can't learn.
import numpy as np
learning_rate = 1
momentum = 0.9

epochs = 1     # Number of iterations
stopError = 0.0001
#define layout of network.
inputLayerSize, hiddenLayerSize, outputLayerSize = 27, 100, 1

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

    # create input list we need...
    imageTotal = len(inputImagelist)
    XList = []
    DList = []
    for imageNo in range(imageTotal):
        inputImage = expandImage(inputImagelist[imageNo])
        DV = desiredValues[imageNo]
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
                desiredCost = DV[i * imageSize + j]
                # print "input Intensity =", myIntensity, "Desired = ", desiredCost
                XList.append(myX)
                DList.append(desiredCost)
    print "input XList", len(XList), "=", XList
    print "Desired = ", len(DList), "=", DList

    X = np.array(XList)
    D = np.array(DList)
    D = D.reshape(144,1)

    #init weights and old weights
    Weightsi_h = np.random.uniform(size=(inputLayerSize, hiddenLayerSize))
    lastdeltaWeightsi_h =np.zeros(shape=(inputLayerSize, hiddenLayerSize))

    Weightsh_o = np.random.uniform(size=(hiddenLayerSize,outputLayerSize))
    lastdeltaWeightsh_o = np.zeros(shape=(hiddenLayerSize,outputLayerSize))

    for i in range(epochs):
        #forward path
        hiddenLayerOutput = sigmoid(np.dot(X, Weightsi_h))
        print "weights", Weightsi_h
        print np.dot(X, Weightsi_h)
        print hiddenLayerOutput
        outputLayerOutput = sigmoid(np.dot(hiddenLayerOutput, Weightsh_o))
        print outputLayerOutput

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

    print(outputLayerOutput)
