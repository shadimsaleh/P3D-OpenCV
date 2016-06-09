#pragma once
#include <opencv/cv.h>
#include "CamCapture.h"

#define DEBUG 1
#define MAX_COUNT 500

class OpticalFlow
{
private:
	CamCapture *capture = nullptr;
	cv::Mat frame;
	cv::Mat image_prev_Gray;
	cv::Mat image_next_Gray;
	cv::Mat rgbFrames;
	cv::Mat opticalFlow;

	std::vector<cv::Point2f> points1;
	std::vector<cv::Point2f> points2;

	cv::Point2f diff;

	std::vector<uchar> status;
	std::vector<float> err;

	cv::TermCriteria termcrit;
	cv::Size subPixWinSize;
	cv::Size winSize;

	bool needToInitialize = true;

	int k = 0;
	int interval;

public:
	OpticalFlow(CamCapture* cam, int interval);
	void GetFlow();
	void Release();
};