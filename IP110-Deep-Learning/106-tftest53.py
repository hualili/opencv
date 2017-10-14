import tensorflow as tf
input = tf.Variable(tf.random_normal([5, 2]))
split0, split1 = tf.split(input,2,1)
init = tf.global_variables_initializer()
with tf.Session() as sess:
    result = sess.run(init)
    print input.eval()
    print split0.eval()
