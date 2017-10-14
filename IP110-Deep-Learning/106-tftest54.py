import tensorflow as tf
import math

def LoG2d(x, y, sigma):
    xyp2 = x ** 2 + y ** 2
    LoG = ((xyp2 - 2 * sigma**2) /(math.sqrt(2 * math.pi) * math.pow(sigma, 5))) * math.pow(math.e, -xyp2 / (2 * sigma**2))
    return LoG

#since it is symetric kernel, we can reduce caculation
def KernelLoG2(sigma, size, kernel):
    assert ((size % 2) != 0)
    for i in range(size/2 + 1):
        for j in range(i + 1):
            kernel[i + size/2 ][j + size/2] = LoG2d(i,j,sigma)

            if (i == 0):  # seed position.
                continue

            if (j != 0):  # need to change sign of j
                kernel[-i + size / 2][-j + size / 2] = kernel[i + size / 2][j + size / 2]
                kernel[i + size / 2][-j + size / 2] = kernel[i + size/2 ][j + size/2]

            kernel[-i + size / 2][j + size / 2] = kernel[i + size / 2][j + size / 2]

            if (i != j):  # need to exchange the place
                kernel[j + size / 2][i + size / 2] = kernel[i + size / 2][j + size / 2]
                kernel[j + size / 2][-i + size / 2] = kernel[i + size / 2][j + size / 2]

                if (j != 0):
                    kernel[-j + size / 2][i + size / 2] = kernel[i + size / 2][j + size / 2]
                    kernel[-j + size / 2][-i + size / 2] = kernel[i + size / 2][j + size / 2]


KernelSize = 3
MyKernel = [[0 for x in range(KernelSize)] for y in range(KernelSize)]
Sigma = 1.8
# create LoG Kerenl
KernelLoG2(Sigma, KernelSize, MyKernel)

print MyKernel
MyKernel = tf.cast(MyKernel, tf.float32)


# input image
InputImage = [[0, 100, 100], [0, 100, 100], [0, 100, 100]]
MyImage = tf.cast(InputImage, tf.float32)

#reshape tensors to meet conv2d inputs
MyTFKernel = tf.reshape(MyKernel,[3,3,1,1], name = "MyTFKernel") #HWCC
MyTFImage = tf.reshape(MyImage,[1,3,3,1], name = "MyTFImage")   #NHWC

#declare Variable for kernel, placeholder for input image as we discussed
MyKernel = tf.Variable(MyTFKernel, name='MyKernel')
MyImageInput = tf.placeholder(tf.float32, [1,3,3,1], "MyImageInput")

#operations - graph
init = tf.global_variables_initializer()
op = tf.nn.conv2d(MyImageInput, MyKernel, strides=[1, 1, 1, 1], padding='SAME')  #SAME

#execution session
with tf.Session() as sess:
    sess.run(init)
    result = sess.run(op, feed_dict={MyImageInput:MyTFImage.eval()})
    print op
    print result
    output = tf.reshape(result,[3,3])
    print output.eval()


