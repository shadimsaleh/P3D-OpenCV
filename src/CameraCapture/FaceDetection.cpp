#include "FaceDetection.h"
FaceDetection::FaceDetection(string fileName, CamCapture* capture)
{
	this->m_fileName = fileName;
	this->m_capture = capture;
}

FaceDetection::~FaceDetection()
{

}

int FaceDetection::Initialize()
{
	if (!face_cascade.load("./src/CameraCapture/haarcascade_frontalface_alt.xml")) {
		printf("Error loading cascade file for face");
		return 0;
	}
	return 1;
}

void FaceDetection::Detect()
{
	cap_img = m_capture->GetFrame_Mat();
	cvtColor(cap_img, gray_img, CV_BGR2GRAY);
	cv::equalizeHist(gray_img, gray_img);

	DetectFaces();
}

void FaceDetection::DetectFaces()
{
	face_cascade.detectMultiScale(gray_img, faces, 1.1, 1, 
		CV_HAAR_SCALE_IMAGE | CV_HAAR_DO_CANNY_PRUNING, cvSize(0, 0), cvSize(300, 300));
	for (int i = 0; i < MAXFACES; i++)
	{
		if (faces[i].x + faces[i].width > this->m_capture->GetFrameWidth() ||
			faces[i].y + faces[i].height > this->m_capture->GetFrameHeight() || 
			faces[i].area() < 100) continue;
		Point pt1(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
		Point pt2(faces[i].x, faces[i].y);
		rectangle(cap_img, pt1, pt2, cvScalar(0, 255, 0), 2, 8, 0);
	}
	imshow("Result", cap_img);
}
