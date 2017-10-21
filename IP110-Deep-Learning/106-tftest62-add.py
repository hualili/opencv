import tensorflow as tf

W = tf.Variable([0.5, 0.5], name="weight")
newW = tf.add(W, 0.1)
# Initialize the variables (i.e. assign their default value)
init = tf.global_variables_initializer()

with tf.Session() as sess:
    sess.run(init)
    result = W.eval()
    print "original W:", result
    result = sess.run(newW)
    print "new W:", result

    

