/*-----------------------------------------------------*
 * Program: findContour.cpp;  CTI One Corp. HL         *
 * Date:    Sept. 2018;                                *
 * Purpose: Demo contour computations                  *
 * Another related program: createImage.cpp for        *
 *         the purpose of creating test pattern        *
 *         image to verify the contour computation.    *
 *-----------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h> //usleep( )
#include <math.h>   //sin( )
#include "opencv2/opencv_modules.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace std;
using namespace cv;

RNG rng(12345);

int main( int, char** argv )
{
        Mat frame, frame_gray, frame_blur;
        Mat frame_down, frame_tmp, frame_canny;

        frame = imread( argv[1], IMREAD_COLOR);

        if (!frame.data)
        {
        printf("No image data \n");
        return -1;
        }

        frame_tmp = frame;

        //for (int i=0; i < 1; i++) {
        //pyrDown( frame_tmp, frame_down, Size( frame_tmp.cols/2, frame_tmp.rows/2 ) );//  to 1/4
        //pyrDown( frame_down, frame_tmp, Size( frame_down.cols/2, frame_down.rows/2 ) ); // to 1/16
        //}
        namedWindow("43 Display Image", WINDOW_AUTOSIZE);
        imshow("43 Display Image", frame);

        GaussianBlur( frame_tmp, frame_blur, Size( 5, 5 ), 20.0, 20.0 );
        //imshow("47", frame_blur);

        Mat frame_binary, frame_blur_gray;
        cvtColor(frame_blur, frame_blur_gray, cv::COLOR_BGR2GRAY);

        cv::Scalar mean,stddev; //0:1st channel, 1:2nd channel and 2:3rd channel
        meanStdDev(frame_blur_gray,mean,stddev,cv::Mat());

        threshold( frame_blur_gray, frame_binary, mean.val[0] - 0.5*stddev.val[0], 255, 0 );

        //Canny(frame_binary, frame_canny, 10, 100, 3); // Apply Canny edge detector

        vector<vector<Point> > contours_TREE, contours_CCOMP ;
        vector<Vec4i> hierarchy_TREE, hierarchy_CCOMP;

        findContours( frame_binary, contours_TREE, hierarchy_TREE,
                RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );

        findContours( frame_binary, contours_CCOMP, hierarchy_CCOMP,
                  RETR_CCOMP, CHAIN_APPROX_SIMPLE, Point(0, 0) );

        Mat drawing_TREE = Mat::zeros( frame_binary.size(), CV_8UC3 );
        cout << "hierarchy_TREE:" << endl;

        for( int i = 0; i< contours_TREE.size(); i++ )
        {
                Scalar color = Scalar( rng.uniform(100, 255),
                                       rng.uniform(100,255), rng.uniform(100,255) );
                drawContours( drawing_TREE, contours_TREE, i, color, 2, 8,
                                       hierarchy_TREE, 0, Point());
                cout << "countour " << i << " [ne, pr, ch, pa]: "
                     << hierarchy_TREE [i] << endl;
        }

        cout << endl;
        imshow("81 drawing_TREE ", drawing_TREE);
        Mat drawing_CCOMP = Mat::zeros( frame_binary.size(), CV_8UC3 );
        cout << "hierarchy_CCOMP:" << endl;

        for( int i = 0; i< contours_CCOMP.size(); i++ )
        {
                Scalar color = Scalar( rng.uniform(200, 255),
                                       rng.uniform(200,255), rng.uniform(200,255) );
                drawContours( drawing_CCOMP, contours_CCOMP, i, color, 2, 8,
                                       hierarchy_CCOMP, 0, Point());
                cout << "countour " << i << " [ne, pr, ch, pa]: "
                     << hierarchy_CCOMP [i] << endl;
        }

        imshow("96 drawing_CCOMP ", drawing_CCOMP);

        //Print out all points of hierachy_TREE's contours
        for (int i=0; i<contours_TREE.size(); i++)
        {	cout << endl;
                cout << "hierarchy_TREE Contour " << i <<endl;
                for (int j=0; j<contours_TREE[i].size(); j++)
                {
                        cout << contours_TREE[i][j] << endl;
                }
        }

        //Print out all points of hierachy_CCOMP's contours
        for (int i=0; i<contours_CCOMP.size(); i++)
        {	cout << endl;
                cout << "hierarchy_CCOMP Contour " << i <<endl;
                for (int j=0; j<contours_CCOMP[i].size(); j++)
                {
                        cout << contours_CCOMP[i][j] << endl;
                }
        }

        Scalar color = Scalar( 0,0,255);

        //Copy contour 0 from hierachy_TREE
        Mat drawing_TREE_processed = Mat::zeros(drawing_TREE.size(), CV_8UC3);
        drawContours( drawing_TREE_processed, contours_CCOMP,
                      0, color, FILLED, 8, hierarchy_CCOMP, 1);
                      //maxLevel=1: nested contour
                      //maxLevel=2: nested-to-nested
        imshow ("124 drawing_TREE_0", drawing_TREE_processed);

        //HL 2018-9-13 Copy the largest contour from hierachy_CCOMP //find largest contour
        int idx = 0, largestComp = 0, smallestComp = 0;
        double maxArea = 0, minArea = 10000;
        for( ; idx >= 0; idx = hierarchy_CCOMP[idx][0] )
        {
        const vector<Point>& c = contours_CCOMP[idx];
        double area = fabs(contourArea(Mat(c)));
        if( area > maxArea )
        {
            maxArea = area;
            largestComp = idx;// find the largest contour??
        }
        }

        Mat drawing_CCOMP_processed = Mat::zeros( frame_binary.size(), CV_8UC3 );
        drawContours( drawing_CCOMP_processed, contours_CCOMP,
                      largestComp, color, FILLED, LINE_8, hierarchy_CCOMP);
        imshow("150 drawing_CCOMP_processed ", drawing_CCOMP_processed);

        //Change color of contour 0 in hierachy_TREE
        /*vector<vector<Point>>contours_TREE_poly(contours_TREE.size());
        vector<Rect>contours_TREE_boundRect(contours_TREE.size());
        approxPolyDP(Mat(contours_TREE[0]), contours_TREE_poly[0], 3, true);
        contours_TREE_boundRect[0] = boundingRect(Mat(contours_TREE_poly[0]));
        rectangle(drawing_TREE, contours_TREE_boundRect[0].tl(),
                  contours_TREE_boundRect[0].br(), color, FILLED, 8, 0 );
        imshow("135 colored contour 0 drawing_TREE ", drawing_TREE);*/
        drawContours( drawing_TREE, contours_TREE,
                      0, color, FILLED, 8, hierarchy_TREE, 1);
        imshow("138 colored contour 0 drawing_TREE ", drawing_TREE);

        waitKey(0);
        return 0;
}
