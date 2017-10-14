import tensorflow as tf

MyKernel = tf.constant([1,2,3,4,5,6,7,8,9], shape=[3,3])

product = tf.multiply(MyKernel, MyKernel)
dotproduct = tf.matmul(MyKernel, MyKernel)
# multiple and matmul are different.
with tf.Session() as sess:
    result = sess.run(product)
    print(result)
    result = sess.run(dotproduct)
    print(result)