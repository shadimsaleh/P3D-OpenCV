#pragma once
#include <Components\Mesh.h>
#include <Components\Transform.h>
#include <GL/glew.h>
#include <opencv/cv.h>
#include <opencv/cxcore.hpp>
#include <opencv/highgui.h>
#include <Debug/Console.h>
#include <Debug/Debug.h>
#include "CamCapture.h"
#include <opencv/cvwimage.h>

#include <iostream>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

class CamCapture;

#define  DEBUG 0

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
	CvPoint2D32f* corners;

	int * MAX_COUNT;

	char* status;
	float* err;

	cv::TermCriteria termcrit;
	cv::Size subPixWinSize;
	cv::Size winSize;

	bool needToInitialize = true;

public:
	OpticalFlow(CamCapture* cam);
	glm::vec3 GetFlow();
	void Release();
};

inline OpticalFlow::OpticalFlow(CamCapture* cam)
{
	corners = new CvPoint2D32f(4, 4);
	MAX_COUNT = new int(500);
	capture = cam;

	opticalFlow = cv::Mat(capture->GetFrameHeight(), capture->GetFrameWidth(), CV_32FC3);

	termcrit = CvTermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03);
	subPixWinSize = CvSize(10, 10);
	winSize = CvSize(31, 31);
}

inline glm::vec3 OpticalFlow::GetFlow()
{
	this->frame = capture->GetFrame().getMatRef();
	frame.copyTo(rgbFrames);
	cvCvtColor(&rgbFrames, &image_next_Gray, CV_BGR2GRAY);

	if(needToInitialize) {
		cvGoodFeaturesToTrack(&image_next_Gray, &points1, &image_next_Gray, corners, MAX_COUNT , 0.1, 5, &cv::Mat(), 3, 0, 0.04);
		needToInitialize = false;
	}
	else if(!points2.empty())
	{
		Print("Calculating  calcOpticalFlowPyrLK", true);
		cvCalcOpticalFlowPyrLK(&image_prev_Gray, &image_next_Gray, &points2, &points1, 
			3,winSize, 0.0001, status, err, termcrit, 0);

	}
}

inline void OpticalFlow::Release()
{
	frame.release();
	image_prev_Gray.release();
	image_next_Gray.release();
	rgbFrames.release();
	opticalFlow.release();
}
