#include "CamCapture.h"

CamCapture::CamCapture()
	: p_capWebCam(nullptr), Width(0), Height(0)
{ }

CamCapture::~CamCapture()
{ }

int CamCapture::Initialize()
{
	p_capWebCam = new cv::VideoCapture(0);

	if(!p_capWebCam->isOpened()){
		return 0; //Returns 0 cannot Continue
	}
	return 1; //Success
}

cv::Mat CamCapture::GetFrame_Mat() const
{
	cv::Mat frame;
	if(p_capWebCam->retrieve(frame, CV_LOAD_IMAGE_COLOR)) {
		return frame;
	}
	return {};
}

IplImage* CamCapture::GetFrame_IplImage() const
{
	cv::Mat frame;
	IplImage* image;
	if(p_capWebCam->read(frame)){
		image = cvCreateImage(cvSize(frame.cols, frame.rows), 8, 1);
		return image;
	}
	return {};
}

void CamCapture::EndCapture() const
{
	p_capWebCam->release();
}

