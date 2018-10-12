#-------------------------------------------------------------*
# program: model.py;                                          * 
# purpose: demo tf keras API.                                 * 
# status : tested;                     Date: Oct. 10, 2018;   * 
# https://medium.com/tensorflow/training-and-serving-ml-models-with-tf-keras-fd975cc0fa27
#-------------------------------------------------------------* 

import tensorflow as tf
IM_SIZE = 128

image_input = tf.keras.Input(shape=(IM_SIZE, IM_SIZE, 3), name='input_layer')

# Some convolutional layers
conv_1 = tf.keras.layers.Conv2D(32,
                                kernel_size=(3, 3),
                                padding='same',
                                activation='relu')(image_input)
conv_1 = tf.keras.layers.MaxPooling2D(padding='same')(conv_1)
conv_2 = tf.keras.layers.Conv2D(32,
                                kernel_size=(3, 3),
                                padding='same',
                                activation='relu')(conv_1)
conv_2 = tf.keras.layers.MaxPooling2D(padding='same')(conv_2)

# Flatten the output of the convolutional layers
conv_flat = tf.keras.layers.Flatten()(conv_2)

# Some dense layers with two separate outputs
fc_1 = tf.keras.layers.Dense(128,
                             activation='relu')(conv_flat)
fc_1 = tf.keras.layers.Dropout(0.2)(fc_1)
fc_2 = tf.keras.layers.Dense(128,
                             activation='relu')(fc_1)
fc_2 = tf.keras.layers.Dropout(0.2)(fc_2)

# Output layers: separate outputs for the weather and the ground labels
weather_output = tf.keras.layers.Dense(4,
                                       activation='softmax',
                                       name='weather')(fc_2)
ground_output = tf.keras.layers.Dense(13,
                                      activation='sigmoid',
                                      name='ground')(fc_2)

# Wrap in a Model
model = tf.keras.Model(inputs=image_input, outputs=[weather_output, ground_output])

#-----------compile-----------------#
model.compile(optimizer='adam',
              loss={'weather': 'categorical_crossentropy',
                    'ground': 'binary_crossentropy'})

#-----------training: make safe GPU multi-processing--------------#
import ast
import numpy as np
import math
import os
import random
import pandas as pd 
 
from tensorflow.keras.preprocessing.image import img_to_array as img_to_array
from tensorflow.keras.preprocessing.image import load_img as load_img

def load_image(image_path, size):
    # data augmentation logic such as random rotations can be added here
    return img_to_array(load_img(image_path, target_size=(size, size))) / 255.

class KagglePlanetSequence(tf.keras.utils.Sequence):
    """
    Custom Sequence object to train a model on out-of-memory datasets. 
    """
    
    def __init__(self, df_path, data_path, im_size, batch_size, mode='train'):
        """
        df_path: path to a .csv file that contains columns with image names and labels
        data_path: path that contains the training images
        im_size: image size
        mode: when in training mode, data will be shuffled between epochs
        """
        self.df = pd.read_csv(df_path)
        self.im_size = im_size
        self.batch_size = batch_size
        self.mode = mode

        # Take labels and a list of image locations in memory
        self.wlabels = self.df['weather_labels'].apply(lambda x: ast.literal_eval(x)).tolist()
        self.glabels = self.df['ground_labels'].apply(lambda x: ast.literal_eval(x)).tolist()
        self.image_list = self.df['image_name'].apply(lambda x: os.path.join(data_path, x + '.jpg')).tolist()

    def __len__(self):
        return int(math.ceil(len(self.df) / float(self.batch_size)))

    def on_epoch_end(self):
        # Shuffles indexes after each epoch
        self.indexes = range(len(self.image_list))
        if self.mode == 'train':
            self.indexes = random.sample(self.indexes, k=len(self.indexes))

    def get_batch_labels(self, idx): 
        # Fetch a batch of labels
        return [self.wlabels[idx * self.batch_size: (idx + 1) * self.batch_size],
                self.glabels[idx * self.batch_size: (idx + 1) * self.batch_size]]

    def get_batch_features(self, idx):
        # Fetch a batch of images
        batch_images = self.image_list[idx * self.batch_size: (1 + idx) * self.batch_size]
        return np.array([load_image(im, self.im_size) for im in batch_images])

    def __getitem__(self, idx):
        batch_x = self.get_batch_features(idx)
        batch_y = self.get_batch_labels(idx)
        return batch_x, batch_y

#--------------sequence init---------------------------#
seq = KagglePlanetSequence('./KagglePlanetMCML.csv',
                       './data/train-jpg/',
                       im_size=IM_SIZE,
                       batch_size=32)

#--------------train for a signal EPOCH----------------#
callbacks = [
    tf.keras.callbacks.ModelCheckpoint('./model.h5', verbose=1)
]

model.fit_generator(generator=seq,
                    verbose=1, 
                    epochs=1,
                    use_multiprocessing=True,
                    workers=4,
                    callbacks=callbacks)



