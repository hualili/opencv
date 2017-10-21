import tensorflow as tf

W = tf.Variable([0.5, 0.5], name="weight")
# Initialize the variables (i.e. assign their default value)
init = tf.global_variables_initializer()

with tf.Session() as sess:
    sess.run(init)
    print W
    print W.eval()
    result = W.eval()
    print "result:", result
    print type(result)


