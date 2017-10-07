#in order to use conv2d, we have to reshape our python list 

import tensorflow as tf

MyFirstKernel = [[1.0, 1.0, 1.0], [0., 0., 0.], [-1.0, -1.0, -1.0]]
MyTFKernel = tf.reshape(MyFirstKernel,[3,3,1,1], name = "MyTFKernel") #HWCC

with tf.Session() as sess:
    print MyTFKernel
    print MyTFKernel.eval()
