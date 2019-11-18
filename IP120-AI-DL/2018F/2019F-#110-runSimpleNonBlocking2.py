#2018-Nov-18
#Coded by Danny Santoso
#Copyrighted by CTI-One corporation for public release
import cv2
import time
import multiprocessing
def sendToServer(sTSContainer):
    time.sleep(0.5) # Emulating a delay to send to the server
    print("Data sent!!! = "+(str)(sTSContainer.ret))

class STSContainer():
    def __init__(self,ret,frame):
        self.ret = ret
        self.frame = frame

# with a multithreading and a queue
def sendToServerWorker(sTSQueue):
    print("Starting sendToServerWorker!")
    while True:
        sTSContainer = sTSQueue.get()
        sendToServer(sTSContainer)

if __name__ == '__main__':
    print(cv2.getBuildInformation())
    device = "/dev/video0"  # has to be string!
    # Source if there is NO GSTREAMER
    cap = cv2.VideoCapture(device)
    cv2.namedWindow(device, cv2.WINDOW_NORMAL)
    
    sTSQueue = multiprocessing.Queue()
    sTSProcess = multiprocessing.Process(target=sendToServerWorker, args=(sTSQueue,))
    sTSProcess.start()
    
    # Set frames elapsed as 0
    nFrame = 0
    realFPS = 0
    pastTime = time.time()
    while True:
        ret, frame = cap.read()
        if (ret):
            # Slow Payload
#             sendToServer(ret, frame)

            if nFrame==15 or nFrame==30 : # only send every 15 FPS
                sTSContainer = STSContainer(ret,frame.copy())
                sTSQueue.put(sTSContainer)
                pass
            
            
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
