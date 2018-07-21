/*-----------------------------------------------------------------------------------* 
 *  Program: kmean.cpp                                                               *
 *  Coded by: OpenCV samples           Date: Jul 18, 18                              *
 *  Version: x01.0                     Status: tested                                *
 *  Purpose:                                                                         *  
 *    Kmean cluster algorithm.                                                       *  
 *-----------------------------------------------------------------------------------*/

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include <iostream>
 
using namespace cv;
using namespace std;
 
int main( int /*argc*/, char** /*argv*/ )
{
 cout << "\n double kmeans(const Mat& samples, int clusterCount, Mat& labels, TermCriteria termcrit, int attempts, int flags, Mat* centers) \n\n\n" << endl;
  
 int clusterCount = 2;
 int dimensions = 3;   //5
 int sampleCount = 4;
 
 Mat points(sampleCount,dimensions, CV_32F,Scalar(0));
 Mat labels;
 Mat centers(clusterCount, 1, points.type());
 
   // 1 feature vector  
   points.at<float>(0,0)=10; points.at<float>(0,1)=20; points.at<float>(0,2)=20;

   // 2nd feature vector 
   points.at<float>(1,0)=0;  points.at<float>(1,1)=0; points.at<float>(1,2)=0;

   // 3rd feature vector 
   points.at<float>(2,0)=0;  points.at<float>(2,1)=0; points.at<float>(2,2)=0;

   // 4th feature vector 
   points.at<float>(3,0)=5;  points.at<float>(3,1)=4; points.at<float>(3,2)=4;
 
 kmeans(points, clusterCount, labels, TermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 10, 1.0), 3, KMEANS_PP_CENTERS, centers);
    // we can print the matrix directly.
 cout<<"Data: \n"<<points<<endl;
 cout<<"Center: \n"<<centers<<endl;
 cout<<"Labels: \n"<<labels<<endl;
 return 0;
}
