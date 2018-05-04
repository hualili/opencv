/*-----------------------------------------------*
 * Program: inRangeColor.cpp;                    *
 * Coded by:  HL;    Reference: On line;         *
 * Date: April 2018;                             *
 * Version: x0.1;                                *
 * Status : debug;                               *
 * Purpose: to remove reflection;                * 
 *          changed BGR to HSV;                  * 
 *-----------------------------------------------*/ 

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <stdlib.h>
using namespace std;
using namespace cv;
 
/*
void on_low_r_thresh_trackbar(int, void *);
void on_high_r_thresh_trackbar(int, void *); 
void on_low_g_thresh_trackbar(int, void *);
void on_high_g_thresh_trackbar(int, void *);
void on_low_b_thresh_trackbar(int, void *);
void on_high_b_thresh_trackbar(int, void *);
*/
void on_low_h_thresh_trackbar(int, void *);
void on_high_h_thresh_trackbar(int, void *); 
void on_low_s_thresh_trackbar(int, void *);
void on_high_s_thresh_trackbar(int, void *);
void on_low_v_thresh_trackbar(int, void *);
void on_high_v_thresh_trackbar(int, void *);

/** Global Variables */
/*
int low_r=30, low_g=30, low_b=30;
int high_r=100, high_g=100, high_b=100;
*/
int low_h=30, low_s=30, low_v=30;
int high_h=100, high_s=100, high_v=100;

    

int main( int argc, char** argv )
{
    if ( argc != 2 ){
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }
    
    Mat frame, frame_threshold, frame_hsv;
    //VideoCapture cap(0);
    //VideoCapture cap(＂output.avi＂);
 
    frame = imread( argv[1], 1 );
    if ( !frame.data ){
        printf("No image data \n");
        return -1;
    }
 
    cvtColor(frame, frame_hsv, CV_BGR2HSV); 
    namedWindow("Video Capture", WINDOW_NORMAL);
    namedWindow("hsv", WINDOW_NORMAL);
    namedWindow("Object Detection", WINDOW_NORMAL);
    //-- Trackbars to set thresholds
/*
    createTrackbar("Low R","Object Detection", &low_r, 255, on_low_r_thresh_trackbar);
    createTrackbar("High R","Object Detection", &high_r, 255, on_high_r_thresh_trackbar);
    createTrackbar("Low G","Object Detection", &low_g, 255, on_low_g_thresh_trackbar);
    createTrackbar("High G","Object Detection", &high_g, 255, on_high_g_thresh_trackbar);
    createTrackbar("Low B","Object Detection", &low_b, 255, on_low_b_thresh_trackbar);
    createTrackbar("High B","Object Detection", &high_b, 255, on_high_b_thresh_trackbar);
*/    
    createTrackbar("Low h","Object Detection", &low_h, 255, on_low_h_thresh_trackbar);
    createTrackbar("High h","Object Detection", &high_h, 255, on_high_h_thresh_trackbar);
    createTrackbar("Low s","Object Detection", &low_s, 255, on_low_s_thresh_trackbar);
    createTrackbar("High s","Object Detection", &high_s, 255, on_high_s_thresh_trackbar);
    createTrackbar("Low v","Object Detection", &low_v, 255, on_low_v_thresh_trackbar);
    createTrackbar("High v","Object Detection", &high_v, 255, on_high_v_thresh_trackbar);
    while((char)waitKey(1)!='q'){
        //cap>>frame;
        if(frame.empty()) break;
        //-- Detect the object based on RGB Range Values
        inRange(frame_hsv,Scalar(low_h,low_s,low_v), Scalar(high_h,high_s,high_v),frame_threshold);
        //-- Show the frames
        imshow("Video Capture",frame);
        imshow("hsv", frame_hsv); 
        imshow("Object Detection",frame_threshold);
        //! [show]
    }
    return 0;
}

void on_low_h_thresh_trackbar(int, void *)
{
    low_h = min(high_h-1, low_h);
    setTrackbarPos("Low h","Object Detection", low_h);
}
 
void on_high_h_thresh_trackbar(int, void *)
{
    high_h = max(high_h, low_h+1);
    setTrackbarPos("High h", "Object Detection", high_h);
}
 
void on_low_s_thresh_trackbar(int, void *)
{
    low_s = min(high_s-1, low_s);
    setTrackbarPos("Low s","Object Detection", low_s);
}
 
void on_high_s_thresh_trackbar(int, void *)
{
    high_s = max(high_s, low_s+1);
    setTrackbarPos("High s", "Object Detection", high_s);
}

void on_low_v_thresh_trackbar(int, void *)
{
    low_v= min(high_v-1, low_v);
    setTrackbarPos("Low v","Object Detection", low_v);
}

void on_high_v_thresh_trackbar(int, void *)
{
    high_v = max(high_v, low_v+1);
    setTrackbarPos("High v", "Object Detection", high_v);
}


/*
void on_low_r_thresh_trackbar(int, void *)
{
    low_r = min(high_r-1, low_r);
    setTrackbarPos("Low R","Object Detection", low_r);
}
 
void on_high_r_thresh_trackbar(int, void *)
{
    high_r = max(high_r, low_r+1);
    setTrackbarPos("High R", "Object Detection", high_r);
}
 
void on_low_g_thresh_trackbar(int, void *)
{
    low_g = min(high_g-1, low_g);
    setTrackbarPos("Low G","Object Detection", low_g);
}
 
void on_high_g_thresh_trackbar(int, void *)
{
    high_g = max(high_g, low_g+1);
    setTrackbarPos("High G", "Object Detection", high_g);
}

void on_low_b_thresh_trackbar(int, void *)
{
    low_b= min(high_b-1, low_b);
    setTrackbarPos("Low B","Object Detection", low_b);
}

void on_high_b_thresh_trackbar(int, void *)
{
    high_b = max(high_b, low_b+1);
    setTrackbarPos("High B", "Object Detection", high_b);
}
*/
