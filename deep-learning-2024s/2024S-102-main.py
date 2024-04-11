# Find bodyshape ROI image based on irregular ROI finding technique, e.g., img_ROI_{bodyshape_i}
# Copyright: CTI One Corporation
# Coded by: HL

def print_hi(name):
    # Use a breakpoint in the code line below to debug your script.
    print(f'Hi, {name}')  # Press Ctrl+F8 to toggle the breakpoint.

# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    print_hi('roi_bodyshape')

# import the necessary packages
    import numpy as np
    import cv2
    noiseSize = 10

    img = input('Enter image file name:')
    image = cv2.imread(img, cv2.IMREAD_COLOR)

    scale_percent = 50  # percent of original size
    width = int(image.shape[1] * scale_percent / 100)
    height = int(image.shape[0] * scale_percent / 100)
    dim = (width, height)

    # resize image
    image_resized = cv2.resize(image, dim, interpolation=cv2.INTER_AREA)

    cv2.imshow('original', image_resized)
    img_gray = cv2.cvtColor(image_resized, cv2.COLOR_BGR2GRAY)
    cv2.imshow('gray', img_gray)
    //print('step 1: binarization')

    (img_B, img_G, img_R) = cv2.split(image_resized)
    cv2.imshow('R plane', img_R)
    threshold = 200
    threshold_R = 120
    binarization_high = 240
    ret, img_R_binarized = cv2.threshold(img_R, threshold_R, binarization_high, cv2.THRESH_BINARY)
    cv2.imshow('Binarization R', img_R_binarized)

    #print('step 2: Dilation-Erosion')
    kernel_erode = np.ones((7, 7), np.uint8)   # 7x7
    kernel_dilate = np.ones((7, 7), np.uint8)  # 7x7
    img_erode = cv2.erode(img_R_binarized, kernel_erode, iterations=3) # iteration = 3
    cv2.imshow('erode', img_erode)
    img_erode_dilate = cv2.dilate(img_erode, kernel_dilate, iterations=3)
    cv2.imshow('erode-dilate', img_erode_dilate)

    print('step 3: contours finding and filtering')
    noiseSize_area = 3000.0
    aspect_threshold_l = 0.5
    aspect_threshold_h = 1.0
    image_black = np.zeros((height, width, 3), dtype="uint8")
    image_gray_from_image_R = np.zeros((height, width, 1), dtype="uint8")
    #image_gray_from_image_R = img_erode_dilate
    #cv2.imshow('red plane to gray', image_gray_from_image_R)
    image_copy1 = image_resized.copy() # all contours
    image_copy2 = image_resized.copy() # bounding boxes
    image_gray_from_image_R_copy = img_R_binarized.copy()
    contours1, hierarchy = cv2.findContours(img_erode_dilate, cv2.RETR_CCOMP,
                                           cv2.CHAIN_APPROX_SIMPLE)  # cv2.CCOMP for 2 levels
    cv2.drawContours(image_copy1, contours1, -1, (0, 255, 0), 3)
    cv2.imshow('all contours', image_copy1)

    img_black = np.zeros((height, width, 3), dtype="uint8")
    for contour in contours1:  # filtering based the contour features
        x, y, w, h = cv2.boundingRect(contour)
        cv2.rectangle(image_resized, (x, y), (x + w, y + h), (0, 255, 0), 2)  # Draw the rectangle
        aspect_ratio_contour = w / h
        area = cv2.contourArea(contour)
        #print(contour)
        if area > noiseSize_area and aspect_threshold_l < aspect_ratio_contour :
           #print(cv2.contourArea(contour))
           cv2.imshow('bounding boxes', image_resized)
    image_black = cv2.drawContours(image_black, contours1, -1, (0,255,255), thickness=-1)
    cv2.imshow('Filled after filtered contours', image_black)
    //print('step 4: Create a mask')

    //print('step 5: roi from the mask')

    # now perform mask operation
    img_roi_snipped = np.zeros((height,width,3), dtype="uint8")

    cv2.bitwise_and(image_resized, image_black, img_roi_snipped)
    cv2.imshow('CTI roi', img_roi_snipped)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    # END