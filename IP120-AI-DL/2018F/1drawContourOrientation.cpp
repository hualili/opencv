/*-------------------------------------------------------*
 * Program: findContour.cpp;  CTI One Corp. HL           *
 * Date:    Sept. 2018;                                  *
 * Purpose: Demo contour computations                    *
 * Another related program: createImage.cpp for          *
 *         the purpose of creating test pattern          * 
 *         image to verify the contour computation.      *
 * Note: (1) this program reads input image and finds    * 
 *       contours;                                       * 
 *       (2) then it computes angle of each              * 
 *       contour segment and its magnitude based         * 
 *       Harry Li's definition, however this program     * 
 *       implementation for angle and magnitude          * 
 *       computation is unverified, YOU WILL NEED TO     * 
 *       VERIFY THIS CODE FOR THAT COMPUTATION.          * 
 *       (3) Compilation & build, you will have to use   * 
 *       C++ 11 compiler to handle stof( )               * 
 *       string to float function, just add 1st line     *
 *       to Cmakelists.txt as follows:                   * 
 *                                                     　　*
 *  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") *
 *-------------------------------------------------------*/ 

#include <iostream>
#include <fstream>
#include <string>

#include <unistd.h> //usleep( )
#include <math.h>   //sin( )
#include "opencv2/opencv_modules.hpp" 
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"
#define PI (atan(1)*4)

using namespace std;
using namespace cv;

RNG rng(12345);
template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}
std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

void draw_orientation(float alpha_in, Size s)
{
      Mat frame_background(s.height, s.width, CV_8UC3, 
		Scalar(255, 255, 255));//creat a frame with black background
      //float alpha_in;
      string line;
      Point pre_P, P, nex_P;
      float alpha, distance;
         
      /*********Load contours atribute from a data file*******/
      ifstream infile("contours_data.txt", ifstream::in);
      if(!infile.good()) {
        cout << "Error to read config file\n";
      }
      while(getline(infile, line, '\n')) {	
	string sStr = line.substr(line.find_first_of('[')+1, line.find_first_of(']')-1);	
	vector<string> vStr = split(sStr, ','); 
	pre_P=P; //get previous point
        try {	 
	    P.x = std::stof(vStr.at(0));
	    P.y = std::stof(vStr.at(1));
	    alpha = std::stof(vStr.at(2));
	    distance = std::stof(vStr.at(3));
        } catch (const std::exception& e) {
            cout << "Error in read config file, check config file content format\n";
            infile.close();
        }
	nex_P.x = P.x + roundf(distance * cos(alpha*PI/180));//get next point,
	nex_P.y = P.y + roundf(distance * sin(alpha*PI/180));
	if (alpha >= alpha_in-0.01 && alpha <= alpha_in+0.01 ){
	    cout << "Pre, Cur, Nex Points has angle= "<< alpha_in << ": " <<
		     pre_P << " " << P << " " << nex_P << endl;
	}	
	arrowedLine(frame_background, P, nex_P, Scalar(0,0,255), 1, 8); 
    }
    infile.close();
    namedWindow( "79 contour_orientation", WINDOW_NORMAL ); 
    imshow( "79 contour_orientation", frame_background);
    imwrite( "CHAIN_APPROX_NONE.jpg", frame_background );
}

int main( int, char** argv )
{ 
  	Mat frame, frame_gray, frame_blur;
	Mat frame_down, frame_tmp, frame_canny;
	float alpha_in;
	frame = imread( argv[1], IMREAD_COLOR);

	if (!frame.data)
	{ 
	printf("No image data \n");
	return -1;
	}

      	cout << "Please enter alpha angle (Ex: 45, -45,..) : ";
      	cin >> alpha_in;    
      	cout << endl;
	
        frame_tmp = frame;  
	
	namedWindow("101 Display Image", WINDOW_AUTOSIZE);
	imshow("101 Display Image", frame);
  
	GaussianBlur( frame_tmp, frame_blur, Size( 5, 5 ), 20.0, 20.0 );
  
	Mat frame_binary, frame_blur_gray; 
	cvtColor(frame_blur, frame_blur_gray, cv::COLOR_BGR2GRAY); 
       
    	cv::Scalar mean,stddev; //0:1st channel, 1:2nd channel and 2:3rd channel
   	meanStdDev(frame_blur_gray,mean,stddev,cv::Mat());
 
  	threshold( frame_blur_gray, frame_binary, mean.val[0] - 0.5*stddev.val[0], 255, 0 );

	vector<vector<Point> > contours_CCOMP ;
	vector<Vec4i> hierarchy_TREE, hierarchy_CCOMP;
	vector<vector<Vec4f> > newcontours;
	
	findContours( frame_binary, contours_CCOMP, hierarchy_CCOMP, 
                  RETR_CCOMP, CHAIN_APPROX_NONE, Point(0, 0) );

	Mat drawing_CCOMP = Mat::zeros( frame_binary.size(), CV_8UC3 );

	/*****orientation****/
  	for( int i = 0; i< contours_CCOMP.size(); i++ ) {
       	 Scalar color = Scalar( rng.uniform(200, 255), 
                                rng.uniform(200,255), rng.uniform(200,255) );
       	 drawContours( drawing_CCOMP, contours_CCOMP, i, color, 2, 8, 
                                hierarchy_CCOMP, 0, Point());
	 cout << "countour " << i << " [ne, pr, ch, pa]: "
		     << hierarchy_CCOMP [i] << endl;
     	}

	imshow("134 drawing_CCOMP ", drawing_CCOMP);

	//Print out all points of hierachy_CCOMP's contours
	vector<Vec4f> vector_tmp;
	for (int i=0; i<contours_CCOMP.size(); i++) {
    	 cout << "hierarchy_CCOMP Contour has point" << i <<endl;
	 for (int j=1; j<contours_CCOMP[i].size(); j++) {	
          float alpha, distance, alpha_degree;
	  cout << contours_CCOMP[i][j] << endl;			
	  if((contours_CCOMP[i][j].x - contours_CCOMP[i][j-1].x)!=0) {			
	    alpha = atan ((contours_CCOMP[i][j].y - contours_CCOMP[i][j-1].y)/
			 (contours_CCOMP[i][j].x - contours_CCOMP[i][j-1].x));
	    } 
          else {
	   alpha = PI/2;
	   }
	  distance = sqrt (pow((contours_CCOMP[i][j].x - 
			   contours_CCOMP[i][j-1].x),2) +
			   pow((contours_CCOMP[i][j].y - 
			   contours_CCOMP[i][j-1].y),2));
			   alpha_degree = alpha*180/PI;
	  vector_tmp.push_back(Vec4f(contours_CCOMP[i][j-1].x, 
			   contours_CCOMP[i][j-1].y, 
			   alpha_degree, distance));
	  } //inner for-loop 
	  newcontours.push_back(vector_tmp);
	}   //outer for-loop 
		
	std:: ofstream output_file("./contours_data.txt");
	for(size_t i=0; i<newcontours.size(); i++) {
	  cout << "contour " << " " << i <<":" <<endl;
	  for(size_t j=1; j<newcontours[i].size(); j++){
	    cout << newcontours[i][j] <<endl;
	    if(output_file.is_open()){
	    output_file <<newcontours[i][j]<<endl;
	    } 
	    else {
	      cout << "Error in opening file! \n";
		}
	 } //inner for-loop  
	}  //outer for-loop 

	output_file.close();
	Size s = frame.size();
	draw_orientation(alpha_in, s);
	
	waitKey(0);
	return 0;
}


