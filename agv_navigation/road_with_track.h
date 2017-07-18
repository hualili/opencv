/********************************************************************
* Project Name : Road track detection for agv                       *
* Description  : Track the road for navigation                      *
* Author       : Kris Huang                                         *
* Date         : July 06, 2017                                      *
* Notes        : This file is road_with_track.h                     *
*                for road with traffic lanes				     	*
* CTI One Corporation, 3679 Enochs Street, Santa Clara, CA 95051    *
*********************************************************************/


#pragma once
#ifndef ROAD_WITH_TRACK_H
#define ROAD_WITH_TRACK_H


#include "agv_navigation.h"

class road_with_track {
private:
	pair<double, double> track;
public:
	road_with_track() { track = pair<double, double>(0, 0); }
	vector<Vec4i> agv_track_detection(const Mat&);
	double agv_contourSize(const vector<Point>&);
	pair<double, double> agv_linear_regression(const vector<Point>&);
};


#endif