#---------------------------------------------------*
# program: 8-1convnets-SmallData-cats-dogs-Deploy-ch05.py;    
# CTI One Training Program, CTI One Corporation;    * 
# date   : Nov 9, 2018;     status  : tested;       * 
# purpose: resize any size input image to 28x28 for * 
#          MNIST convnet use.                       * 
#---------------------------------------------------* 

import time
import keras
keras.__version__
#import tensorflow as tf
import numpy as np

#----------load trained model--------------------*
#from keras import layers
from keras import models
import cv2
from keras.models import load_model
model = load_model('cats_and_dogs_small_1.h5')
#model.summary() #check the model

image =cv2.imread('1.jpg',cv2.IMWRITE_JPEG_QUALITY)
image = cv2.resize(image,(150,150))

image=np.reshape(image,[1,150,150,3])

time_curr=int(round(time.time()*1000))

output=model.predict_classes(image)

time_end=int(round(time.time()*1000))
time=time_end-time_curr
print("")
print(output) # prediction
print("")
print(time)
print("")



