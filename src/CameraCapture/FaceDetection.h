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
	FaceDetection(char* fileName, CamCapture* capture);
	~FaceDetection();

	int Initialize();
	void Detect();

private:

	void DetectFaces();

	static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';');

	/* XML File Name to detect Faces */
	char* m_fileName;
	CamCapture* m_capture;
	
	Mat cap_img, gray_img;
	vector<Rect> faces, eyes;
	CascadeClassifier face_cascade, eye_cascade;
};
