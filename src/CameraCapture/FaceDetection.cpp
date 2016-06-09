#include "FaceDetection.h"
#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/videoio/videoio.hpp"
#include "opencv2/highgui/highgui.hpp"

FaceDetection::FaceDetection(char* fileName, CamCapture* capture)
	: m_storage(nullptr), m_frame(nullptr)
{
	this->m_fileName = fileName;
	this->m_capture = capture;
}

FaceDetection::~FaceDetection()
{

}

void FaceDetection::Initialize()
{
	this->m_cascade_f[0] = static_cast<CvHaarClassifierCascade*>(
		cvLoad(this->m_fileName, nullptr, nullptr, nullptr));
	SetupMemory();
}

void FaceDetection::Detect()
{
	this->m_frame = m_capture->GetFrame_IplImage();	
	if (!m_frame) return;	
	//assert(m_cascade_f[0] && m_storage);

	DetectFaces();
}

void FaceDetection::DetectFaces()
{
	Rect *debug_Rect;
	GLuint i;

	IplImage* grayImage = cvCreateImage(cvSize(this->m_frame->width, this->m_frame->height), 8, 1);

	cvCvtColor(m_frame, grayImage, CV_BGR2GRAY);
	cvEqualizeHist(grayImage, grayImage);

	CvSeq* faces = cvHaarDetectObjects(grayImage, m_cascade_f[0], m_storage, 1.1, 2, 0, cvSize(30, 30));

	for (i = 0; i<MAXFACES; i++){
		if (imgfaces[i]) cvReleaseImage(&imgfaces[i]);
	}

	if (faces->total == 0) return;

	for (i = 0; i < (faces ? faces->total : 0); i++){
		debug_Rect = reinterpret_cast<Rect*>(cvGetSeqElem(faces, i));

		if(i<MAXFACES){
			cvSetImageROI(m_frame, cvRect(debug_Rect->x, debug_Rect->y, 
				debug_Rect->width, debug_Rect->height));
			imgfaces[i] = cvCreateImage(cvSize(128, 128), m_frame->depth, m_frame->nChannels);
			cvResize(m_frame, imgfaces[i], CV_INTER_LINEAR);
			cvResetImageROI(m_frame);
		}
		cvRectangle(m_frame, Point(debug_Rect->x, debug_Rect->y),
			Point(debug_Rect->x + debug_Rect->width, debug_Rect->y + debug_Rect->height), CV_RGB(255, 0, 0), 1, 8, 0);
	}

	cvClearMemStorage(this->m_storage);

	cvReleaseImage(&grayImage);
}

void FaceDetection::SetupMemory()
{
	m_storage = cvCreateMemStorage(0);
}
