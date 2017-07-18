/********************************************************************
* Project Name : Road track detection for agv                       *
* Description  : Track the road for navigation                      *
* Author       : Kris Huang                                         *
* Date         : July 06, 2017                                      *
* Notes        : This file is road_with_track.cpp                   *
*                for road with traffic lanes				     	*
* CTI One Corporation, 3679 Enochs Street, Santa Clara, CA 95051    *
*********************************************************************/


#include "road_with_track.h"


#define    sigmaX    2.0
#define    sigmaY    1.0
#define    gaussian_kernel_size    5
#define    img_thresh    200


vector<Vec4i> road_with_track::agv_track_detection(const Mat& img)
{
	// Gaussian blur decreases noise
	Mat img_copy;
	img.copyTo(img_copy);
	Size gaussian_kernel = Size(gaussian_kernel_size, gaussian_kernel_size);
	GaussianBlur(img_copy, img_copy, gaussian_kernel, sigmaX, sigmaY);


	// Convert color to gray scale and hsv scale
	Mat img_gray, img_hsv;
	cvtColor(img_copy, img_gray, CV_BGR2GRAY);
	cvtColor(img_copy, img_hsv, CV_BGR2HSV);


	// Color : Select and yellow pixels and white pixels
	Vec3b thres_yellow_low(20, 100, 100), thres_yellow_high(30, 255, 255);
	uchar thres_white_low = 200, thres_white_high = 255;
	Mat mask_yellow, mask_white, mask_lanes;
	inRange(img_hsv, thres_yellow_low, thres_yellow_high, mask_yellow);
	inRange(img_gray, thres_white_low, thres_white_high, mask_white);
	bitwise_or(mask_yellow, mask_white, mask_lanes);
	Mat img_after_color_mask;
	bitwise_and(img_gray, mask_lanes, img_after_color_mask);


	// Region : Select the lower part region
	Mat mask_region = Mat::zeros(img.rows, img.cols, CV_8UC1);
	Point root_points[1][4];
	root_points[0][0] = Point(0, img.rows - 1);
	root_points[0][1] = Point(img.cols - 1, img.rows - 1);
	root_points[0][3] = Point(img.cols / 9, img.rows * 0.6);
	root_points[0][2] = Point(img.cols - 1 - img.cols / 9, img.rows * 0.6);

	const Point* ppt[1] = { root_points[0] };
	int npt[] = { 4 };
	polylines(mask_region, ppt, npt, 1, 1, Scalar(255));
	fillPoly(mask_region, ppt, npt, 1, Scalar(255));
	Mat img_after_region_mask;
	bitwise_and(img_after_color_mask, mask_region, img_after_region_mask);


	// Threshold the img after mask
	threshold(img_after_region_mask, img_after_region_mask, img_thresh, 255, CV_THRESH_BINARY);
	imshow("img_after_region_mask", img_after_region_mask);
	//waitKey(0);


	// Erode and dilate to remove small pieces
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 1));
	dilate(img_after_region_mask, img_after_region_mask, kernel, Point(-1, -1), 1);
	kernel = getStructuringElement(MORPH_RECT, Size(1, 3));
	dilate(img_after_region_mask, img_after_region_mask, kernel, Point(-1, -1), 1);
	//imshow("erode", img_after_region_mask);
	//waitKey(0);

	/*
	// Find contours
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(img_after_region_mask, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);


	Mat img_all_contours; img.copyTo(img_all_contours);
	Mat img_valid_contours; img.copyTo(img_valid_contours);
	// Analyze contours
	vector<vector<Point>> valid_contours;
	//vector<int> colors = agv_contourColor(img, contours);

	for (unsigned int i = 0; i < contours.size(); i++) {
		// Size
		double area = agv_contourSize(contours[i]);

		// Validate
		drawContours(img_all_contours, contours, i, Scalar(0, 0, 255), 3);
		if (area > 0.0005 * (img.rows * img.cols) && area < 0.015 * (img.rows * img.cols)) {
			valid_contours.push_back(contours[i]);
			drawContours(img_valid_contours, contours, i, Scalar(0, 255, 0), 3);
		}
	}


	//imshow("img_all_contours", img_all_contours);
	//imshow("img_valid_contours", img_valid_contours);
	//waitKey(0);
	*/


	vector<Vec4i> lines;
	Mat img_lines; img.copyTo(img_lines);
	HoughLinesP(img_after_region_mask, lines, 4, CV_PI / 180, 250, 50, 150);
	vector<pair<double, double>> lanes;
	for (size_t i = 0; i < lines.size(); i++)
	{
		// Orientation
		Vec4i l = lines[i];
		float angle = atan2(l[1] - l[3], l[0] - l[2]) * 180 / CV_PI;
		angle = abs(angle);
		if (angle > 20 && angle < 160) {
			float k = (float)(l[1] - l[3]) / (float)(l[0] - l[2]);
			float b = l[1] - k * l[0];
			lanes.push_back(pair<double, double>(k, b));
			int x1 = (img.rows - 1 - b) / k, y1 = img.rows - 1;
			int x2 = (img.rows * 0.65 - b) / k, y2 = img.rows * 0.65;			
			line(img_lines, Point(x1, y1), Point(x2, y2), Scalar(0, 0, 255), 3, CV_AA);
		}
	}


	double k_l = 0, b_l = 0, cnt_l = 0, k_r = 0, b_r = 0, cnt_r = 0;
	for (unsigned int i = 0; i < lanes.size(); i++) {
		if (lanes[i].first < 0) {
			k_l += lanes[i].first;
			b_l += lanes[i].second;
			cnt_l++;
		}
		if (lanes[i].first > 0) {
			k_r += lanes[i].first;
			b_r += lanes[i].second;
			cnt_r++;
		}
	}
	if (cnt_l && cnt_r) {
		k_l = k_l / cnt_l; b_l = b_l / cnt_l;
		k_r = k_r / cnt_r; b_r = b_r / cnt_r;
		Point p1(((img.rows - 1 - b_l) / k_l + (img.rows - 1 - b_r) / k_r) / 2, img.rows - 1);
		Point p2(((img.rows * 0.65 - b_l) / k_l + (img.rows * 0.65 - b_r) / k_r) / 2, img.rows * 0.65);
		vector<Point> pts;
		pts.push_back(p1); pts.push_back(p2);
		track = agv_linear_regression(pts);
	}
	int x1 = (img.rows - 1 - track.second) / track.first, y1 = img.rows - 1;
	int x2 = (img.rows * 0.65 - track.second) / track.first, y2 = img.rows * 0.65;
	line(img_lines, Point(x1, y1), Point(x2, y2), Scalar(0, 255, 0), 3, CV_AA);


	imshow("lines", img_lines);
	waitKey(1);


	return lines;
}

double road_with_track::agv_contourSize(const vector<Point>& contour)
{
	return contourArea(contour);
}

pair<double, double> road_with_track::agv_linear_regression(const vector<Point>& points)
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
