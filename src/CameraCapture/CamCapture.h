#pragma once
#include <Components\Mesh.h>
#include <Components\Transform.h>
#include <GL/glew.h>
#include <opencv/cv.h>
#include <opencv/cxcore.hpp>
#include <opencv/highgui.h>


#define MAXFACES 10

class CamCapture
{
public:
	CamCapture(int w, int h);
	~CamCapture();

	int Initialize();
	IplImage* GetFrame();
	CvCapture* GetCapture() const { return this->p_capWebCam; }
	void EndCapture(void);

private:
	CvCapture* p_capWebCam;
	
	IplImage* frame;

	GLuint Width;
	GLuint Height;
};

