import tensorflow as tf
a = tf.constant([[2,2],[3,3]], name="a")
b = tf.constant([[0,1], [2,3]], name="b")
x = tf.add(a, b, name = "adder")
y = tf.matmul(a, b, name = "multipler")

with tf.Session() as sess:
    x, y = sess.run([x, y])
    print x
    print y

