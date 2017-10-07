import tensorflow as tf

MyFirstKernel = [[1, 1, 1], [0, 0, 0], [-1, -1, -1]]
MyKernel = tf.cast(MyFirstKernel, tf.float32) 

MyTestImage = [[100,101,100,100,100], [100,100,100,100,100],[100,100,100,100,100],[100,100,100,100,100],[100,100,100,100,100]]
MyImage = tf.cast(MyTestImage, tf.float32)

#reshape tensors to meet conv2d inputs
MyTFKernel = tf.reshape(MyKernel,[3,3,1,1], name = "MyTFKernel") #HWCC
MyTFImage = tf.reshape(MyImage,[1,5,5,1], name = "MyTFImage")   #NHWC

#declare Variable for kernel, placeholder for input image as we discussed
MyKernel = tf.Variable(MyTFKernel, name='MyKernel')
MyImageInput = tf.placeholder(tf.float32, [1,5,5,1], "MyImageInput")  

#operations - graph
init = tf.global_variables_initializer()
op = tf.nn.conv2d(MyImageInput, MyKernel, strides=[1, 1, 1, 1], padding='VALID')  #VALID = no padding.

#execution session
with tf.Session() as sess:
    sess.run(init)
    result = sess.run(op, feed_dict={MyImageInput:MyTFImage.eval()})
    print op
    print result
    output = tf.reshape(result,[3,3])
    print output.eval()


