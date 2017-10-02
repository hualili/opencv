import tensorflow as tf
a = tf.constant(1, name = "a")
b = tf.constant(2, name = "b")
x = tf.add(a, b, name = "adder")

with tf.Session() as sess:
    print sess.run(x)
