#pragma once
#include <GL/glew.h>
#include <opencv/cxcore.hpp>
#include <opencv/highgui.h>
#include <opencv2/videoio.hpp>


#define MAXFACES 10

class CamCapture
{
public:
	CamCapture();
	~CamCapture();

	int Initialize();
	cv::Mat GetFrame_Mat() const;
	IplImage* GetFrame_IplImage() const;
	cv::VideoCapture* GetCapture() const { return this->p_capWebCam; }
	void EndCapture(void) const;

	double GetFrameHeight(){
		this->Height = this->p_capWebCam->get(CV_CAP_PROP_FRAME_HEIGHT);
		return this->Height;
	}
	double GetFrameWidth(){
		this->Width = this->p_capWebCam->get(CV_CAP_PROP_FRAME_WIDTH);
		return  this->Width;
	}

private:
	cv::VideoCapture* p_capWebCam;

	GLdouble Width;
	GLdouble Height;
};

