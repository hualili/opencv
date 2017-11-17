/*---------------------------------------------------------------*
 * Program: videoFrame.c              Coded by: HL;              *
 * Date: Jan 26, 2016;                Version: x0.1;             *
 * Purpose: To capture image frames from video cam input.        *
 *---------------------------------------------------------------*

compilation and make:  
g++ -ggdb `pkg-config --cflags opencv` -o `basename overlapAvi.c .c` overlapAvi.c `pkg-config --libs opencv` -lm

location: 
cd /home/harry/Desktop/SJSU/EE264/EE264Ubuntu/OpenCV/OpenCV/opencv-2.4.6.1/samples/c/harry/LecVideo/



*/ 

#include "opencv2/opencv.hpp"

using namespace cv;

int main(int, char**)
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat edges;
    //Mat ibuffer;

    namedWindow("edges",1);
    //namedWindow("ibuffer",1);

    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera
        //cvtColor(frame, edges, CV_BGR2GRAY);
        cvtColor(frame, edges, CV_BGR2GRAY);
        //GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        //Canny(edges, edges, 0, 30, 3);
        //imshow("edges", edges);
        imshow("edges", frame);
        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
