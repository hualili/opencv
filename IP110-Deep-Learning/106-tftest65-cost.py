'''
A linear regression learning algorithm example using TensorFlow library.

'''

import tensorflow as tf

# Parameters
learning_rate = 0.1
training_epochs = 1

trainX = [[1.0, 2.0], [1.0, 3.0], [2.0, 3.0], [2.0, 1.0], [3.0, 1.0], [3.0, 2.0]]
trainY = [1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 1.0]
t = 0.5
# Training Data

n_samples = len(trainX)

# tf Graph Input
X = tf.placeholder("float")
Y = tf.placeholder("float")
Pred = tf.placeholder("float")

# Set model weights
W = tf.Variable([0.5, 0.5], name="weight")
b = tf.Variable([0.5], name="bias")

# Construct a linear model
myScore = tf.add(tf.reduce_sum(tf.multiply(X, W)), b)
myCost = Y - Pred

# Initialize the variables (i.e. assign their default value)
init = tf.global_variables_initializer()

# Start training
with tf.Session() as sess:
    # Run the initializer
    sess.run(init)

    # Fit all training data
    for epoch in range(training_epochs):
        for (x, y) in zip(trainX, trainY):
            result = sess.run(myScore, feed_dict={X: x})
            print "my score:", result
            if (result[0] == 0):  # it is a special case, we skip it
                continue
            if result[0] < 0.0:
                myPred = [0.0]
            else: myPred = [1.0]
            result = sess.run(myCost, feed_dict={Pred:myPred, Y:y})
            print "my cost:", result


