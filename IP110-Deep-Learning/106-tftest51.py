import tensorflow as tf

matrix1 = tf.constant([1,2,3,4,5,6], shape=[2,3])
matrix2 = tf.constant([7,8,9,10,11,12], shape = [3,2])

#inner product
product = tf.matmul(matrix1, matrix2)

with tf.Session() as sess:
    result = sess.run(product)
    print(result)

