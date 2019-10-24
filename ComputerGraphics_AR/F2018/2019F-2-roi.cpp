#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace cv;
int main(int argc, char** argv ) {
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
int x=20, y=20, w=40, h=60;
Rect region_of_interest = Rect(x, y, w, h);
Mat image_roi = image(region_of_interest);
imshow("Image", image);
imshow("ROI", image_roi);
waitKey(0);
return 0;
}
