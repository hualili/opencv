# with differentiating 100 from -100 and 0, we actually make data set more separable by a simpler function.
# it is easier to make them apart and so this model converges

import tensorflow as tf
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
                desiredOutputlist =[]
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
    print "input XList", len(XList), "=", XList
    print "Desired = ", len(DList), "=", DList

    X = np.array(XList)
    mid_array = np.array([2.5, 2.5, 50, 2.5, 2.5,50, 2.5, 2.5, 50,
                          2.5, 2.5, 50, 2.5, 2.5, 50, 2.5, 2.5, 50,
                          2.5, 2.5, 50, 2.5, 2.5, 50, 2.5, 2.5, 50])

    X = (X - mid_array)/mid_array
    #print "X=", X
    D = np.array(DList)
    #print "D=", D

    #init weights and old weights
    Weightsi_h = tf.Variable(tf.truncated_normal((inputLayerSize, hiddenLayerSize), mean=0.0, stddev=0.5, dtype=tf.float32, seed=None, name=None))
    Weightsh_o = tf.Variable(tf.truncated_normal((hiddenLayerSize,outputLayerSize), mean=0.0, stddev=0.5, dtype=tf.float32, seed=None, name=None))

    #inputs and desired output
    tensorX = tf.placeholder(tf.float32, (None, 27),"X")
    tensorD = tf.placeholder(tf.float32, (None, 2), "D")

    # Create model
    hidden_output = tf.sigmoid(tf.matmul(tensorX, Weightsi_h))
    output_output = tf.sigmoid(tf.matmul(hidden_output, Weightsh_o))

    # Define loss and optimizer
    loss_op = tf.reduce_mean(tf.nn.sigmoid_cross_entropy_with_logits(
        logits=output_output, labels=tensorD))

    optimizer = tf.train.AdamOptimizer(learning_rate=learning_rate)
    #optimizer = tf.train.GradientDescentOptimizer(learning_rate=learning_rate)
    #optimizer = tf.train.MomentumOptimizer(learning_rate=learning_rate,momentum=momentum)
    train_op = optimizer.minimize(loss_op)

    # Initializing the variables

    init = tf.global_variables_initializer()

    with tf.Session() as sess:
        sess.run(init)
        #print Weightsi_h.eval()
        for i in range(epochs):
            _,_,output_result, hidden_reuslt = \
                sess.run([train_op, loss_op, output_output,hidden_output], feed_dict={tensorX: X, tensorD: D})

            # error (delta error) /cost /loss
            E = D - output_result
            # determine if we have reached desired accuracy
            currentError = np.sum(np.square(E)) / float(len(X))
            if (currentError < stopError):
                print "Reach to desired accuracy at epoch:", i
                break
        #print output_result
        print "Error = ", currentError