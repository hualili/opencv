#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
 
using namespace cv;
using namespace std;

int main()
    {
        int pixel_value1 = 0, pixel_value2 = 0;
        Mat image = Mat(100, 100, CV_8UC1, Scalar(127));

        pixel_value1 = image.at<uchar>(10, 10);//if you know the position of the pixel
        cout << "pixel_value1: " << pixel_value1 << endl;

        for (int x = 0;x < image.rows; x++)//To loop through all the pixels
        {
            for (int y = 0; y < image.cols; y++)
            {
                pixel_value2 = image.at<uchar>(x,y);

                cout << "pixel_value2: " << pixel_value2 << endl;
            }
        }

        return 0;
    }
