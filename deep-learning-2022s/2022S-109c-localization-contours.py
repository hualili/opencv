# This is a sample Python script.
# Source: https://docs.opencv.org/4.x/d4/d73/tutorial_py_contours_begin.html

def contour_example(name):
    # Use a breakpoint in the code line below to debug your script.
    print(f'Harry, {name}')  # Press Ctrl+F8 to toggle the breakpoint.

def get_distance(x,y):
    return math.sqrt(x*x+y*y)

# Press the green button in the gutter to run the script.
if __name__ == '__main__':

    contour_example('Contour Example')
    import cv2
    import math

    #img = cv2.imread('test.jpg')
    image = input('Enter image file name:')

    img = cv2.imread(image, cv2.IMREAD_COLOR)
    img = cv2.resize(img, (256, 256))
    cv2.imshow('original image', img)

    imgray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    cv2.imshow('gray scale image', imgray)

    thresh = cv2.Canny(imgray, 100, 200)
    cv2.imshow('Canny', thresh)

    contours, hierarchy = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    # Draw contour
    thresh1 = cv2.cvtColor(thresh, cv2.COLOR_GRAY2BGR)
    cv2.drawContours(thresh1, contours, -1, (0, 255, 0), 5) # all contours
    cv2.imshow('All contours', thresh1)
    #Bounding box

    for i in range(len(contours)):
        [x, y, w, h] = cv2.boundingRect(contours[i])
        print("i:",i)
        cv2.rectangle(img, (x, y), (x + w, y + h), (0, 255, 0), 2)
    cv2.imshow('sorted', img)

print(img.shape)

cropped2 = img[10:20, 10:30]
cv2.imshow('cropped2:',cropped2)
cv2.waitKey(0)
cv2.destroyAllWindows()