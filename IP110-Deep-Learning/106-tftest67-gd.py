'''
A linear regression learning algorithm example using TensorFlow library.

'''

from __future__ import print_function

import tensorflow as tf
import numpy
import matplotlib.pyplot as plt
# Parameters
learning_rate = 0.1
training_epochs = 5

w = [0.5, 0.5]
trainX = [[1, 2], [1, 3], [2, 3], [2, 1], [3, 1], [3, 2]]
trainY = [1, 1, 1, 0, 0, 0]
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
score = tf.add(tf.reduce_sum(tf.multiply(X, W)), b)
pred = score
# Mean squared error
cost = tf.reduce_sum(tf.pow(pred-Y, 2))/(2*n_samples)
# Gradient descent
#  Note, minimize() knows to modify W and b because Variable objects are trainable=True by default
optimizer = tf.train.GradientDescentOptimizer(learning_rate).minimize(cost)

# Initialize the variables (i.e. assign their default value)
init = tf.global_variables_initializer()

# Start training
with tf.Session() as sess:
    # Run the initializer
    sess.run(init)

    # Fit all training data
    for epoch in range(training_epochs):
        for (x, y) in zip(trainX, trainY):
            sess.run(optimizer, feed_dict={X: x, Y: y})

    print("Optimization Finished!")
    training_cost = sess.run(cost, feed_dict={X: trainX, Y: trainY})
    print("Training cost=", training_cost, "W=", sess.run(W), "b=", sess.run(b), '\n')

