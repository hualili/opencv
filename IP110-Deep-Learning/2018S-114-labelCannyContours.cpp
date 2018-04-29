//-----------------------------------------------*
// program: labelBinary.cpp;  coded by: Harry Li *
// purpose: label each region of binary image.   *
//-----------------------------------------------* 
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;
using namespace std;
int main( int argc, char** argv )
{
    if ( argc != 2 ){
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }

    Mat image, image_gray, image_canny, image_gaussian;
    image = imread( argv[1], 1 );
    if ( !image.data ){
        printf("No image data \n");
        return -1;
    }
    imshow( "Input image", image );

    cvtColor(image, image_gray, CV_BGR2GRAY);
    imshow( "Gray image", image_gray );

    GaussianBlur(image_gray, image_gaussian, Size(17,17), 5, 7);
    imshow( "Gaussian", image_gaussian );

    Canny(image_gaussian, image_canny, 0, 30, 3);
    imshow( "Canny", image_canny );

    Mat image_dst = Mat::zeros(image_gray.rows, image_gray.cols, CV_8UC3);

    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    findContours( image_canny, contours, hierarchy,
        RETR_CCOMP, CHAIN_APPROX_SIMPLE );
    //or:    RETR_EXTERNAL 

    // iterate through all the top-level contours,
    // draw each connected component with its own random color
    int idx = 0;
    for( ; idx >= 0; idx = hierarchy[idx][0] )
    {
        Scalar color( rand()&255, rand()&255, rand()&255 );   //define color 

        drawContours( image_dst, contours, idx, color, FILLED, 8, hierarchy );
    }


// loop through all contour components 
// any contour areas >= Threshold && 
// w/h >= Threshold && 
// w/h <= Threshold 

//for i in range(len(contours)):
//if (area > 2000) &
//(w/h < 2.5) &
//(w/h > 1.5) &
//(hierarchy[0][i][3] > -1):
//#draw contour


    namedWindow( "Components", 1 );
    imshow( "Components", image_dst );
    waitKey(0);
}

