#pragma once
#include "CamCapture.h"
#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>

using namespace cv;

#define MAXFACES 1

class FaceDetection
{
public:
	FaceDetection(char* fileName, CamCapture* capture);
	~FaceDetection();

	void Initialize();
	void Detect();

private:

	void DetectFaces();

	void SetupMemory();
	CvMemStorage* m_storage;

	CvHaarClassifierCascade* m_cascade_f[1];

	/* XML File Name to detect Faces */
	char* m_fileName;
	CamCapture* m_capture;
	
	IplImage* m_frame;
	IplImage *imgfaces[MAXFACES];
};
