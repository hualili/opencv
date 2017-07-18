/********************************************************************
* Project Name : Road track detection for agv                       *
* Description  : Track the road for navigation                      *
* Author       : Kris Huang                                         *
* Date         : July 06, 2017                                      *
* Notes        : This file is the main.cpp     				     	*
*********************************************************************/


#include "road_without_track.h"

int main() {
	while (1) {
		//Mat img = imread("road5.jpg");
		int mode = 0;
		cout << "Input 1 for road with track, 2 for road without track, 3 for quit : " << endl;
		cin >> mode;
		cout << endl;
		if (mode == 1) {
			string video_name = "";
			cout << "Name of Video : " << endl;
			cin >> video_name;
			VideoCapture cam(video_name);
			road_with_track* test = new road_with_track;
			Mat frame;
			while (1) {
				cam >> frame;
				if (frame.empty()) break;
				test->agv_track_detection(frame);
			}
		}
		if (mode == 2) {
			string video_name = "";
			cout << "Name of Video : " << endl;
			cin >> video_name;
			video_name = "ENOCHS_Videos//" + video_name;
			VideoCapture cam(video_name);
			road_without_track* test = new road_without_track;
			Mat frame;
			while (1) {
				cam >> frame;

				//transpose(frame, frame);
				//flip(frame, frame, 1);
				if (frame.empty()) break;
				test->agv_track_detection(frame);
			}
		}
		if (mode == 3) break;
		cout << endl;
	}
	return 0;
}