#pragma once
#include "CamCapture.h"
#include<stdio.h>
#include<math.h>
#include<opencv\cv.h>
#include<opencv\highgui.h>
#include<opencv2\objdetect\objdetect.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<vector>

using namespace cv;
using namespace std;

#define MAXFACES 1


class FaceDetection
{
public:
	FaceDetection(string fileName, CamCapture* capture);
	~FaceDetection();

	int Initialize();
	void Detect();
	Point& returnFacePoint();

private:
	
	void DetectFaces();

	/* XML File Name to detect Faces */
	string m_fileName;
	CamCapture* m_capture;

	Point pt1;
	Mat cap_img, gray_img;
	std::vector<Rect> faces, eyes;
	CascadeClassifier face_cascade, eye_cascade;
};
