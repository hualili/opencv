#######################################################
# Company           :   CTI One Corporation
# Coded by          :   Prashanth Rajasekar, AI & DLE
# Date              :   07/19/2019
# Architected by    :   Dr. Harry Li, PHD
# Purpose           :   Stream video frames from webcam
#######################################################

# Include the library
import cv2

# Provide the streaming adress.
cap = cv2.VideoCapture("2-shopfloor.mov")

# Create a default output window
cv2.namedWindow('frame', cv2.WINDOW_NORMAL)

# Create a default output window for edged output.
cv2.namedWindow('edge', cv2.WINDOW_NORMAL)

# Pick one frame
ret, frame = cap.read()

# Get the
heigth, width, _ = frame.shape
fourcc = cv2.VideoWriter_fourcc(*'XVID')
video_writer_object = cv2.VideoWriter("edged_output.mov", fourcc, 20.0, (width, heigth))

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
    
    video_writer_object.write(edge)
    # If "q" pressed, the program will end
    if cv2.waitKey(1)== ord('q'):
        break

# Release the active writing function
video_writer_object.release()

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()
########################## THE END ###################

