#placeholder example

import tensorflow as tf
MyInput = [1,2,3,4]
x = tf.placeholder(tf.float32, len(MyInput))
y = x * 2

with tf.Session() as sess:
    result = sess.run(y, feed_dict={x: MyInput})
    print result


