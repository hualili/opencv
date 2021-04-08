'''++++++++++++++++++++++++++++++++++++++++++++++++++
'  File    : README.txt                             +
'  Date    : Apr. 5, 2021                           +
'  Created by: YY                                   +
'  Purpose : To run Yolov4/TensorFlow               +
'  Note    : HL 2021-4-5: updated the part on       +
'            yolo4.weights download information.    + 
'+++++++++++++++++++++++++++++++++++++++++++++++++'''

Refernece URL
https://github.com/theAIGuysCode/tensorflow-yolov4-tflite

Prerequisite:
1. Anaconda

2. Create a Anaconda virtual environment
  2.1 Download all files from the reference URL
  2.2 Open a terminal in the 2.1 directory
  2.3 Perform the below command
     (CPU) conda env create -f conda-cpu.yml
     (GPU) conda env create -f conda-gpu.yml


To run the image processing program
1. Open a terminal in tensorflow-yolov4-tflite-master folder

2. Activate the Anaconda environment
  conda activate yolov4-cpu
  conda activate yolov4-gpu
  
Note (HL, 2021-4-5) before running to 3 below, you will need to 
Download the yolo4.weights from this link
https://drive.google.com/u/1/uc?id=1cewMfusmPjYWbrnuJRuKhPMwRe_b9PaT&export=download
(based on the github information of yolo4)
and place this file into the ./data folder of the yolo4 distribution code 

3. Convert darknet weights to tensorflow
  python save_model.py --weights ./data/yolov4.weights --output ./checkpoints/yolov4-416 --input_size 416 --model yolov4 

4. Run Yolov4 on image 
  python detect.py --weights ./checkpoints/yolov4-416 --size 416 --model yolov4 --images ./data/images/kite.jpg

5. Run Yolov4 on video 
  python detect_video.py --weights ./checkpoints/yolov4-416 --size 416 --model yolov4 --video ./data/video/video.mp4 --output ./detections/results.avi


NOTE: This example uses Yolov4/TensorFlow, Not Yolov4/Darknet

