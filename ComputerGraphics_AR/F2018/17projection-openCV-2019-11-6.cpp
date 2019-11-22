// Example for CMPE297, Coded by: HL, Jan 2019 
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

//#include <math.h>
//#include <unistd.h> 
 
using namespace cv;
using namespace std;
 
int main(int argc, char** argv)
{
    
#define UpperBD 10
#define PI      3.1415926
//#define Num_pts 10

float Xe = 800.0;
float Ye = 800.0;
float Ze = 300.0;
float Rho = sqrt(pow(Xe,2) + pow(Ye,2) + pow(Ze,2));
float D_focal = 100.0; 

    Mat image = imread( argv[1], 1 );
    Mat image_result;
    Mat image2(1024, 1024, CV_8UC3);

    int width = image2.cols; 
    int height = image2.rows; 

    cout << "width image2" << width << endl;
    cout << "height image2" << height << endl;

    if (image.empty())
    {
        cout << "Could not open or find the image" << endl;
        cin.get(); //wait for any key press
        return -1;
    }
  
    namedWindow("Display the image", CV_WINDOW_NORMAL);  

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
    pperspective perspective, new_perspective;

    //define the x-y-z world coordinate
    world.X[0] = 0.0;    world.Y[0] =  0.0;   world.Z[0] =  0.0;    // origin
    world.X[1] = 500.0;  world.Y[1] =  0.0;   world.Z[1] =  0.0;    // x-axis
    world.X[2] = 0.0;    world.Y[2] =  500.0; world.Z[2] =  0.0;    // y-axis
    world.X[3] = 0.0;    world.Y[3] =  0.0;   world.Z[3] =  500.0;  // z-axis 

    //define projection plane
    world.X[4] = 450.0;     world.Y[4] = -150.0;    world.Z[4] = 0.0;    //plane left bottom corner 
    world.X[5] = 450.0;     world.Y[5] = 150.0;     world.Z[5] = 0.0;    //right bottom corner 
    world.X[6] = 450.0;     world.Y[6] = 150.0;     world.Z[6] = 200.0;  //right upper corner  
    world.X[7] = 450.0;     world.Y[7] = -150.0;    world.Z[7] = 200.0;  //left upperr corner 

    float sPheta = Ye / sqrt(pow(Xe,2) + pow(Ye,2));
    float cPheta = Xe / sqrt(pow(Xe,2) + pow(Ye,2));
    float sPhi = sqrt(pow(Xe,2) + pow(Ye,2)) / Rho;
    float cPhi = Ze / Rho;

    for(int i = 0; i < 8; i++)
    {
        viewer.X[i] = - sPheta * world.X[i] + cPheta * world.Y[i];
        viewer.Y[i] = - cPheta * cPhi * world.X[i]
        - cPhi * sPheta * world.Y[i]
        + sPhi * world.Z[i];
        viewer.Z[i] = - sPhi * cPheta * world.X[i]
        - sPhi * cPheta * world.Y[i]
        - cPheta * world.Z[i] + Rho;

/*
        std::cout << "world.X[i] " << i << " " << world.X[i] << std::endl;
        std::cout << "world.Y[i] " << i << " " << world.Y[i] << std::endl; 
        std::cout << "world.Z[i] " << i << " " << world.Z[i] << std::endl;
        std::cout << "viewer.X[i] " << i << " " << viewer.X[i] << std::endl;
        std::cout << "viewer.Y[i] " << i << " " << viewer.Y[i] << std::endl; 
        std::cout << "viewer.Z[i] " << i << " " << viewer.Z[i] << std::endl;
*/
    }

    //float xMax, yMax, xMin, yMin; 

    for(int i = 0; i < 8; i++)
    {
        perspective.X[i] = D_focal * viewer.X[i] / viewer.Z[i] ;
        perspective.Y[i] = D_focal * viewer.Y[i] / viewer.Z[i] ;

        //std::cout << "perspective.X[i] " << i << " " << perspective.X[i] << std::endl;
        //std::cout << "perspective.Y[i] " << i << " " << perspective.Y[i] << std::endl; 
 
        //if (perspective.X[i] > xMax) xMax = perspective.X[i];
        //if (perspective.X[i] < xMin) xMin = perspective.X[i];
        //if (perspective.Y[i] > yMax) yMax = perspective.Y[i];
        //if (perspective.Y[i] < yMin) yMin = perspective.Y[i];
    }

    for(int i = 0; i < 8; i++) //physical to virtual 
    {
        new_perspective.X[i] =  perspective.X[i] + (width/2.0);
        new_perspective.Y[i] =  (height/2.0) - perspective.Y[i];

        std::cout << "new_perspective.X[i] " << i << " " << new_perspective.X[i] << std::endl;
        std::cout << "new_perspective.Y[i] " << i << " " << new_perspective.Y[i] << std::endl; 
    }

    Point pt0, pt1, pt2, pt3;   //for world coordinate 
    Point pt4, pt5, pt6, pt7;   //for projection plane  

 
        pt0.x = new_perspective.X[0];
        pt0.y = new_perspective.Y[0];
        pt1.x = new_perspective.X[1];
        pt1.y = new_perspective.Y[1];

        pt2.x = new_perspective.X[2];
        pt2.y = new_perspective.Y[2];
        pt3.x = new_perspective.X[3];
        pt3.y = new_perspective.Y[3];
 

        std::cout << "pt0.x " << pt0.x << std::endl;
        std::cout << "pt0.y " << pt0.y << std::endl;
        std::cout << "pt1.x " << pt1.x << std::endl;
        std::cout << "pt1.y " << pt1.y << std::endl;
        std::cout << "pt2.x " << pt2.x << std::endl;
        std::cout << "pt2.y " << pt2.y << std::endl;
        std::cout << "pt3.x " << pt3.x << std::endl;
        std::cout << "pt3.y " << pt3.y << std::endl;

    // world coordinate 
    line( image2, pt0, pt1, Scalar(0,0,255), 2, 2, 0); //red 255 b:g:r for opencv
    line( image2, pt0, pt2, Scalar(0,255,0), 2, 2, 0); //green 255
    line( image2, pt0, pt3, Scalar(255,0,0), 2, 2, 0); //blue 255 

    // projection plane  

        pt4.x = new_perspective.X[4];
        pt4.y = new_perspective.Y[4];
        pt5.x = new_perspective.X[5];
        pt5.y = new_perspective.Y[5];
        line( image2, pt4, pt5, Scalar(0,0,255), 2, 3, 0); //base line

        pt6.x = new_perspective.X[6];
        pt6.y = new_perspective.Y[6];
        line( image2, pt6, pt5, Scalar(0,0,255), 2, 3, 0); 

        pt7.x = new_perspective.X[7];
        pt7.y = new_perspective.Y[7];
        line( image2, pt6, pt7, Scalar(0,0,255), 2, 3, 0); //top line 
        line( image2, pt4, pt7, Scalar(0,0,255), 2, 3, 0); 
/*
        pt1.x = 0;
        pt1.y = height/2;
        pt2.x = width;
        pt2.y = height/2;

        pt3.x = width/2;
        pt3.y = 0;
        pt4.x = width/2;
        pt4.y = height;
*/
    
    //line( image, pt1, pt2, Scalar(0,255,255), 5, 8, 0); 
    //line( image, pt3, pt4, Scalar(0,255,255), 5, 8, 0); 
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

    imshow("Projection Image", image2); 
 
    waitKey(0);
    return(0);
}
