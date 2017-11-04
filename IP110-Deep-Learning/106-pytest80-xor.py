#!/usr/bin/python2.7
import numpy as np
learning_rate = 1
epochs = 100000          # Number of iterations
stopError = 0.001
#define layout of network.
inputLayerSize, hiddenLayerSize, outputLayerSize = 2, 3, 1

# input pairs 4 x 2 array define in numpy 
X = np.array([[0,0], [0,1], [1,0], [1,1]])
# desired output 4 x 1 arrary 
D = np.array([ [0],   [1],   [1],   [0]])
 
#activation function sigmoid
def sigmoid (x): 
	return 1/(1 + np.exp(-x))     

# derivative of sigmoid 
def sigmoid_derivative(x): 
	return x * (1 - x)

if __name__ == "__main__":
    # initialization of weights on each layer
    # weights between input layer and hidden layer: 2 x 3 in our case
    Weightsi_h = np.random.uniform(size=(inputLayerSize, hiddenLayerSize))
    # weights between hidden layer and output layer: 3 x 1
    Weightsh_o = np.random.uniform(size=(hiddenLayerSize,outputLayerSize))

    for i in range(epochs):
        # forward path
        # dot product between X (4 x 2) and Weightsi_h (2 x 3): generate (4 x 3) array
        hiddenLayerOutput = sigmoid(np.dot(X, Weightsi_h))
        # dot product between hiddent layer output (4 x 3) and weightsh_o (3 x 1): generate (4 x 1) array
        outputLayerOutput = sigmoid(np.dot(hiddenLayerOutput, Weightsh_o))

        # how much we missed (error)
        # E is error, define as (di - yi), yi = outputLayerOutput D is desired output
        # E is an (4 x 1) array
        E = D - outputLayerOutput

        # if we reach to small difference, we can stop training
        currentError = np.sum(np.square(E)) / float(len(X))
        if (currentError < stopError):
            print "Reach to desired accuracy at epoch:", i
            break
        # output layer error delta  : yi * (1 - yi) * (di - yi),  yi = outputLayerOutput
        # dEatoutputLayer is an (4 x 1) array
        dEatoutputLayer = E * sigmoid_derivative(outputLayerOutput)

        # delta W for weights between hidden layer and output layer
        # formula: delta_wji =  n * Ej * oi
        # n : learning rate
        # Ej: error next layer (output layer) as inputs
        # oi: output from current node
        # hiddenLayerOutput (4 x 3) array, transpose (3 x 4)
        # dEatoutputLayer is an (4 x 1) array. will generate an (3 x 1) array
        dWeightsh_o = learning_rate * hiddenLayerOutput.T.dot(dEatoutputLayer)

        # hiddlen layer error delta formula: oi * (1 - oi) * sum(delta_error * w)
        # oi: is output from current node i
        # delta error : next layer errors (output layer)
        # w: weights between current layer to next layer (hidden to output layer)
        # idea is to calculate delta errors from next layer into this node (or current layer's nodes)
        # (4 x 1) * (3 x 1).T -> (4 x 3) *  (4 x 3)
        dEathiddenLayer = dEatoutputLayer.dot(Weightsh_o.T) * sigmoid_derivative(hiddenLayerOutput)

        # delta W for weights between hidden layer and input layer
        # X (4*2).T -> (2 * 4) dot dEathiddenLayer (4 x 3) -> an (2 x 3) array.
        dWeightsi_h = learning_rate * X.T.dot(dEathiddenLayer)

        # update output and hidden layer weights
        Weightsh_o += dWeightsh_o
        Weightsi_h += dWeightsi_h

    print(outputLayerOutput)
