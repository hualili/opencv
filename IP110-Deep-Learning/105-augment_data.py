#######################################################
# Project   : Traffic_Sign_Detection_Recognition      #
# Author    : Kris Huang                              #
# Copyright : CTIOne Corporation                      #
# Date      : August 10, 2017                         #
# Version   : x0.1                                    #
# Status    : Debug                                   #
# Note      : For augmenting the image (preprocessing #
#             image dataset), 1 image becomes 12      #
#             images.                                 #
#######################################################
import sys, os
import cv2

data_dir = "Training"  #path for the folder  

#list all the directories which hold all different images in each directory

directories = [d for d in os.listdir(data_dir)
              if os.path.isdir(os.path.join(data_dir, d))]

for d in directories:
    images = []
    label_dir = os.path.join(data_dir, d)
    file_names = [os.path.join(label_dir, f)
                  for f in os.listdir(label_dir)
                  if f.endswith(".ppm") or f.endswith(".JPG")
                  or f.endswith(".png")]

    # Augment the image dataset with rotation and blurring
    for f in file_names:
        img = cv2.imread(f)
        if img is not None:
            print("Processing" + f)
            M = cv2.getRotationMatrix2D((img.shape[1] / 2, img.shape[0] / 2),
                                        10, 1)  # rotation matrix by 10 degree
            rotate1 = cv2.warpAffine(img, M, (img.shape[1], img.shape[0]))
                                                # rotate image and assign it back
            M = cv2.getRotationMatrix2D((img.shape[1] / 2, img.shape[0] / 2),
                                        -10, 1) # rotation matrix counterwise 
            rotate2 = cv2.warpAffine(img, M, (img.shape[1], img.shape[0]))
                                                # rotate image and assign it back

            blur1 = cv2.GaussianBlur(img, (5, 5), 3) # 5 by 5 kernel, sigma 3
            blur2 = cv2.GaussianBlur(img, (7, 7), 5) 
            blur3 = cv2.GaussianBlur(img, (9, 9), 7)

            rotate1_blur1 = cv2.GaussianBlur(rotate1, (5, 5), 3)
            rotate1_blur2 = cv2.GaussianBlur(rotate1, (7, 7), 5)
            rotate1_blur3 = cv2.GaussianBlur(rotate1, (9, 9), 7)

            rotate2_blur1 = cv2.GaussianBlur(rotate2, (5, 5), 3)
            rotate2_blur2 = cv2.GaussianBlur(rotate2, (7, 7), 5)
            rotate2_blur3 = cv2.GaussianBlur(rotate2, (9, 9), 7)
             
            # Aug 10, 2017 
            # add motion blur

            cv2.imwrite(f[0:-4] + "_rotate1.jpg", rotate1)
            cv2.imwrite(f[0:-4] + "_rotate2.jpg", rotate2)
            cv2.imwrite(f[0:-4] + "_blur1.jpg", blur1)
            cv2.imwrite(f[0:-4] + "_blur2.jpg", blur2)
            cv2.imwrite(f[0:-4] + "_blur3.jpg", blur3)
            cv2.imwrite(f[0:-4] + "_rotate1_blur1.jpg", rotate1_blur1)
            cv2.imwrite(f[0:-4] + "_rotate1_blur2.jpg", rotate1_blur2)
            cv2.imwrite(f[0:-4] + "_rotate1_blur3.jpg", rotate1_blur3)
            cv2.imwrite(f[0:-4] + "_rotate2_blur1.jpg", rotate2_blur1)
            cv2.imwrite(f[0:-4] + "_rotate2_blur2.jpg", rotate2_blur2)
            cv2.imwrite(f[0:-4] + "_rotate2_blur3.jpg", rotate2_blur3)
# end of the code
