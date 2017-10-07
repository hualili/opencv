'''from Python list to tensor
display tensor's value by using eval() '''

import tensorflow as tf

t = [1,2,3,4,5,6,7,8,9]
print "t is", type(t)

t1 = tf.reshape(t, [3,3])

with tf.Session() as sess:
    print t1
    print t1.eval()



