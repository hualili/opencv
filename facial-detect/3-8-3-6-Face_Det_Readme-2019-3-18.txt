March 18, 2019
Minh 
1. To run the program with tensorflow-gpu:
   Step 1: navigate to the directory:cd /home/ubuntu/Documents/multi_cam_test/Facenet_detection
   Step 2: run this comamnd: python3 63real_time_face_recognize.py

This command will run the program with IP camera: 
192.168.1.63

2. To run program with other camera:
   python3 [2 last digits of camera IP]real_time_face_recognize.py
For example:
   python3 62real_time_face_recognize.py
   
3. Face, time and location information of detected people are stored in 2 directories:
   ./Identity_DIR
   ./Stranger_DIR   
   
  


