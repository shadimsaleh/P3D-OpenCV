#include "CamCapture.h"

CamCapture::CamCapture(int w, int h) : p_capWebCam(nullptr) {
	this->Width = w;
	this->Height = h;
}

CamCapture::~CamCapture()
{ }

int CamCapture::Initialize()
{
	p_capWebCam = cvCaptureFromCAM(0);
	cvSetCaptureProperty(this->p_capWebCam, CV_CAP_PROP_FRAME_WIDTH, 320);
	cvSetCaptureProperty(this->p_capWebCam, CV_CAP_PROP_FRAME_HEIGHT, 280);

	if(!p_capWebCam){
		return 0; //Returns 0 cannot Continue
	}
	return 1; //Success
}

IplImage* CamCapture::GetFrame()
{
	this->frame = cvQueryFrame(this->p_capWebCam);
	return this->frame;
}

void CamCapture::EndCapture()
{
	cvReleaseCapture(&p_capWebCam);
}

