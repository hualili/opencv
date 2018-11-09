#-------------------------------------------------------------------*
# program: 7-5augment_data.py;         coded by: CTI One AI group;  *
# date   : Aug 2017;                   status  : debug;             * 
# purpose: demo of image data augmentation;                         *
#-------------------------------------------------------------------* 
import sys, os
sys.path.append('/usr/local/lib/python2.7/dist-packages')
import cv2

data_dir = "CTIOne_harry_Training_Data"
directories = [d for d in os.listdir(data_dir)
                   if os.path.isdir(os.path.join(data_dir, d))]

for d in directories:
    images = []
    label_dir = os.path.join(data_dir, d)
    file_names = [os.path.join(label_dir, f)
                  for f in os.listdir(label_dir)
                  if f.endswith(".ppm") or f.endswith(".JPG")
                  or f.endswith(".png")]

    # Augment the dataset with rotation and blurring
    for f in file_names:
        img = cv2.imread(f)
        if img is not None:
            M = cv2.getRotationMatrix2D((img.shape[1] / 2, img.shape[0] / 2), 10, 1)
            rotate1 = cv2.warpAffine(img, M, (img.shape[1], img.shape[0]))
            M = cv2.getRotationMatrix2D((img.shape[1] / 2, img.shape[0] / 2), -10, 1)
            rotate2 = cv2.warpAffine(img, M, (img.shape[1], img.shape[0]))

            blur1 = cv2.GaussianBlur(img, (5, 5), 3)
            blur2 = cv2.GaussianBlur(img, (7, 7), 5)
            blur3 = cv2.GaussianBlur(img, (9, 9), 7)

            rotate1_blur1 = cv2.GaussianBlur(rotate1, (5, 5), 3)
            rotate1_blur2 = cv2.GaussianBlur(rotate1, (7, 7), 5)
            rotate1_blur3 = cv2.GaussianBlur(rotate1, (9, 9), 7)

            rotate2_blur1 = cv2.GaussianBlur(rotate2, (5, 5), 3)
            rotate2_blur2 = cv2.GaussianBlur(rotate2, (7, 7), 5)
            rotate2_blur3 = cv2.GaussianBlur(rotate2, (9, 9), 7)

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
