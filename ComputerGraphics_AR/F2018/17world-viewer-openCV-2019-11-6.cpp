// Example for CMPE297, Coded by: HL, Jan 2019 
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <math.h>
#include <unistd.h> 
 
using namespace cv;
using namespace std;
 
int main(int argc, char** argv)
{
    
#define UpperBD 51
#define PI      3.1415926
#define Num_pts 10

float Xe = 200.0f;
float Ye = 200.0f;
float Ze = 200.0f;
float Rho = sqrt(pow(Xe,2) + pow(Ye,2) + pow(Ze,2));
float D_focal = 20.0f; 

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

typedef struct {
    float X[UpperBD];
    float Y[UpperBD];
    float Z[UpperBD];
} pworld;

typedef struct {
    float X[UpperBD];
    float Y[UpperBD];
    float Z[UpperBD];
} pviewer;

typedef struct{
    float X[UpperBD];
    float Y[UpperBD];
} pperspective;

    pworld  world;
    pviewer viewer;
    pperspective perspective;

    //define the x-y-z world coordinate
    world.X[0] = 0.0;    world.Y[0] =  0.0;   world.Z[0] =  0.0;    // origin
    world.X[1] = 50.0;   world.Y[1] =  0.0;   world.Z[1] =  0.0;    // x-axis
    world.X[2] = 0.0;    world.Y[2] =  50.0;  world.Z[2] =  0.0;    // y-axis
    world.X[3] = 0.0;    world.Y[3] =  0.0;   world.Z[3] =  50.0;   // y-axis

    float sPheta = Ye / sqrt(pow(Xe,2) + pow(Ye,2));
    float cPheta = Xe / sqrt(pow(Xe,2) + pow(Ye,2));
    float sPhi = sqrt(pow(Xe,2) + pow(Ye,2)) / Rho;
    float cPhi = Ze / Rho;

    for(int i = 0; i <= 3; i++)
    {
        viewer.X[i] = -sPheta * world.X[i] + cPheta * world.Y[i];
        viewer.Y[i] = -cPheta * cPhi * world.X[i]
        - cPhi * sPheta * world.Y[i]
        + sPhi * world.Z[i];
        viewer.Z[i] = -sPhi * cPheta * world.X[i]
        - sPhi * cPheta * world.Y[i]
        -cPheta * world.Z[i] + Rho;
    }

    float xMax, yMax, xMin, yMin; 

    for(int i = 0; i <= 3; i++)
    {
        perspective.X[i] = D_focal * viewer.X[i] / viewer.Z[i] ;
        perspective.Y[i] = D_focal * viewer.Y[i] / viewer.Z[i] ;
        if (perspective.X[i] > xMax) xMax = perspective.X[i];
        if (perspective.X[i] < xMin) xMin = perspective.X[i];
        if (perspective.Y[i] > yMax) yMax = perspective.Y[i];
        if (perspective.Y[i] < yMin) yMin = perspective.Y[i];
    }

    Point pt0, pt1, pt2, pt3, pt4;
        pt0.x = perspective.X[0];
        pt0.y = perspective.Y[0];
        pt1.x = perspective.X[1];
        pt1.y = perspective.Y[1];

        pt2.x = perspective.X[2];
        pt2.y = perspective.Y[2];
        pt3.x = perspective.X[3];
        pt3.y = perspective.Y[3];

    line( image, pt0, pt1, Scalar(255,0,0), 5, 8, 0); 
    line( image, pt0, pt2, Scalar(0,255,0), 5, 8, 0); 
    line( image, pt0, pt3, Scalar(0,0,255), 5, 8, 0); 
     
 
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
