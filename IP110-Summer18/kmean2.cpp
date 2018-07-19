/*-----------------------------------------------------------------------------------* 
 *  Program: kmean2.cpp                                                               *
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
 int dimensions = 4;   //5
 int sampleCount = 50;
 
 Mat points(sampleCount,dimensions, CV_32F,Scalar(10));
 Mat labels;
 Mat centers(clusterCount, 1, points.type());

 // values of 1st half of data set is set to 10
 //change the values of 2nd half of the data set; i.e. set it to 20
 
 for(int i =24;i<points.rows;i++)
 {
  for(int j=0;j<points.cols;j++)
  {
   points.at<float>(i,j)=20;
  }
 }
 
 kmeans(points, clusterCount, labels, TermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 10, 1.0), 3, KMEANS_PP_CENTERS, centers);
    // we can print the matrix directly.
 cout<<"Data: \n"<<points<<endl;
 cout<<"Center: \n"<<centers<<endl;
 cout<<"Labels: \n"<<labels<<endl;
 return 0;
}
