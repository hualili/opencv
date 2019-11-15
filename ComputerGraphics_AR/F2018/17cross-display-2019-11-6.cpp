// Example for CMPE297, Coded by: HL, Jan 2019 
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
 
using namespace cv;
using namespace std;
 
int main(int argc, char** argv)
{
    
  Mat image = imread( argv[1], 1 );
    if (image.empty())
    {
        cout << "Could not open or find the image" << endl;
        cin.get(); //wait for any key press
        return -1;
    }
 
    cout<<" Demo Display Image "<<endl; 
  
    namedWindow("Display the image", CV_WINDOW_NORMAL);  

    Mat image_result;

    int width = image.cols; 
    int height = image.rows; 

    Point pt1, pt2, pt3, pt4;
        pt1.x = 0;
        pt1.y = height/2;
        pt2.x = width;
        pt2.y = height/2;

        pt3.x = width/2;
        pt3.y = 0;
        pt4.x = width/2;
        pt4.y = height;

    
    line( image, pt1, pt2, Scalar(0,255,255), 5, 8, 0); 
    line( image, pt3, pt4, Scalar(0,255,255), 5, 8, 0); 
/*
https://docs.opencv.org/2.4/modules/core/doc/drawing_functions.html#line
C++: void line(Mat& img, Point pt1, Point pt2, const Scalar& color, int thickness=1, int lineType=8, int shift=0)

Parameters:	
    img – Image.
    pt1 – First point of the line segment.
    pt2 – Second point of the line segment.
    color – Line color.
    thickness – Line thickness.
    lineType –

    Type of the line:
        8 (or omitted) - 8-connected line.
        4 - 4-connected line.
        CV_AA - antialiased line.
    shift – Number of fractional bits in the point coordinates.



*/ 

    image_result = image; 
    imshow("Display the image", image_result); 
 
    waitKey(0);
    return(0);
}
