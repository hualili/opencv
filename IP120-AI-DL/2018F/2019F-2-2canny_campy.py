#######################################################
# Company           :   CTI One Corporation
# Coded by          :   MInh DUc Ong
# Date              :   09/04/2019
# Architected by    :   Dr. Harry Li, PHD
# Purpose           :   Stream video frames from webcam
#######################################################

# Include the OpenCV library
import cv2

# Create a default output window
cv2.namedWindow('frame', cv2.WINDOW_NORMAL)

# Read the image from the disk.
frame = cv2.imread('image.png')

# Canny Edge detector function
edge = cv2.Canny(frame, 100, 150)

# Write the image to the disk.
cv2.imwrite('edge_Canny.jpg', edge)

# Display the resulting frame
cv2.imshow('frame',frame)
cv2.imshow('edge', edge)

# Wait for any key to be pressed.
cv2.waitKey(0)

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()
########################## THE END ###################

