#in order see the value in variable, you have to use eval()

import tensorflow as tf
w = tf.Variable([1.0,1.0,1.0], "MyFirstVariable")

with tf.Session() as sess:
    sess.run(w.initializer)
    print w
    print w.eval()


