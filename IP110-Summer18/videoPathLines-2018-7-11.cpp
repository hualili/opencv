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
   
    while(1)
    {
        if(playVideo)
            cap >> frame;
        if(frame.empty())
        {
            cout<<"Empty Frame\n";
            return 0;
        }
     // imshow("Video",frame);

    
      usleep(70000); //micro second 
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
        //hl 7-5-18 to do: check image resolution before reduction to 1/16 


	for (int i=0; i < 1; i++) {  
        pyrDown( frame_tmp, frame_down, Size( frame_tmp.cols/2, frame_tmp.rows/2 ) );//  to 1/4 
	pyrDown( frame_down, frame_tmp, Size( frame_down.cols/2, frame_down.rows/2 ) ); // to 1/16 
        }	

	GaussianBlur( frame_tmp, frame_blur, Size( 5, 5 ), 20.0, 20.0 );
	//imshow("86", frame_blur);
 
   	//cvtColor(frame_blur, frame_hsv, CV_BGR2HSV); 
        //imshow("blured hsv", frame_hsv); 
	
	//Mat frame_canny; 
	//Canny(frame_blur, frame_canny, 180, 190, 7); // Apply Canny edge detector
	//imshow("93", frame_canny); 

	Mat frame_binary, frame_blur_gray; 
	cvtColor(frame_blur, frame_blur_gray, CV_BGR2GRAY); 

	//adaptiveThreshold(frame_gray, frame_binary, 
	//	255, ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY,233,0);

    	cv::Scalar mean,stddev; //0:1st channel, 1:2nd channel and 2:3rd channel
   	meanStdDev(frame_blur_gray,mean,stddev,cv::Mat());
 
  	threshold( frame_blur_gray, frame_binary, mean.val[0] - 0.5*stddev.val[0], 255, 0 );

	Mat frame_tmp2 = frame_binary; 
    	dilate(frame_tmp2, frame_binary, Mat(), 
            Point(-1, -1), 3, 1, 1);
	imshow("112", frame_binary); 

	Mat frame_canny; 
	Canny(frame_binary, frame_canny, 10, 100, 3); // Apply Canny edge detector
	imshow("110", frame_canny); 

        // to do (hl 6-26-18): use color to get more reliable path binarization
        // to do (hl 6-27-18): add path boundary detection
         
        #define ROI_cols_l 0
        #define ROI_rows_l 0
 	#define ROI_l2r_l frame_tmp.cols*0.35  //8 
	#define ROI_t2b_l frame_tmp.rows-1    //20 

        #define ROI_cols_r frame_tmp.cols-frame_tmp.cols*0.35+1 //25
        #define ROI_rows_r 0
 	#define ROI_l2r_r frame_tmp.cols*0.35 //10 
	#define ROI_t2b_r frame_tmp.rows-1
 
	Rect roi_left = Rect(ROI_cols_l, ROI_rows_l,
			ROI_l2r_l, ROI_t2b_l); 
 
	Rect roi_right = Rect(ROI_cols_r, ROI_rows_r,
			ROI_l2r_r, ROI_t2b_r);

        Mat  roi_blur_l = frame_blur(roi_left);   
  	Mat  roi_blur_r = frame_blur(roi_right);

	Mat roi_blur_gray_l, roi_blur_gray_r; 
	Mat roi_blur_gray_binary_l, roi_blur_gray_binary_r; 

	cvtColor(roi_blur_l, roi_blur_gray_l, CV_BGR2GRAY); 
	cvtColor(roi_blur_r, roi_blur_gray_r, CV_BGR2GRAY); 

    	cv::Scalar mean_roi_l,stddev_roi_l; //0:1st channel, 1:2nd channel and 2:3rd channel
   	meanStdDev(roi_blur_l,mean_roi_l,stddev_roi_l,cv::Mat());
    	cv::Scalar mean_roi_r,stddev_roi_r; //0:1st channel, 1:2nd channel and 2:3rd channel
   	meanStdDev(roi_blur_r,mean_roi_r,stddev_roi_r,cv::Mat());

  	threshold(roi_blur_gray_l, roi_blur_gray_binary_l, mean_roi_l.val[0] 
			- 0.5*stddev_roi_l.val[0], 255, 0 );
  	threshold(roi_blur_gray_r, roi_blur_gray_binary_r, mean_roi_r.val[0] 
			- 0.5*stddev_roi_r.val[0], 255, 0 );

	Mat roi_blur_gray_binary_l_canny, roi_blur_gray_binary_r_canny; 
	Canny(roi_blur_gray_binary_l, 
	      roi_blur_gray_binary_l_canny, 10, 100, 3); 
	Canny(roi_blur_gray_binary_r, 
	      roi_blur_gray_binary_r_canny, 10, 100, 3); 
	imshow("155", roi_blur_gray_binary_l_canny); 
	imshow("156", roi_blur_gray_binary_r_canny); 

 	#define min_intersection_hough 20 

    	vector<Vec2f> lines_l, lines_r; // will hold the results of the detection
    	HoughLines(roi_blur_gray_binary_l_canny, 
		   lines_l, 1, CV_PI/180, min_intersection_hough, 0, 0 ); 
   	HoughLines(roi_blur_gray_binary_r_canny, 
		   lines_r, 1, CV_PI/180, min_intersection_hough, 0, 0 );
                   //docs.opencv.org/3.4.0/d9/db0/tutorial_hough_lines.html

	// calculate line orientation 
   	 // Draw the lines on roi left 
	#define PI 3.1415926 
/*
	#define angle_l_thre_low (PI/180)*90
	#define angle_l_thre_up  (PI/180)*160
	#define angle_r_thre_low (PI/180)*45
	#define angle_r_thre_up  (PI/180)*90   
 
	#define angle_l_thre_low (3.14/180.0)*90.0
	#define angle_l_thre_up  (PI/180.0)*160.0
	#define angle_r_thre_low (PI/180.0)*45.0
	#define angle_r_thre_up  (PI/180.0)*90.0   
*/
	#define angle_l_thre_low 17.0*(3.14/180.0) //degree to radians
	#define angle_l_thre_up  60.0*(3.14/180.0)
	#define angle_r_thre_low 110.0*(3.14/180.0)
	#define angle_r_thre_up  135.0*(3.14/180.0) 
	
	//cout << "angle_l_thre_low" << angle_l_thre_low << endl; 
	//cout << "angle_l_thre_up" << angle_l_thre_up << endl; 

    	for( size_t i = 0; i < lines_l.size(); i++ )
    	{
        float rho = lines_l[i][0], theta = lines_l[i][1]; // for thresholding 

 

	if ((theta >= angle_l_thre_low) 
	    &&  (theta <= angle_l_thre_up)) 
	{
	 cout << "theta_left:" << theta << " dgr:" <<(theta * 180.0/3.14) << endl; 
 
         Point pt1, pt2; 
         double a = cos(theta), b = sin(theta);
         double x0 = a*rho, y0 = b*rho;
         pt1.x = cvRound(x0 + 1000*(-b));
         pt1.y = cvRound(y0 + 1000*(a));
         pt2.x = cvRound(x0 - 1000*(-b));
         pt2.y = cvRound(y0 - 1000*(a));
         line( roi_blur_l, pt1, pt2, Scalar(0,0,255), 3, CV_AA);
	}
    	}
    	 // Draw the lines on roi right 

	//cout << "angle_r_thre_low" << angle_r_thre_low << endl; 
	//cout << "angle_r_thre_up" << angle_r_thre_up << endl; 

    	for( size_t i = 0; i < lines_r.size(); i++ )
    	{
        float rho = lines_r[i][0], theta = lines_r[i][1];

	if ((theta >= angle_r_thre_low) 
	    &&  (theta <= angle_r_thre_up)) 
	{

	cout << "theta_right" << theta << " dgr:" << (theta * 180.0/3.14) << endl; 

        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));
        line( roi_blur_r, pt1, pt2, Scalar(0,0,255), 3, CV_AA);
    	}
	} 

        imshow("194 roi_blur_l", roi_blur_l); 
        imshow("195 roi_blur_r", roi_blur_r); 

        // Scalar:Color, 1-thickness, 8-line type, 0-shift position
        rectangle(frame_blur_gray, roi_left, Scalar(0,255,0), 1, 8, 0); 
        rectangle(frame_blur_gray, roi_right, Scalar(0,255,0), 1, 8, 0);
        //imshow("156 frame_blur_gray", frame_blur_gray); 

	#define boundary_binary_thre 200  //for path boundary detection 

	cv::Point pixel; 

        /*--- left roi ---*/  
	for (int y=0; y< roi_blur_l.rows; y++) {   
 	  for (int x=0; x< roi_blur_l.cols-2 ; x++) {
 	     if ( (roi_blur_gray_binary_l.at<cv::Vec3b>(y,x)[0] < 
                   boundary_binary_thre)
                  && 
                  (roi_blur_gray_binary_l.at<cv::Vec3b>(y,x+2)[0] > 
                   boundary_binary_thre)
		)
	       {  
 		roi_blur_l.at<cv::Vec3b>(y,x+1)[0] = 0;
                roi_blur_l.at<cv::Vec3b>(y,x+1)[1] = 255;
 		roi_blur_l.at<cv::Vec3b>(y,x+1)[2] = 0;
                }  
  	}  
	} 

        /*--- right roi ---*/ 
	for (int y=0; y< roi_blur_r.rows; y++) {   
 	  for (int x=0; x< roi_blur_r.cols-2 ; x++) {
 	     if ( (roi_blur_gray_binary_r.at<cv::Vec3b>(y,x)[0] > 
                   boundary_binary_thre)
                  && 
                  (roi_blur_gray_binary_r.at<cv::Vec3b>(y,x+2)[0] < 
                   boundary_binary_thre)
		)
	       {  
 		roi_blur_r.at<cv::Vec3b>(y,x+1)[0] = 0;
                roi_blur_r.at<cv::Vec3b>(y,x+1)[1] = 255;
 		roi_blur_r.at<cv::Vec3b>(y,x+1)[2] = 0;
                }  
  	}  
	}

 	//imshow("boundary left",frame_binary);
	//imshow("231 roi_blur_l",roi_blur_l); 
	//imshow("232 roi_blur_r",roi_blur_r);   
 
	// use feature points on roi_left to generate left line

        // use feature points on roi_right to generate right line  

        // hl 6-27-18 from boundary to generate 2 path outlines 

        // hl 6-27-18 from 2 path outlines to generate center green line 
 

        /*--- Hough Line detection ---*/ 

  
        char key = waitKey(5);
        if(key == 'p')
            playVideo = !playVideo; 
    }
    return 0;
}
