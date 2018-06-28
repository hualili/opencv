/*------------------------------------------------------*
 * Code: videoPathLines.cpp                             *
 * Coded by:  Harry Li;                                 *
 * Date: June 26, 2018;                                 *
 * Version: x0.1;                                       *
 * Status : release;                                    *
 * Purpose: 1. detection of shop path with no color     *
 *             information.                             *    
 *------------------------------------------------------*/ 
 
//test, May 5, 2018 
//NO contours 
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h> //usleep( )
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

      imshow("Video",frame);

    
      usleep(60000); //micro second 
    /* 
    inRange(frame_hsv,Scalar(low_h,low_s,low_v), 
                Scalar(high_h,high_s,high_v),
                frame_threshold);
    dilate(frame_threshold, frame_result, Mat(), 
            Point(-1, -1), 3, 1, 1);
    */   

	/*--- blur image ---*/  
   
        Mat frame_down, frame_tmp, frame_blur;      

        frame_tmp = frame; 
	//for (int i=0; i <= 2; i++) {
        pyrDown( frame_tmp, frame_down, Size( frame_tmp.cols/2, frame_tmp.rows/2 ) );
	pyrDown( frame_down, frame_tmp, Size( frame_down.cols/2, frame_down.rows/2 ) );
	//pyrUp( frame_down, frame_blur, Size( frame_down.cols*2, frame_down.rows*2 ) );
        //}
	

	GaussianBlur( frame_tmp, frame_blur, Size( 5, 5 ), 20.0, 20.0 );
	imshow("image_blur", frame_blur);
 

   	cvtColor(frame_blur, frame_hsv, CV_BGR2HSV); 
        imshow("hsv", frame_hsv); 
	
	//Mat frame_canny; 
	//Canny(frame_hsv, frame_canny, 180, 190, 7); // Apply Canny edge detector
	//imshow("frame_canny", frame_canny); 

	Mat frame_binary, frame_gray; 
	cvtColor(frame_blur, frame_gray, CV_BGR2GRAY); 
        imshow("gray", frame_gray); 

	adaptiveThreshold(frame_gray, frame_binary, 255, ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY,233,0);
	imshow("frame_binary adaptive threshold", frame_binary); 

 

    	cv::Scalar mean,stddev; //0:1st channel, 1:2nd channel and 2:3rd channel
   	meanStdDev(frame_gray,mean,stddev,cv::Mat());
        //stddev.val[0]
 

	//cv:Scalar tempVal = mean( frame_gray );
	//float frameMean = tempVal.val[0]; 
  	threshold( frame_gray, frame_binary, mean.val[0] - 0.5*stddev.val[0], 255, 0 );
	imshow("frame_binary threshold", frame_binary); 


        // to do 1: use color to touch up the binarization


        /*--- Hough Line detection ---*/ 

  
        char key = waitKey(5);
        if(key == 'p')
            playVideo = !playVideo; 
    }
    return 0;
}
