/*------------------------------------------------------*
 * Code: video.cpp                                      *
 * Coded by:  Harry Li;                                 *
 * Date: May 8 2018;                                    *
 * Version: x0.1;                                       *
 * Status : release;                                    *
　*          production;  5/24/18                        * 
 * Purpose: 1. simple demo program for video file       *
 *             display and processing.                  *       
 *------------------------------------------------------*/ 
 
//test, May 5, 2018 
//NO contours 
#include <iostream>
#include <fstream>
#include <string>
#include "opencv2/opencv_modules.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace std;
using namespace cv;

int low_h=0, low_s=18, low_v=0;  //global var, emperical 
int high_h=73, high_s=255, high_v=250; //global var


int main(int argc, char **argv)
{
    bool playVideo = true;
    VideoCapture cap(argv[1]);  //command line input video file
    if(!cap.isOpened())
    {
        cout<<"Unable to open video "<<argv[1]<<"\n";
        return 0;
    }

    Mat frame, frame_threshold, frame_hsv, frame_result;
  
    namedWindow("Video", WINDOW_NORMAL);
    namedWindow("hsv", WINDOW_NORMAL);
    //namedWindow("Track Detection", WINDOW_NORMAL);

    while(1)
    {
        if(playVideo)
            cap >> frame;
        if(frame.empty())
        {
            cout<<"Empty Frame\n";
            return 0;
        }

    cvtColor(frame, frame_hsv, CV_BGR2HSV); 
    /* 
    inRange(frame_hsv,Scalar(low_h,low_s,low_v), 
                Scalar(high_h,high_s,high_v),
                frame_threshold);
    dilate(frame_threshold, frame_result, Mat(), 
            Point(-1, -1), 3, 1, 1);
    */   
        imshow("Video",frame);
        imshow("hsv", frame_hsv); 
        //imshow("Track Detection",frame_result);
  
        char key = waitKey(5);
        if(key == 'p')
            playVideo = !playVideo; 
    }
    return 0;
}
