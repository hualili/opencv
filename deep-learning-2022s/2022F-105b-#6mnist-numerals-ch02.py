#----------------------------------------------------------*
# program : 2mnist.py;                date: Oct 18, 2018   *
# version : x0.10;                    status: tested;      * 
# ref: https://github.com/fchollet/deep-learning-with-python-notebooks/blob/96d58b5727fcf76106f929f5ce24c40fc9b46d75/2.1-a-first-look-at-a-neural-network.ipynb
#                                                          *
# purpose : demo of mnist net for hand written numerals    * 
#           recognition.                                   *  
#----------------------------------------------------------*
import keras
keras.__version__

from keras.datasets import mnist

#---------------------load data-----------------*
# MNIST dataset pre-loaded in Keras, in the form of 4 Numpy arrays:
(train_images, train_labels), (test_images, test_labels) = mnist.load_data()

train_images.shape
test_images.shape

train_labels
test_labels

len(train_labels)
len(test_labels)

#------------build neural network-----------------*
from keras import models
from keras import layers

network = models.Sequential()
network.add(layers.Dense(512, activation='relu', input_shape=(28 * 28,)))
network.add(layers.Dense(10, activation='softmax'))

network.summary()

#---------loss function, optimizer and metrics----*
network.compile(optimizer='rmsprop',
                loss='categorical_crossentropy',
                metrics=['accuracy'])


#----------reshape images to float----------------* 
'''
Preprocessing by reshaping. Previously, training images 
were stored in an array of shape (60000, 28, 28) of type uint8 
with values in the [0, 255]. Now convert it into a float32 
array of shape (60000, 28 * 28) with values between 0 and 1.
'''
train_images = train_images.reshape((60000, 28 * 28))
train_images = train_images.astype('float32') / 255

test_images = test_images.reshape((10000, 28 * 28))
test_images = test_images.astype('float32') / 255

#-----------------encode labels-------------------*
from keras.utils import to_categorical

train_labels = to_categorical(train_labels)
test_labels = to_categorical(test_labels)

#------------------training-----------------------*
network.fit(train_images, train_labels, epochs=5, batch_size=128)

network.save('mnist.h5')

#---------------training result-------------------*
test_loss, test_acc = network.evaluate(test_images, test_labels)
print('test_acc:', test_acc)
