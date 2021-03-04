from keras.models import load_model
import cv2
import numpy as np
from PIL import Image

model = load_model('mnist.h5')
model.compile(optimizer='rmsprop',
                loss='categorical_crossentropy',
                metrics=['accuracy'])

img = Image.open('1.jpg').convert('L')
img = np.resize(img, (28,28,1))
im2arr = np.array(img)
im2arr = im2arr.reshape(1,28*28)
y_pred = model.predict_classes(im2arr)
print(y_pred)

