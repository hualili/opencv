#conv2d example with two variables
#we use random values as input and filter (kernel)

import tensorflow as tf

input = tf.Variable(tf.random_normal([1,5,5,1]))   #NHWC
filter = tf.Variable(tf.random_normal([3,3,1,1]))  #HWCC

op = tf.nn.conv2d(input, filter, strides=[1, 1, 1, 1], padding='VALID')  #VALID = no padding.
init = tf.global_variables_initializer()
with tf.Session() as sess:
    sess.run(init)
    print "input:", input.eval()
    print "filter:", filter.eval()
    print "result:"
    result = sess.run(op)
    print(result)

