
import tensorflow as tf
with tf.Session() as sess:
    hello = tf.constant('Hello World')
    print sess.run(hello)