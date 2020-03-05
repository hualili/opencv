/*-----------------------------------------------------*
 * Program: contours_2019.cpp;           *
 * Date:    March. 2019;                                *
 * Purpose: Hand wriiten digits localization                  *
 * This program is based on and inspired from 
 *  the professor's HL's class repository   *
 *-----------------------------------------------------*/ 

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h> 
#include <math.h>   
#include "opencv2/opencv_modules.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace std;
using namespace cv;

RNG rng(2345);
int main( int, char** argv )
{ 
  VideoCapture cap(0);
   
  while(1)
  {


  Mat frame, frame_gray, frame_blur;
	Mat frame_down, frame_tmp, frame_canny;
  
  cap >> frame;
	//frame = imread( argv[1], IMREAD_COLOR);

	if (!frame.data)
	{ 
	printf("No image data \n");
	return -1;
	}
  namedWindow("Display original Image", WINDOW_NORMAL);
  imshow("Display original Image", frame);
  frame_tmp = frame;  

	pyrDown( frame_tmp, frame_down, Size( frame_tmp.cols/2, frame_tmp.rows/2 ) );//  to 1/4 
	 
	GaussianBlur( frame_down, frame_blur, Size( 5, 5 ), 10.0, 10.0 );
  
	Mat frame_binary, frame_blur_gray; 
	cvtColor(frame_blur, frame_blur_gray, cv::COLOR_BGR2GRAY); 
       
  cv::Scalar mean,stddev; //0:1st channel, 1:2nd channel and 2:3rd channel
  meanStdDev(frame_blur_gray,mean,stddev,cv::Mat());
 
  threshold( frame_blur_gray, frame_binary, mean.val[0] - 0.5*stddev.val[0], 255, 0 );
	
	vector<vector<Point> > contours_TREE, contours_CCOMP ;
	vector<Vec4i> hierarchy_TREE, hierarchy_CCOMP;

	findContours( frame_binary, contours_TREE, hierarchy_TREE, 
                RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );
	
	findContours( frame_binary, contours_CCOMP, hierarchy_CCOMP, 
                  RETR_CCOMP, CHAIN_APPROX_SIMPLE, Point(0, 0) );

	Mat drawing_TREE = Mat::zeros( frame_binary.size(), CV_8UC3 );
    vector<Rect> boundRect( contours_TREE.size() );
    for( size_t i = 0; i < contours_TREE.size(); i++ )
    {
        
      boundRect[i] = boundingRect( contours_TREE[i] );
        
    }
  	for( int i = 0; i< contours_TREE.size(); i++ )
     	{
       		Scalar color = Scalar( rng.uniform(100, 255), 
                                       rng.uniform(100,255), rng.uniform(100,255) );
       		drawContours( drawing_TREE, contours_TREE, i, color, 2, 8, 
                                       hierarchy_TREE, 0, Point() );
          rectangle( drawing_TREE, boundRect[i].tl(), boundRect[i].br(), color, 2 );
     	}

	namedWindow("ROI using Trees", WINDOW_NORMAL);
	imshow("ROI using Trees", drawing_TREE);

	Mat drawing_CCOMP = Mat::zeros( frame_binary.size(), CV_8UC3 );

  	for( int i = 0; i< contours_CCOMP.size(); i++ )
     	{
       		Scalar color = Scalar( rng.uniform(200, 255), 
                                       rng.uniform(200,255), rng.uniform(200,255) );
       		drawContours( drawing_CCOMP, contours_CCOMP, i, color, 2, 8, 
                                       hierarchy_CCOMP, 0, Point() );
     	}

    	int idx = 0, largestComp = 0, smallestComp = 0;
    	double maxArea = 0, minArea = 10000;

    	for( ; idx >= 0; idx = hierarchy_CCOMP[idx][0] )
    	{
        const vector<Point>& c = contours_CCOMP[idx];
        double area = fabs(contourArea(Mat(c)));
        if( area > maxArea )
        {
            maxArea = area;
            largestComp = idx;
        }
    	}

    	Scalar color( 0, 0, 255 );

	Mat drawing_CCOMP_processed = Mat::zeros( frame_binary.size(), CV_8UC3 );
    	drawContours( drawing_CCOMP_processed, contours_CCOMP, 
			largestComp, color, FILLED, LINE_8, hierarchy_CCOMP );
        
   for( size_t i = 0; i < contours_CCOMP.size(); i++ )
    {
        
        boundRect[i] = boundingRect( contours_CCOMP[i] );
        
    }
    for( int i = 0; i< contours_CCOMP.size(); i++ )
      {
          Scalar color = Scalar( rng.uniform(100, 255), 
                                       rng.uniform(100,255), rng.uniform(100,255) );
          
          rectangle( drawing_CCOMP_processed, boundRect[i].tl(), boundRect[i].br(), color, 2 );
      }
  namedWindow("Processed_digits", WINDOW_NORMAL); 
  imshow("Processed_digits ", drawing_CCOMP_processed);
  char c = (char)waitKey(1);
    if( c == 27 ) 
      break;
 } 
	
	return 0;
}
