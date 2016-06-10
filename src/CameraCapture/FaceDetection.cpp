#include "FaceDetection.h"

Point pt1;
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
	if (!face_cascade.load("./src/CameraCapture/haarcascade_frontalface_default.xml")) {
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
	//with great processors comes greater performance (change 3rd parameter from 2 to 1.05 or 1.1)
	face_cascade.detectMultiScale(gray_img, faces, 1.3, 1, 
		0 | CV_HAAR_SCALE_IMAGE ,cvSize(60, 60));
	for (int i = 0; i < MAXFACES; i++)
	{
		if (faces[i].x + faces[i].width > this->m_capture->GetFrameWidth() ||
			faces[i].y + faces[i].height > this->m_capture->GetFrameHeight() || 
			faces[i].area() < 100) continue;
		pt1.x = faces[i].x + faces[i].width*0.5f;
		pt1.y = faces[i].y + faces[i].height*0.5f;
		
		ellipse(cap_img, pt1, Size(faces[i].width*0.5, faces[i].height*0.5),0,0,360,Scalar(255,0,0),4, 8, 0);
	}
	imshow("Result", cap_img);
}

Point& FaceDetection::returnFacePoint()
{
	return pt1;
}
