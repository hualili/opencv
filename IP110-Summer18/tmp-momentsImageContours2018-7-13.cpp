/*------------------------------------------------------*
 * Code: videoPathLines.cpp                             *
 * Coded by:  Harry Li;                                 *
 * Date: June 26, 2018;                                 *
 * Version: x0.1;                                       *
 * Status : release;                                    *
 * Purpose: 1. detection of shop path with no color     *
 *             information.                             * 
 * To do (6-27-18): 1. future reduce the pyramid        *
 *    resolution to save resources;                     *
 *    2. compute the path boundary and driving path at  *
 *    the center.                                       *    
 *------------------------------------------------------*/ 
 
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h> //usleep( )
#include <math.h>   //sin( )
#include "opencv2/opencv_modules.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace std;
using namespace cv;

//int low_h=0, low_s=18, low_v=0;  //global var, emperical 
//int high_h=73, high_s=255, high_v=250; //global var

#define 	low_h 	0
#define 	low_s 	18
#define 	low_v 	0  //global for color  
#define 	high_h 	73
#define 	high_s	255
#define		high_v	250 //global var

int main( int, char** argv )
{ 
  Mat frame, frame_gray, frame_blur, frame_hsv, frame_result;
  Mat frame_threshold;

  frame = imread( argv[1], 1 );
    
    while(1)
{
  usleep(200000); //micro second 
    /* 
    inRange(frame_hsv,Scalar(low_h,low_s,low_v), 
                Scalar(high_h,high_s,high_v),
                frame_threshold);
    dilate(frame_threshold, frame_result, Mat(), 
            Point(-1, -1), 3, 1, 1);
    */   

	/*--- blur image ---*/  
        Mat frame_down, frame_tmp;      

        frame_tmp = frame;  

	for (int i=0; i < 1; i++) {  
        pyrDown( frame_tmp, frame_down, Size( frame_tmp.cols/2, frame_tmp.rows/2 ) );//  to 1/4 
	pyrDown( frame_down, frame_tmp, Size( frame_down.cols/2, frame_down.rows/2 ) ); // to 1/16 
        }	

	GaussianBlur( frame_tmp, frame_blur, Size( 5, 5 ), 20.0, 20.0 );
	imshow("65", frame_blur);
  
	Mat frame_binary, frame_blur_gray; 
	cvtColor(frame_blur, frame_blur_gray, CV_BGR2GRAY); 
       
    	cv::Scalar mean,stddev; //0:1st channel, 1:2nd channel and 2:3rd channel
   	meanStdDev(frame_blur_gray,mean,stddev,cv::Mat());
 
  	threshold( frame_blur_gray, frame_binary, mean.val[0] - 0.5*stddev.val[0], 255, 0 );

	Mat frame_tmp2 = frame_binary; 
    	dilate(frame_tmp2, frame_binary, Mat(), 
            Point(-1, -1), 3, 1, 1);
	imshow("90", frame_binary); 

	Mat frame_canny; 
	Canny(frame_binary, frame_canny, 10, 100, 3); // Apply Canny edge detector
	imshow("94", frame_canny); 
 
  	vector<vector<Point> > contours;
  	vector<Vec4i> hierarchy;
 
  	findContours( frame_canny, contours, hierarchy, 
                RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );

  	vector<Moments> mu(contours.size() );
	double hu[7];
  	for( size_t i = 0; i < contours.size(); i++ )
    	  { 
	  //mu[i] = moments( contours[i], false ); //for contour i 
	  mu[i] = moments( contours[i] ); //for contour i 
	  cv::HuMoments(mu[i], hu); // now in hu are your 7 Hu-Moments
	  //cout << "HuMoments: " << hu[0], hu[1], hu[2], hu[3] << endl;   
	  cout << "HuMoments 0: " << hu[0] << endl;   
	  cout << "HuMoments 1: " << hu[1] << endl;   
	  cout << "HuMoments 2: " << hu[2] << endl;   
	  cout << "HuMoments 3: " << hu[3] << endl;   
	  cout << "HuMoments 4: " << hu[4] << endl;   
	  cout << "HuMoments 5: " << hu[5] << endl;  
	  cout << "HuMoments 6: " << hu[6] << endl;   
	  cout << "HuMoments 7: " << hu[7] << endl;    
          }
  
	//cv::Moments mom = cv::moments(contours[0]); 

	//x-bar and y-bar 
  	vector<Point2f> mc( contours.size() );
  	for( size_t i = 0; i < contours.size(); i++ )
	  { 
	  mc[i] = Point2f( static_cast<float>(mu[i].m10/mu[i].m00) , 
                        static_cast<float>(mu[i].m01/mu[i].m00) ); 
	  }
 
  	Mat drawing = Mat::zeros( frame_canny.size(), CV_8UC3 );
  	for( size_t i = 0; i< contours.size(); i++ )
     	  {
          Scalar color = Scalar( 0, 255 ,255 );
          drawContours( drawing, contours, (int)i, color, 2, 8, 
                     hierarchy, 0, Point() );
          circle( drawing, mc[i], 4, color, -1, 8, 0 );
      	  }
	imshow("112 ", drawing); 

  	printf("\t Info: Area and Contour Length \n");
  	for( size_t i = 0; i< contours.size(); i++ )
     	 {
       	  printf(" *Contour[%d] - Area (M_00) = %.2f - Area: %.2f - Length: %.2f \n", (int)i, mu[i].m00, contourArea(contours[i]), arcLength( contours[i], true ) );
       	  Scalar color = Scalar( 0, 255, 0 );
       	  drawContours( drawing, contours, (int)i, color, 2, 8, hierarchy, 0, Point() );
       	  circle( drawing, mc[i], 4, color, -1, 8, 0 );
     }
	imshow("122 ", drawing); 

        char key = waitKey(5);
        if(key == 'q') 
            return 0;
}
}
