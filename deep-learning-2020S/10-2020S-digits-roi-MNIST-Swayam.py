#----------------------------------------------------------*
# program : web_cam_roi.py                                 *
# author  : Swayam Swaroop Mishra                          *
# date    : April 9, 2020                                  *
# status: tested                                           *
#                                                          *
# purpose : real time digit recognation using web camera.  *  
#----------------------------------------------------------*

import cv2
from keras.models import load_model
from keras.preprocessing import image
import numpy as np

def find_numbers_conturs(frame):
    gray = cv2.cvtColor(roi, cv2.COLOR_BGR2GRAY)
    im_blur = cv2.GaussianBlur(gray, (5, 5), 3.5)   ### Use Sigma big value (3.5), 60%
    im_th = cv2.threshold(im_blur, 90, 255, cv2.THRESH_BINARY_INV)[1]
    edges = cv2.Canny(im_th,100,200)
    ctrs, hier = cv2.findContours(edges.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    rects = [cv2.boundingRect(ctr) for ctr in ctrs]
    return rects, im_th

model = load_model('model_under_test.h5')

cap = cv2.VideoCapture(0)
cv2.namedWindow("frame", cv2.WINDOW_NORMAL)

while True:
    ret, frame = cap.read()
    height , width, layers = frame.shape
    height75 = int(height * 0.75)
    width75 = int(width * 0.75)
    dim = (width75, height75)
    frame75 = cv2.resize(frame, dim)

    upper_left = (int(width75 / 4 * 0.5) , int(height75 / 4 * 0.5))
    bottom_right = (int(width75 * 3 / 4 * 0.5) , int(height75 * 3 / 4 * 0.5))

    rect_img = cv2.rectangle(frame75, upper_left, bottom_right, (77, 255, 77), 2)
    roi = rect_img[upper_left[1] : bottom_right[1], upper_left[0] : bottom_right[0]]
    # Our operations on the frame come here
    rects, im_th = find_numbers_conturs(roi)

    for rect in rects:
        # Draw the rectangles
        cv2.rectangle(roi, (rect[0], rect[1]), (rect[0] + rect[2], rect[1] + rect[3]), (100, 0, 0), 3)
        leng = int(rect[3] * 1.6)
        pt1 = int(rect[1] + rect[3] // 2 - leng // 2)
        pt2 = int(rect[0] + rect[2] // 2 - leng // 2)
        im_th = im_th[pt1:pt1+leng, pt2:pt2+leng]
        try:
            digit_roi = cv2.resize(im_th, (28,28),  interpolation=cv2.INTER_AREA)
            digit_roi = cv2.dilate(digit_roi, (3, 3))
            test_image = np.reshape(digit_roi, [1, 28, 28, 1])
            result_arr = model.predict(test_image)
            result = model.predict_classes(test_image)
            cv2.putText(frame75, str(int(result)), (rect[0]+50, rect[1]+50),cv2.FONT_HERSHEY_DUPLEX, 2, (0, 255, 255), 3)
        except:
            pass

    cv2.imshow("frame", frame75)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
