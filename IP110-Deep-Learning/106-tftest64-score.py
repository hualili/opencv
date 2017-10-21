'''
A linear regression learning algorithm example using TensorFlow library.
'''

import tensorflow as tf

# Parameters
learning_rate = 0.1
training_epochs = 5

trainX = [[1.0, 2.0], [1.0, 3.0], [2.0, 3.0], [2.0, 1.0], [3.0, 1.0], [3.0, 2.0]]
trainY = [1.0, 1.0, 1.0, 0.0, 0.0, 0.0]

t = 0.5
# Training Data

n_samples = len(trainX)

# tf Graph Input
X = tf.placeholder("float")
Y = tf.placeholder("float")

# Set model weights
W = tf.Variable([0.5, 0.5], name="weight")
b = tf.Variable([0.5], name="bias")

# Construct a linear model
myScore = tf.add(tf.reduce_sum(tf.multiply(X, W)), b)

# Initialize the variables (i.e. assign their default value)
init = tf.global_variables_initializer()

# Start training
with tf.Session() as sess:
    # Run the initializer
    sess.run(init)
    for (x, y) in zip(trainX, trainY):
    # Fit all training data
        print x
        result = sess.run(myScore,feed_dict={X: x})
        print (result)

