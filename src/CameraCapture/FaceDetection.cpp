#include "FaceDetection.h"
FaceDetection::FaceDetection(char* fileName, CamCapture* capture)
{
	this->m_fileName = fileName;
	this->m_capture = capture;
}

FaceDetection::~FaceDetection()
{

}

int FaceDetection::Initialize()
{
	if (!face_cascade.load("c:\\haar\\haarcascade_frontalface_alt2.xml")) {
		printf("Error loading cascade file for face");
		return 0;
	}
	if (!eye_cascade.load("c:\\haar\\haarcascade_eye.xml")) {
		printf("Error loading cascade file for eye");
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
	face_cascade.detectMultiScale(gray_img, faces, 1.1, 10, 
		CV_HAAR_SCALE_IMAGE | CV_HAAR_DO_CANNY_PRUNING, cvSize(0, 0), cvSize(300, 300));
	for (int i = 0; i < faces.size(); i++)
	{
		Point pt1(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
		Point pt2(faces[i].x, faces[i].y);
		Mat faceROI = gray_img(faces[i]);
		eye_cascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));
		for (size_t j = 0; j< eyes.size(); j++)
		{
			//Point center(faces[i].x+eyes[j].x+eyes[j].width*0.5, faces[i].y+eyes[j].y+eyes[j].height*0.5);
			Point center(faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5);
			int radius = cvRound((eyes[j].width + eyes[j].height)*0.25);
			circle(cap_img, center, radius, Scalar(255, 0, 0), 2, 8, 0);
		}
		rectangle(cap_img, pt1, pt2, cvScalar(0, 255, 0), 2, 8, 0);
	}
	imshow("Result", cap_img);
}
