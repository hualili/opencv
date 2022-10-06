'''
 Sample code; 
 Codeded by: HL; 
''' 
from keras.models import load_model
import cv2
import numpy as np
from PIL import Image #PIL is the Python Imaging Library 

model = load_model('mnist.h5')
model.compile(optimizer='rmsprop',
                loss='categorical_crossentropy',
                metrics=['accuracy'])

img = Image.open('1.jpg').convert('L') #L: convert to gray scale
img = np.resize(img, (28,28,1))
im2arr = np.array(img)
im2arr = im2arr.reshape(1,28*28)
y_pred = model.predict_classes(im2arr)
print(y_pred)

