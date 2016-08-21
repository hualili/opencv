/* 
  Program: DisplayImage.cpp; 
  Coded by: HL from refenece of OpenCV  
  Date: March 2016 
  Purpose: 
        Demo 
*/ 
#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace cv;
int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }
    Mat image;
    image = imread( argv[1], 1 );
    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    namedWindow("Display Image OpenGL", WINDOW_OPENGL );
    //namedWindow("Display Image OpenGL", WINDOW_NORMAL );
    //namedWindow("Display Image 2", 0 );
    imshow("Display Image", image);
    waitKey(0);
    return 0;
}

