#######################################################
# Codeded by: Harry Li　　                              #
# Copyright : CTIOne Corporation                      #
# Date      : July 20, 2018                           #
# Status    : tested                                  #
# Purpose   : Generating test image data sets         # 
#######################################################

import sys, os
import cv2
import glob

for file in glob.glob("*.jpg"):
    print(file)
    img = cv2.imread(file)
    cv2.imshow('8 img',img) 

    if img is not None:
            print("Processing : " + file)

            M = cv2.getRotationMatrix2D((img.shape[1] / 2, img.shape[0] / 2), 10, 1)   
            rotate1 = cv2.warpAffine(img, M, (img.shape[1], img.shape[0])) 

            M = cv2.getRotationMatrix2D((img.shape[1] / 2, img.shape[0] / 2), -10, 1) # counterwise 
            rotate2 = cv2.warpAffine(img, M, (img.shape[1], img.shape[0])) 

            blur1 = cv2.GaussianBlur(img, (25, 25), 23) # 5by5 kernel, sigma 3

            rotate1_blur1 = cv2.GaussianBlur(rotate1, (25, 25), 23)
            rotate2_blur1 = cv2.GaussianBlur(rotate2, (25, 25), 23)

            # To do: add motion blue

            cv2.imwrite(file[0:-4] + "_rotate1.jpg", rotate1)
            cv2.imwrite(file[0:-4] + "_rotate2.jpg", rotate2)
            cv2.imwrite(file[0:-4] + "_blur1.jpg", blur1) 
            cv2.imwrite(file[0:-4] + "_rotate1_blur1.jpg", rotate1_blur1) 
            cv2.imwrite(file[0:-4] + "_rotate2_blur1.jpg", rotate2_blur1) 
 

