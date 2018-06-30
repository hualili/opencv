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
  
    //namedWindow("Video", WINDOW_NORMAL);
    //namedWindow("hsv", WINDOW_NORMAL);
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
	for (int i=0; i <= 1; i++) {
        pyrDown( frame_tmp, frame_down, Size( frame_tmp.cols/2, frame_tmp.rows/2 ) );
	pyrDown( frame_down, frame_tmp, Size( frame_down.cols/2, frame_down.rows/2 ) ); 
        }
	

	GaussianBlur( frame_tmp, frame_blur, Size( 5, 5 ), 20.0, 20.0 );
	//imshow("image_blur", frame_blur);
 
   	//cvtColor(frame_blur, frame_hsv, CV_BGR2HSV); 
        //imshow("blured hsv", frame_hsv); 
	
	//Mat frame_canny; 
	//Canny(frame_hsv, frame_canny, 180, 190, 7); // Apply Canny edge detector
	//imshow("frame_canny", frame_canny); 

	Mat frame_binary, frame_blur_gray; 
	cvtColor(frame_blur, frame_blur_gray, CV_BGR2GRAY); 
        //imshow("blured gray", frame_blur_gray); 

	//adaptiveThreshold(frame_gray, frame_binary, 
	//	255, ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY,233,0);

    	cv::Scalar mean,stddev; //0:1st channel, 1:2nd channel and 2:3rd channel
   	meanStdDev(frame_blur_gray,mean,stddev,cv::Mat());
 
  	threshold( frame_blur_gray, frame_binary, mean.val[0] - 0.5*stddev.val[0], 255, 0 );
	imshow("frame_binary threshold", frame_binary); 


        // to do (hl 6-26-18): use color to get more reliable path binarization
        // to do (hl 6-27-18): add path boundary detection
        // first define roi_left and roi_right
        #define col_left_path_ROI 0
        #define row_left_path_ROI 0
 	#define width_left_path_ROI 8
	#define height_left_path_ROI 20
        #define col_right_path_ROI 25
        #define row_right_path_ROI 0
 	#define width_right_path_ROI 10
	#define height_right_path_ROI 20
 
	Rect roi_left = Rect(col_left_path_ROI, row_left_path_ROI,
			width_left_path_ROI, height_left_path_ROI); 
 
	Rect roi_right = Rect( col_right_path_ROI,row_right_path_ROI,
			width_right_path_ROI, height_right_path_ROI);

        //Mat  roi_binary = frame_binary(roi_left);      //map to image_roi
        Mat  roi_blur_l = frame_blur(roi_left);   
  	Mat  roi_blur_r = frame_blur(roi_right);

        imshow("137 roi_blur_l", roi_blur_l); 
	imshow("138 roi_blur_r", roi_blur_r); 

        // Scalar:Color, 1-thickness, 8-line type, 0-shift position
        rectangle(frame_blur_gray, roi_left, Scalar(0,255,0), 1, 8, 0); 
        rectangle(frame_blur_gray, roi_right, Scalar(0,255,0), 1, 8, 0);
        imshow("142 frame_blur_roi_right", frame_blur_gray); 

        // parse roi_left and roi_right for feature points 
	#define boundary_binary_thre 200  //for path boundary detection 

	for (int i=0; i< width_left_path_ROI; i++) {
	   for (int j=0; j< height_left_path_ROI; j++) {

	       Vec3b roi_l_pxl_binary_right = frame_binary.at< Vec3b >( Point(i, j+1) ); 
	       Vec3b roi_l_pxl_binary = frame_binary.at< Vec3b >( Point(i, j) ); 
	        
 	       if ((roi_l_pxl_binary_right.val[0] - roi_l_pxl_binary.val[0]) >
			 boundary_binary_thre) {
                   /* ploting the result back to the original blur image, you can remove it
                      if not debuging, except keep the boundary points for find line euqation
                   */ 
		   //Vec3b roi_l_pxl_original_blur = frame_blur.at< Vec3b >(Point( i, j ) );
                   //Vec3b roi_l_pxl_original_blur_right=frame_blur.at< Vec3b >(Point(i,j+1));
		   //Vec3b roi_l_pxl_original_blur;
                   Vec3b roi_l_pxl_original_blur_right;
                   roi_l_pxl_original_blur_right.val[0]=0;    //char 
		   roi_l_pxl_original_blur_right.val[1]=255; 
		   roi_l_pxl_original_blur_right.val[2]=0; 
		   frame_blur.at<Vec3b>(Point(i,j+1)) = roi_l_pxl_original_blur_right;
                   }  
  	} 
	} 
	//for the right roi 
	for (int i=0; i< width_right_path_ROI; i++) {
	   for (int j=1; j< height_right_path_ROI; j++) {
 
 	       Vec3b roi_r_pxl_binary_left = frame_binary.at< Vec3b >( Point(i, j-1) ); 
	       Vec3b roi_r_pxl_binary = frame_binary.at< Vec3b >(Point(i, j)); //row, col
	        
 	        if ((roi_r_pxl_binary_left.val[0] - roi_r_pxl_binary.val[0]) >
			 boundary_binary_thre) {
                   /* ploting the result back to the original blur image, you can remove it
                      if not debuging, except keep the boundary points for find line euqation
                   */ 
		   Vec3b roi_r_pxl_original_blur_left = frame_blur.at< Vec3b >(Point(i, j-1));
                   Vec3b roi_r_pxl_original_blur = frame_blur.at< Vec3b >(Point(i, j) );
                   roi_r_pxl_original_blur.val[0]=0;    //char 
		   roi_r_pxl_original_blur.val[1]=255; 
		   roi_r_pxl_original_blur.val[2]=0; 
		   frame_blur.at<Vec3b>(Point(i,j)) = roi_r_pxl_original_blur;
                   }  
  	} 
	} 

	//imshow("boundary left",frame_binary);
	imshow("161 frame blur boundary",frame_blur);  
 
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
