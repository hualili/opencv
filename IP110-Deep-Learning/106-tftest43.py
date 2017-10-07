import tensorflow as tf
#a python list
MyFirstKernel = [[1, 1, 1], [0, 0, 0], [-1, -1, -1]]

print MyFirstKernel

#define a 3x3 Kernel
MyKernel = tf.Variable(MyFirstKernel,
                       expected_shape=(3,3),
                       dtype=tf.float32,
                       name='MyKernel')

#initialization of all variables
init = tf.global_variables_initializer()

with tf.Session() as sess:
    sess.run(init)
    print MyKernel.eval()


