/********************************************************************
* Project Name : Road track detection for agv                       *
* Description  : Track the road for navigation                      *
* Author       : Kris Huang                                         *
* Revision     : KH and HL, version 2.0;                            *
* Date         : July 07, 2017                                      *
* Notes        : This file is road_without_track.cpp                *
*                for road without traffic lanes		                *
* Caution (HL and KH, July 7th, 17) :                               *
* This program currently does not work for the the heavy shadows    *
* casted by the sunshine, see the testing image and video;          *
* image xxxx2650.jpg and ENOCHS_110.MOV                             *
* To solve this problem:                                            *
*  1. add stereo vision depth map; and                              *
*  2. Lidar depth map;                                              *
*     if the input from vision is an obstacle                       *
*        && input from the stereo is far away and/or same as the    *
*           neighbouring path region                                *
*     then the "obstacle" is ignored;                               *
*        && the path is calculated based on partial video info and  *
*           stereo vision                                           *
* CTI One Corporation, 3679 Enochs Street, Santa Clara, CA 95051    *
* Note:                                                             *
*  processing principles:                                           *
*  1. PROXIMITY;                                                    *
*  2. Good continuation;                                            *
*  3. Symmetry;                                                     *
*  4. Similarity;                                                   *
*  5. Closure;                                                      *
*  6. Simplicity;                                                   *
*********************************************************************/


#include "road_without_track.h"

#define    sigmaX    1.0          //Gaussian kernel 
#define    sigmaY    1.0
#define    gaussian_kernel_size    5
#define    img_resize_ratio        0.25 //0.5, or 0.25, or 0.125 
#define    img_thresh    100


void road_without_track::agv_track_detection(Mat &img)
{
	// preprocessing 
	// Resize the image -- preprocessing stage 1 
	resize(img, img, Size(img.cols * img_resize_ratio, img.rows * img_resize_ratio), 0, 0, INTER_LINEAR);


	// Gaussian blur decreases noise -- preprocessing stage 2 
	Mat img_copy;
	img.copyTo(img_copy);
	Size gaussian_kernel = Size(gaussian_kernel_size, gaussian_kernel_size);
	GaussianBlur(img_copy, img_copy, gaussian_kernel, sigmaX, sigmaY);


	// Binarization of grey scale -- preprocessing stage 3 
	Mat img_gray;
	cvtColor(img_copy, img_gray, CV_BGR2GRAY);
	threshold(img_gray, img_gray, img_thresh, 255, CV_THRESH_OTSU);


	/*
	// Convert color to gray scale and hsv scale
	Mat img_gray, img_hsv;
	cvtColor(img_copy, img_gray, CV_BGR2GRAY);
	cvtColor(img_copy, img_hsv, CV_BGR2HSV);


	// Select and yelloe pixels and white pixels
	Vec3b thres_yellow_low(20, 100, 100), thres_yellow_high(30, 255, 255);
	uchar thres_white_low = 200, thres_white_high = 255;
	Mat mask_yellow, mask_white, mask_lanes;
	inRange(img_hsv, thres_yellow_low, thres_yellow_high, mask_yellow);
	inRange(img_gray, thres_white_low, thres_white_high, mask_white);
	bitwise_or(mask_yellow, mask_white, mask_lanes);


	// Threshold the img after mask
	Mat img_after_color_mask;
	bitwise_and(img_gray, mask_lanes, img_after_color_mask);
	threshold(img_after_color_mask, img_after_color_mask, 0, 255, CV_THRESH_OTSU);


	imshow("img", img_after_color_mask);
	waitKey(0);
	*/

	/*
	// Region : Select the lower part region
	Mat mask_region = Mat::zeros(img.rows, img.cols, CV_8UC1);
	Point root_points[1][4];
	root_points[0][0] = Point(0, img.rows - 1);
	root_points[0][1] = Point(img.cols - 1, img.rows - 1);
	root_points[0][3] = Point(img.cols / 9, img.rows * 0.4);
	root_points[0][2] = Point(img.cols - 1 - img.cols / 9, img.rows * 0.4);

	const Point* ppt[1] = { root_points[0] };
	int npt[] = { 4 };
	polylines(mask_region, ppt, npt, 1, 1, Scalar(255));
	fillPoly(mask_region, ppt, npt, 1, Scalar(255));
	Mat img_after_region_mask;
	bitwise_and(img_gray, mask_region, img_after_region_mask);

	imshow("img", img_after_region_mask);
	waitKey(0);
	*/


	// Image morphology processing -- preprocessing stage 4 
	Mat img_erode, img_dilate;
	erode(img_gray, img_erode, Mat(), Point(2, 2), 7);     // removal of smaller binarized regions  
	dilate(img_gray, img_dilate, Mat(), Point(2, 2), 7);   // connecting regions 
	threshold(img_dilate, img_dilate, 1, 50, THRESH_BINARY_INV); // ??? change 0 to 50 by offset 

	Mat path_trace(img_gray.size(), CV_8U, Scalar(0));
	path_trace = img_erode + img_dilate;   // = img_dilate; 

	findroad road;
	road.setpath(path_trace);

	// rule 4: similarity (color) 
	//      1: proximity (region???) 
	Mat road_found = road.getroad(img);
	road_found.convertTo(road_found, CV_8U); // water shade algorithm, result back to road_found 


	vector<Point> points = agv_find_border_point(road_found); //find the buttom points 


	// Divide into left part points and right part points
	// and remove outliers based on rule 2 : good continuous
	vector<Point> left_points(points.begin(), points.begin() + 9);
	agv_reject_outliers(left_points);
	vector<Point> right_points(points.begin() + 9, points.end());
	agv_reject_outliers(right_points);
	for (unsigned int i = 0; i < left_points.size(); i++) circle(img, left_points[i], 4, Scalar(0, 0, 255), 3);
	for (unsigned int i = 0; i < right_points.size(); i++) circle(img, right_points[i], 4, Scalar(0, 0, 255), 3);


	// rule 3: symmetry for left and right
	// rule 6: simplicity for regression 
	for (unsigned int i = 0; i < right_points.size(); i++) right_points[i].x = img.cols - 1 - right_points[i].x;
	//pair<double, double> left_bottom_line = agv_linear_regression(left_points);
	//pair<double, double> right_bottom_line = agv_linear_regression(right_points);
	vector<double> left_curve = agv_quadratic_regression(left_points);
	vector<double> right_curve = agv_quadratic_regression(right_points);
	vector<Point2f> left_curve_points, right_curve_points;
	vector<Point> central_points;
	for (int i = 0; i < img.cols * 0.35; i++) {
		left_curve_points.push_back(Point(i, left_curve[0] + left_curve[1] * i + left_curve[2] * i * i));
		right_curve_points.push_back(Point(img.cols - 1 - i, right_curve[0] + right_curve[1] * i + right_curve[2] * i * i));
	}


	int y_i = max(left_curve_points[(int)left_curve_points.size() - 1].y, right_curve_points[(int)right_curve_points.size() - 1].y);
	int y_r = min(left_curve_points[0].y, right_curve_points[0].y);
	int y_m = (y_i + y_r) / 2;
	int x_i_l = -1, x_m_l = -1, x_r_l = -1;
	for (unsigned int i = 0; i < left_curve_points.size(); i++) {
		if (left_curve_points[i].y == y_i) x_i_l = left_curve_points[i].x;
		if (left_curve_points[i].y == y_m) x_m_l = left_curve_points[i].x;
		if (left_curve_points[i].y == y_r) x_r_l = left_curve_points[i].x;
	}
	int x_i_r = -1, x_m_r = -1, x_r_r = -1;
	for (unsigned int i = 0; i < right_curve_points.size(); i++) {
		if (right_curve_points[i].y == y_i) x_i_r = right_curve_points[i].x;
		if (right_curve_points[i].y == y_m) x_m_r = right_curve_points[i].x;
		if (right_curve_points[i].y == y_r) x_r_r = right_curve_points[i].x;
	}

	vector<Point> central_curve_points;
	if (x_i_l == -1 || x_i_r == -1 || x_r_l == -1 || x_r_r == -1) {
		for (int i = img.rows - 1; i >= y_i; i--) {
			central_curve_points.push_back(Point(img.cols / 2, i));
		}
	}
	else {
		vector<Point> central_points;
		central_points.push_back(Point((x_i_l + x_i_r) / 2, y_i));
		central_points.push_back(Point((x_m_l + x_m_r) / 2, y_m));
		central_points.push_back(Point((x_r_l + x_r_r) / 2, y_r));
		circle(img, central_points[0], 3, Scalar(0, 255, 0), 3);
		circle(img, central_points[1], 3, Scalar(0, 255, 0), 3);
		circle(img, central_points[2], 3, Scalar(0, 255, 0), 3);
		
		/*
		// Fit a quadratic line
		int compensation = central_points[1].x;
		central_points[0].x -= compensation;
		central_points[1].x -= compensation;
		central_points[2].x -= compensation;
		vector<double> central_curve = agv_quadratic_regression(central_points);
		for (int i = (x_m_l + x_m_r) / 2; i < img.cols; i++) {
			if ((central_curve[0] + central_curve[1] * (i - compensation) + central_curve[2] * (i - compensation) * (i - compensation)) >= img.rows || (central_curve[0] + central_curve[1] * (i - compensation) + central_curve[2] * (i - compensation) * (i - compensation)) < y_i) break;
			central_curve_points.push_back(Point(i, central_curve[0] + central_curve[1] * (i - compensation) + central_curve[2] * (i - compensation) * (i - compensation)));
		}
		for (int i = (x_m_l + x_m_r) / 2 - 1; i >= 0; i--) {
			if ((central_curve[0] + central_curve[1] * (i - compensation) + central_curve[2] * (i - compensation) * (i - compensation)) >= img.rows || (central_curve[0] + central_curve[1] * (i - compensation) + central_curve[2] * (i - compensation) * (i - compensation)) < y_i) break;
			central_curve_points.insert(central_curve_points.begin(), Point(i, central_curve[0] + central_curve[1] * (i - compensation) + central_curve[2] * (i - compensation) * (i - compensation)));
		}
		*/
		
		
		
		
		// Fit a linear line
		pair<double, double> central_line = agv_linear_regression(central_points);
		if ((track.first == 0 && track.second == 0) || (abs(central_line.first) >= 0.1)) {
			track = central_line;
		}
		for (int i = (x_m_l + x_m_r) / 2;i < img.cols; i++) {
			if ((track.first * i + track.second) >= img.rows || (track.first * i + track.second) < y_i) break;
			central_curve_points.push_back(Point(i, track.first * i + track.second));
		}
		for (int i = (x_m_l + x_m_r) / 2 - 1;i >= 0; i--) {
			if ((track.first * i + track.second) >= img.rows || (track.first * i + track.second) < y_i) break;
			central_curve_points.insert(central_curve_points.begin(), Point(i, track.first * i + track.second));
		}
		
	}


	/*
	line(img, Point(0, left_bottom_line.second), Point(img.cols / 2,
		left_bottom_line.first * img.cols / 2 + left_bottom_line.second),
		Scalar(0, 255, 0), 2);  // linear interpolation, but quadratic is better; change to quadratic fitting 
	line(img, Point(img.cols / 2, right_bottom_line.first * img.cols / 2
		+ right_bottom_line.second), Point(img.cols - 1, right_bottom_line.first * (img.cols - 1)
			+ right_bottom_line.second), Scalar(0, 255, 0), 2); // for the right side of the image, same 2nd order needed 
	*/
	Mat curve_left(left_curve_points, true);
	curve_left.convertTo(curve_left, CV_32S);
	Mat curve_right(right_curve_points, true);
	curve_right.convertTo(curve_right, CV_32S);
	Mat curve_central(central_curve_points, true);
	curve_central.convertTo(curve_central, CV_32S);
	polylines(img, curve_left, false, Scalar(0, 255, 0), 2);
	polylines(img, curve_right, false, Scalar(0, 255, 0), 2);
	polylines(img, curve_central, false, Scalar(255, 0, 0), 2);


	// rule 5: closure -- no need for that

	imshow("road", road_found);
	imshow("points", img);
	waitKey(1);
}


double road_without_track::agv_contourSize(const vector<Point>& contour)
{
	return contourArea(contour);
}


vector<Point> road_without_track::agv_find_border_point(const Mat & road)
{
	const int step_width = road.cols * 0.04;
	vector<Point> points;
	for (unsigned int i = 0; i < 10 * step_width; i += step_width) {
		for (unsigned int j = road.rows - 1; j > 0; j--) {
			int pixel = road.at<uchar>(j, i);
			if (pixel > 0 && pixel < 255) {
				points.push_back(Point(i, j)); break;
			}
		}
	}


	for (unsigned int i = road.cols - 1; i > road.cols - 1 - 10 * step_width; i -= step_width) {
		for (unsigned int j = road.rows - 1; j > 0; j--) {
			int pixel = road.at<uchar>(j, i);
			if (pixel > 0 && pixel < 255)
			{
				points.push_back(Point(i, j)); break;
			}
		}
	}

	return points;
}


pair<double, double> road_without_track::agv_linear_regression(const vector<Point>& points)
{
	double avg_x = 0., avg_y = 0.;
	const int size = (int)points.size();
	for (unsigned int i = 0; i < size; i++) {
		avg_x += points[i].x;
		avg_y += points[i].y;
	}
	avg_x = avg_x / size; avg_y = avg_y / size;
	double k1 = 0, k2 = 0;
	for (unsigned int i = 0; i < size; i++) {
		k1 += (points[i].x - avg_x) * (points[i].y - avg_y);
		k2 += (points[i].x - avg_x) * (points[i].x - avg_x);
	}
	double k = k1 / k2; double b = avg_y - k * avg_x;
	return pair<double, double>(k, b);
}


vector<double> road_without_track::agv_quadratic_regression(const vector<Point>& points)
{
	// Fit a quadratic function based a set of points with least-square method
	const int n = (int)points.size();
	double x_i = 0, x_i2 = 0, x_i3 = 0, x_i4 = 0;
	double y_i = 0, x_i_y_i = 0, x_i2_y_i = 0;
	for (unsigned int i = 0; i < points.size(); i++) {
		x_i += points[i].x;
		x_i2 += points[i].x * points[i].x;
		x_i3 += points[i].x * points[i].x * points[i].x;
		x_i4 += points[i].x * points[i].x * points[i].x * points[i].x;
		y_i += points[i].y;
		x_i_y_i += points[i].x * points[i].y;
		x_i2_y_i += points[i].x * points[i].x * points[i].y;
	}
	Mat A(3, 3, CV_64F);
	A.at<double>(0, 0) = n; A.at<double>(0, 1) = x_i; A.at<double>(0, 2) = x_i2;
	A.at<double>(1, 0) = x_i; A.at<double>(1, 1) = x_i2; A.at<double>(1, 2) = x_i3;
	A.at<double>(2, 0) = x_i2; A.at<double>(2, 1) = x_i3; A.at<double>(2, 2) = x_i4;
	Mat b(3, 1, CV_64F);
	b.at<double>(0, 0) = y_i; b.at<double>(1, 0) = x_i_y_i; b.at<double>(2, 0) = x_i2_y_i;

	Mat A_inverse;
	invert(A, A_inverse);
	Mat x = A_inverse * b;
	vector<double> res(3, 0.);
	res[0] = x.at<double>(0, 0); res[1] = x.at<double>(1, 0); res[2] = x.at<double>(2, 0);

	return res;
}


void road_without_track::agv_reject_outliers(vector<Point>& points)
{
	for (unsigned int i = 1; (i + 1) < points.size(); i++) {
		if ((points[i].y > points[i - 1].y && points[i].y > points[i + 1].y) || (points[i].y < points[i - 1].y && points[i].y < points[i + 1].y)) {
			points.erase(points.begin() + i);
			i--;
		}
	}
}


void findroad::setpath(Mat & image)
{
	image.convertTo(path, CV_32S);
}


Mat findroad::getroad(Mat & image)
{
	watershed(image, path);
	path.convertTo(path, CV_8U);
	return path;
}
