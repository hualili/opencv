#----------------------------------------------------------*
# program : 7-4convnets-NumeralDet-DeployTrained.py;       * 
# date    : Nov 6, 2018                                    *
# version : x0.10;                    status: tested;      *  
# www.ctione.org Intern Training Program                   * 
#                                                          *
# purpose : demo of saving trained mnist net               *  
#----------------------------------------------------------*
# homework for TF Keras load model for detection 
 
from keras.models import load_model
from keras.preprocessing import image
import cv2
import numpy as np


gray = cv2.imread('test.png',cv2.IMREAD_GRAYSCALE)
gray = cv2.resize(gray, (28,28))
cv2.imshow('image',gray)
cv2.imwrite('resized_LCTest.jpg',gray, [int(cv2.IMWRITE_JPEG_QUALITY),90])

# load model and predict the image 
model = load_model('Numeral_detector.h5')
test_image= cv2.imread('resized_LCTest.jpg', cv2.IMREAD_GRAYSCALE) 
test_image = np.reshape(test_image, [1, 28, 28, 1])
result_arr = model.predict(test_image)
result = model.predict_classes(test_image)
print(result_arr,' ', result)
