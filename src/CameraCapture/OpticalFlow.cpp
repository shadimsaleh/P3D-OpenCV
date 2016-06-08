#include "OpticalFlow.h"
#include <iostream>

OpticalFlow::OpticalFlow(CamCapture* cam, int interval)
{
	capture = cam;

	this->interval = interval;

	opticalFlow = cv::Mat(capture->GetFrameHeight(), capture->GetFrameWidth(), CV_32FC3);

	termcrit = CvTermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03);
	subPixWinSize = CvSize(10, 10);
	winSize = CvSize(31, 31);
}

void OpticalFlow::GetFlow()
{
	*capture->GetCapture() >> frame;
	frame.copyTo(rgbFrames);
	cv::cvtColor(rgbFrames, image_next_Gray, CV_BGR2GRAY);

	if (needToInitialize) {
		cv::goodFeaturesToTrack(image_next_Gray, points1, MAX_COUNT, 0.01, 5, 
			cv::Mat(), 3, false, 0.04);
		needToInitialize = false;
	}

	else if (!points2.empty())
	{
		//nice::Print("Calculating  calcOpticalFlowPyrLK", true);
		cv::calcOpticalFlowPyrLK(image_prev_Gray, image_next_Gray, points2, points1,
			status, err, winSize, 3, termcrit, 0, 0.0001);
#if DEBUG 1
		for (size_t i = 0; i < points2.size(); i++) {
			std::cout << "X = " << int(points1[i].x - points2[i].x)
				<< " Y = " << int(points1[i].y - points2[i].y) << "\n";
			points1[k++] = points1[i];
		}
#endif

		cv::goodFeaturesToTrack(image_next_Gray, points1, MAX_COUNT,
			0.01, 10, cv::Mat(), 3, 0, 0.04);
	}

	std::swap(points2, points1);
	//if (!points1.empty()) points1.clear();
	image_next_Gray.copyTo(image_prev_Gray);
}

void OpticalFlow::Release()
{
	frame.release();
	image_prev_Gray.release();
	image_next_Gray.release();
	rgbFrames.release();
	opticalFlow.release();
}
