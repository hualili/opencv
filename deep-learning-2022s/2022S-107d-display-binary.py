# OpenCV Demo for display image and binarization
# Coded by: Harry Li 
# Status: Release 
# Date: Feb. 21, 2022 

def print_hi(name):
    # Use a breakpoint in the code line below to debug your script.
    print(f'OpenCV Example, {name}')  # Press Ctrl+F8 to toggle the breakpoint.

# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    print_hi('Harry 2022-2-17')
# import the necessary packages
    import numpy as np
    #import argparse
    import cv2

    img = input('Enter image file name:')

    image = cv2.imread(img, cv2.IMREAD_COLOR)

    if image is None:
        print('Error opening image!')
        print('Usage: pdisplay.py image_name\n')

    image = cv2.resize(image, (256, 256))

    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    edges = cv2.Canny(gray,100,200)
    ret, thresh1 = cv2.threshold(gray, 127, 255, cv2.THRESH_BINARY)

    cv2.imshow('original',image)
    cv2.imshow('gray scale',gray)
    cv2.imshow('Canny edges',edges)
    cv2.imshow('Binary image', thresh1)

    cv2.imshow("Harry's Images", np.hstack([image, image]))
    cv2.waitKey(0)

