#######################################################
# Company           :   CTI One Corporation
# Coded by          :   Minh Duc Ong, AI & DLE
# Date              :   08/04/2019
# Architected by    :   Dr. Harry Li, PHD
# Purpose           :   Stream video frames from webcam
#######################################################

# Include the library
import cv2

# Provide the streaming adress."0" for webcam.
cap = cv2.VideoCapture(0)

# Create a default output window
cv2.namedWindow('frame', cv2.WINDOW_NORMAL)

# Create a default output window for edged output.
cv2.namedWindow('edge', cv2.WINDOW_NORMAL)

# Start the loop to receive the frame one by one
while(True):
    # Capture frame-by-frame
    ret, frame = cap.read()
    
    # Perform Canny edge detection.
    edge = cv2.Canny(frame, 50, 100)
    
    # Display the resulting frame
    cv2.imshow('frame',frame)
    
    # Display the edged data
    cv2.imshow('edge', edge)
    
    # If "q" pressed, the program will end
    if cv2.waitKey(1)== ord('q'):
        break

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()
########################## THE END ###################

