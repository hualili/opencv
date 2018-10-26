#------------------------------------------------*
# Program: visualization-convnet.py;             * 
# Data   : Oct 25, 2018;                         *
# version: 0x0.1;                                * 
# status : debug;                                * 
# purpose: visualization demo of VGG16 model     * 
# code prepared : HL                             * 
#------------------------------------------------* 
# tutorial   
'''
https://github.com/fchollet/deep-learning-with-python-notebooks
''' 
import keras
keras.__version__


'''
1. VISACT Visualizing intermediate convnet ("intermediate activations") to get an 
   idea of individual convnet filters.
2. VISFLT Visualizing convnets filters to understand visual pattern or concept of each filter
   in convnet. 
3. VISHET Visualizing heatmaps of class activation in an image to understand which part of 
   an image where identified as belonging to a given class, and thus allows to 
   localize objects in images.

Note: VISACT Visualizing intermediate activations:
(1) display the feature maps that are output of convolution and pooling layers. 
    Note given a certain input the output of a layer is often called its "activation", 
    which illustrates how an input is decomposed unto the different filters learned by 
    the network. 
(2) Feature maps have 3 dimensions: width, height, and depth (channels). 
(3) Each channel encodes relatively independent features, so plotting each channel
    as a 2D image. 
'''

#----------load model--------------*
from keras.models import load_model

model = load_model('cats_and_dogs_small_2.h5')
model.summary()  # As a reminder to print out the model structure 

#----------input image-------------*
# the image below is not part the image the net was trained on
img_path = '/Users/fchollet/Downloads/cats_and_dogs_small/test/cats/cat.1700.jpg'

# We preprocess the image into a 4D tensor
from keras.preprocessing import image
import numpy as np

img = image.load_img(img_path, target_size=(150, 150))
img_tensor = image.img_to_array(img)
img_tensor = np.expand_dims(img_tensor, axis=0)
# Remember that the model was trained on inputs
# that were preprocessed in the following way:
img_tensor /= 255.

# Its shape is (1, 150, 150, 3)
print(img_tensor.shape)

#--------display (plot) image-------*
import matplotlib.pyplot as plt

plt.imshow(img_tensor[0])
plt.show()

#--------display models-------------* 
'''
use the Keras class Model is instantiated using two arguments: 
(1) an input tensor (or list of input tensors), and 
(2) an output tensor (or list of output tensors). 
The resulting class is a Keras model and it allows for models with multiple outputs, 
unlike Sequential.  
'''
from keras import models

# Extracts the outputs of the top 8 layers:
layer_outputs = [layer.output for layer in model.layers[:8]]
# Creates a model that will return these outputs, given the model input:
activation_model = models.Model(inputs=model.input, outputs=layer_outputs)

'''
When fed an image input, this model returns the values of the layer activations.
A model here has one input and 8 outputs, one output per each layer activation.
'''
# This will return a list of 5 Numpy arrays:
# one array per layer activation
activations = activation_model.predict(img_tensor)

#----------print 1st activation layer--------*
first_layer_activation = activations[0]
print(first_layer_activation.shape)

#----------visualize 3rd channel-------------*
import matplotlib.pyplot as plt

plt.matshow(first_layer_activation[0, :, :, 3], cmap='viridis')
plt.show()

#----------visualize 30th channel------------*  
'''
Note that each time the channel may vary, since the specific 
filters learned by convolution layers are not deterministic.
'''
plt.matshow(first_layer_activation[0, :, :, 30], cmap='viridis')
plt.show()

#---------visualization of all channels------* 
'''
extract and plot every channel and stack the results 
in one big image tensor, with channels stacked side by side.
'''
import keras

# These are the names of the layers, so can have them as part of our plot
layer_names = []
for layer in model.layers[:8]:
    layer_names.append(layer.name)

images_per_row = 16

# Now let's display our feature maps
for layer_name, layer_activation in zip(layer_names, activations):
    # This is the number of features in the feature map
    n_features = layer_activation.shape[-1]

    # The feature map has shape (1, size, size, n_features)
    size = layer_activation.shape[1]

    # We will tile the activation channels in this matrix
    n_cols = n_features // images_per_row
    display_grid = np.zeros((size * n_cols, images_per_row * size))

    # We'll tile each filter into this big horizontal grid
    for col in range(n_cols):
        for row in range(images_per_row):
            channel_image = layer_activation[0,
                                             :, :,
                                             col * images_per_row + row]
            # Post-process the feature to make it visually palatable
            channel_image -= channel_image.mean()
            channel_image /= channel_image.std()
            channel_image *= 64
            channel_image += 128
            channel_image = np.clip(channel_image, 0, 255).astype('uint8')
            display_grid[col * size : (col + 1) * size,
                         row * size : (row + 1) * size] = channel_image

    # Display the grid
    scale = 1. / size
    plt.figure(figsize=(scale * display_grid.shape[1],
                        scale * display_grid.shape[0]))
    plt.title(layer_name)
    plt.grid(False)
    plt.imshow(display_grid, aspect='auto', cmap='viridis')
    
plt.show()






