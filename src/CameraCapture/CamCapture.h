#pragma once
#include <Components\Mesh.h>
#include <Components\Transform.h>
#include <GL/glew.h>
#include <opencv/cv.h>
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
	cv::OutputArray& GetFrame() const;
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
	//CvCapture* p_capWebCam;
	cv::VideoCapture* p_capWebCam;

	//IplImage* frame;

	GLdouble Width;
	GLdouble Height;
};

