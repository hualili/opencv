/*-----------------------------------------------------*
 * Program: findContour.cpp;  CTI One Corp. HL         *
 * Date:    Sept. 2018;                                *
 * Purpose: Demo contour computations                  *
 * Another related program: createImage.cpp for        *
 *         the purpose of creating test pattern        * 
 *         image to verify the contour computation.    *
 *-----------------------------------------------------*/ 

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

RNG rng(2345);

int main( int, char** argv )
{ 
  	Mat frame, frame_gray, frame_blur;
	Mat frame_down, frame_tmp, frame_canny;

	frame = imread( argv[1], IMREAD_COLOR);

	if (!frame.data)
	{ 
	printf("No image data \n");
	return -1;
	}

        frame_tmp = frame;  

	//for (int i=0; i < 1; i++) {  
        //pyrDown( frame_tmp, frame_down, Size( frame_tmp.cols/2, frame_tmp.rows/2 ) );//  to 1/4 
	//pyrDown( frame_down, frame_tmp, Size( frame_down.cols/2, frame_down.rows/2 ) ); // to 1/16 
        //}	
	namedWindow("37 Display Image", WINDOW_NORMAL);
	imshow("37 Display Image", frame);
  
	GaussianBlur( frame_tmp, frame_blur, Size( 5, 5 ), 20.0, 20.0 );
	//imshow("40", frame_blur);
  
	Mat frame_binary, frame_blur_gray; 
	cvtColor(frame_blur, frame_blur_gray, cv::COLOR_BGR2GRAY); 
       
    	cv::Scalar mean,stddev; //0:1st channel, 1:2nd channel and 2:3rd channel
   	meanStdDev(frame_blur_gray,mean,stddev,cv::Mat());
 
  	threshold( frame_blur_gray, frame_binary, mean.val[0] - 0.5*stddev.val[0], 255, 0 );
	
//	Canny(frame_binary, frame_canny, 10, 100, 3); // Apply Canny edge detector

	vector<vector<Point> > contours_TREE, contours_CCOMP ;
	vector<Vec4i> hierarchy_TREE, hierarchy_CCOMP;

	findContours( frame_binary, contours_TREE, hierarchy_TREE, 
                RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );
	
	findContours( frame_binary, contours_CCOMP, hierarchy_CCOMP, 
                  RETR_CCOMP, CHAIN_APPROX_SIMPLE, Point(0, 0) );

//	Mat drawing = Mat::zeros( frame_canny.size(), CV_8UC3 );

	Mat drawing_TREE = Mat::zeros( frame_binary.size(), CV_8UC3 );

  	for( int i = 0; i< contours_TREE.size(); i++ )
     	{
       		Scalar color = Scalar( rng.uniform(100, 255), 
                                       rng.uniform(100,255), rng.uniform(100,255) );
       		drawContours( drawing_TREE, contours_TREE, i, color, 2, 8, 
                                       hierarchy_TREE, 0, Point() );
     	}

	namedWindow("79_drawing_TREE ", WINDOW_NORMAL);
	imshow("79_drawing_TREE ", drawing_TREE);

	Mat drawing_CCOMP = Mat::zeros( frame_binary.size(), CV_8UC3 );

  	for( int i = 0; i< contours_CCOMP.size(); i++ )
     	{
       		Scalar color = Scalar( rng.uniform(200, 255), 
                                       rng.uniform(200,255), rng.uniform(200,255) );
       		drawContours( drawing_CCOMP, contours_CCOMP, i, color, 2, 8, 
                                       hierarchy_CCOMP, 0, Point() );
     	}

	namedWindow("92_drawing_CCOMP ", WINDOW_NORMAL); 
	imshow("92_drawing_CCOMP ", drawing_CCOMP);
//
	//print contours values for testing 
    	int idx = 0, largestComp = 0, smallestComp = 0;
    	double maxArea = 0, minArea = 10000;

    	for( ; idx >= 0; idx = hierarchy_CCOMP[idx][0] )
    	{
        const vector<Point>& c = contours_CCOMP[idx];
        double area = fabs(contourArea(Mat(c)));
        if( area > maxArea )
        {
            maxArea = area;
            largestComp = idx;// find the largest contour??
        }
    	}

    	Scalar color( 0, 0, 255 );

	Mat drawing_CCOMP_processed = Mat::zeros( frame_binary.size(), CV_8UC3 );
    	drawContours( drawing_CCOMP_processed, contours_CCOMP, 
			largestComp, color, FILLED, LINE_8, hierarchy_CCOMP );
        namedWindow("113_drawing_CCOMP_processed ", WINDOW_NORMAL); 
	imshow("113_drawing_CCOMP_processed ", drawing_CCOMP_processed);
//
	cout<<"hierarchy_CCOMP[i]"<<endl; 
        for(int i=0;i<hierarchy_CCOMP.size();i++)
         {
          cout<<hierarchy_CCOMP[i]<<endl;
         }

	cout<<"contours_CCOMP_CCOMP[i]"<<endl; 
        for(int i=0;i<contours_CCOMP.size();i++)
         {
          cout<<contours_CCOMP[i]<<endl;
         }


	waitKey(0);
	return 0;
}


