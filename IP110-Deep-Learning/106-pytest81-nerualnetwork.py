
import numpy as np
learning_rate = 1
epochs = 100000          # Number of iterations
stopError = 0.0001
#define layout of network.
inputLayerSize, hiddenLayerSize, outputLayerSize = 2, 5, 2

# input pairs 9 x 2 array define in numpy 
X = np.array([[1,1], [2,1], [4,1], [3,3], [4,4], [4,5], [1,3],[1,4],[1,5]])
# desired output 9 x 2 arrary 
D = np.array([ [1,1],[1,1], [1,1], [0,1], [0,1], [0,1], [1,0],[1,0],[1,0]])
 
#activation function sigmoid
def sigmoid (x): 
	return 1/(1 + np.exp(-x))     

# derivative of sigmoid 
def sigmoid_derivative(x): 
	return x * (1 - x)

if __name__ == "__main__":
    #init weights
    Weightsi_h = np.random.uniform(size=(inputLayerSize, hiddenLayerSize))
    Weightsh_o = np.random.uniform(size=(hiddenLayerSize,outputLayerSize))

    for i in range(epochs):
        #forward path
        hiddenLayerOutput = sigmoid(np.dot(X, Weightsi_h))
        #print hiddenLayerOutput.shape
        #print hiddenLayerOutput

        outputLayerOutput = sigmoid(np.dot(hiddenLayerOutput, Weightsh_o))
        #print outputLayerOutput

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
        dWeightsh_o = learning_rate * hiddenLayerOutput.T.dot(dEatoutputLayer)
        #print dWeightsh_o

        #step 3, caculate delta E for hidden layers
        dEathiddenLayer = dEatoutputLayer.dot(Weightsh_o.T) * sigmoid_derivative(hiddenLayerOutput)
        #print dEathiddenLayer

        #determine delta weights between hidden layer and input layer
        dWeightsi_h = learning_rate * X.T.dot(dEathiddenLayer)

        #update output and hidden layer weights
        Weightsh_o +=  dWeightsh_o
        Weightsi_h +=  dWeightsi_h

    print(outputLayerOutput)
