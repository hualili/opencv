#######################################################
# Company           :   CTI One Corporation
# Coded by          :   Prashanth Rajasekar, AI & DLE
# Date              :   07/18/2019
# Architected by    :   Dr. Harry Li, PHD
# Purpose           :   Finding contours on digits
#######################################################

# import the necessary packages
import imutils
from imutils.perspective import four_point_transform
from imutils import contours
import cv2

# Load the test image.
image = cv2.imread("2019.jpg")

# Show the input image.
cv2.imshow("Input", image)

# Make a copy of the image.
thresh = image.copy()

# Convert the color Image to Gray Scale.
gray = cv2.cvtColor(thresh, cv2.COLOR_BGR2GRAY)

# Set the Threshold to its maximum level.
thresh = cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY_INV | cv2.THRESH_OTSU)[1]

# find contours in the thresholded image.
cnts = cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

# Grab the number of Contours.
cnts = imutils.grab_contours(cnts)

# Initialize the digit contours lists.
digit_Coordinates = []

# Loop over the grabbed Contours.
for c in cnts:
	# Get the coordinates.
	(x, y, w, h) = cv2.boundingRect(c)

	# Append the coordinates in the digit contour list in line 29.
	digit_Coordinates.append(c)

# Sort the contours from left-to-right.
digit_Coordinates = contours.sort_contours(digit_Coordinates, method="left-to-right")[0]


# Loop over each index in the digit contour list.
for c in digit_Coordinates:
	# extract the ROI coordinates from each index.
	(x, y, w, h) = cv2.boundingRect(c)
	# Draw the ROI.
	cv2.rectangle(image, (x, y), (x + w, y + h), (0, 255, 0), 2)
	
# Write the output
cv2.imwrite("output.jpg", image)

# Display the digits
cv2.imshow("Output", image)
cv2.waitKey(0)
