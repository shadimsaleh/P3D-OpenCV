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

class CamCapture;

#define  DEBUG 0

class OpticalFlow
{
private:
	CamCapture *capture = nullptr;
	IplImage *frame = nullptr; // frame
	IplImage *grayA = nullptr; // gray
	IplImage *grayB = nullptr; // prevgray
	IplImage *velx = nullptr;
	IplImage *vely = nullptr;

public:
	OpticalFlow(CamCapture* cam);
	glm::vec3 GetFlow();
	void Release();
};

inline OpticalFlow::OpticalFlow(CamCapture* cam)
{
	capture = cam;
}

inline glm::vec3 OpticalFlow::GetFlow()
{
	this->frame = capture->GetFrame();

	if (!frame) return glm::vec3(0,0,0);

	if (!grayA) grayA = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 1);
	if (!grayB) grayB = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 1);
	if (!velx) velx = cvCreateImage(cvGetSize(frame), IPL_DEPTH_32F, 1);
	if (!vely) vely = cvCreateImage(cvGetSize(frame), IPL_DEPTH_32F, 1);
	cvCvtColor(frame, grayA, CV_BGR2GRAY);

	CvTermCriteria IterCriteria;
	IterCriteria.type = CV_TERMCRIT_ITER;
	IterCriteria.max_iter = 5;

	//this
	//cvCalcOpticalFlowHS(grayB, grayA, 1, velx, vely, 0.1, IterCriteria);

	for (int i = 0; i<frame->height; i += 5)
	{
		for (int j = 0; j<frame->width; j += 5)
		{
			int dx = (int)cvGetReal2D(velx, i, j);
			int dy = (int)cvGetReal2D(vely, i, j);
#if DEBUG 1
			cvLine(frame, cvPoint(j, i), cvPoint(j + dx, i + dy), CV_RGB(255, 255, 255), 1, 8, 0);
#endif

		}
	}



	cvCopy(grayA, grayB);

	return {};
}

inline void OpticalFlow::Release()
{
	if (!frame) cvReleaseImage(&frame);
	if (!grayA) cvReleaseImage(&grayA);
	if (!grayB) cvReleaseImage(&grayB);
	if (!velx) cvReleaseImage(&velx);
	if (!vely) cvReleaseImage(&vely);
}
