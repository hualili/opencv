#2018-Nov-18
#Coded by Danny Santoso
#Copyrighted by CTI-One corporation for public release
import cv2
import time
def sendToServer(ret, frame):
    time.sleep(0.5) # Emulating a delay to send to the server
    print("Data sent!!! = "+(str)(ret))
    
print(cv2.getBuildInformation())
device = "/dev/video0"  # has to be string!
# Source if there is NO GSTREAMER
cap = cv2.VideoCapture(device)
cv2.namedWindow(device, cv2.WINDOW_NORMAL)
# Set frames elapsed as 0
nFrame = 0
realFPS = 0
pastTime = time.time()
while True:
    ret, frame = cap.read()
    if (ret):
        # Slow Payload
        if nFrame==15 or nFrame==30 : # only send every 15 FPS
            sendToServer(ret, frame)
        
        # Display the resulting frame
        cv2.imshow(device, frame)
        
        ### For Frame display
        if nFrame == 30:
            # Take the current timings
            curTime = time.time()
            # calculate FPS
            realFPS = nFrame / (curTime - pastTime)
            print("FPS = "+(str)(realFPS))
            nFrame = 0
            pastTime = curTime
            
        nFrame = nFrame + 1
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()
