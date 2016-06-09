#include "OpticalFlow.h"
#include <iostream>
#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/videoio/videoio.hpp"
#include "opencv2/highgui/highgui.hpp"

OpticalFlow::OpticalFlow(CamCapture* cam, int interval)
{
	capture = cam;

	this->interval = interval;

	opticalFlow = cv::Mat(capture->GetFrameHeight(), capture->GetFrameWidth(), CV_32FC3);

	termcrit = CvTermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03);
	subPixWinSize = CvSize(2, 2);
	winSize = CvSize(1, 1);
}

void OpticalFlow::GetFlow()
{
	this->frame = capture->GetFrame_Mat();
	frame.copyTo(rgbFrames);
	cv::cvtColor(rgbFrames, image_next_Gray, CV_BGR2GRAY);

	if (needToInitialize) {
		cv::goodFeaturesToTrack(image_next_Gray, points1, MAX_COUNT, 0.01, 5, 
			cv::Mat(), 3, false, 0.04);
		cv::cornerSubPix(image_next_Gray, points1, subPixWinSize, 
			cv::Size(-1, -1), termcrit);
		needToInitialize = false;
	}

	else if (!points2.empty())
	{
		if (image_prev_Gray.empty())
			image_next_Gray.copyTo(image_prev_Gray);

		//nice::Print("Calculating  calcOpticalFlowPyrLK", true);
		cv::calcOpticalFlowPyrLK(image_prev_Gray, image_next_Gray, points2, points1,
			status, err, winSize, 3, termcrit, 0, 0.001);

#if DEBUG 1
		size_t i, k = 0;
		for (i = 0; i < points1.size(); i++) {
			std::cout << "X = " << int(points1[i].x - points2[i].x)
				<< " Y = " << int(points1[i].y - points2[i].y) << "\n";
			points1[k++] = points1[i];
			cv::circle(rgbFrames, points1[i], 3, cv::Scalar(0, 255, 0), -1, 8);
		}
		points1.resize(k);

		cv::imshow("LK Demo", image_next_Gray);
		cv::imshow("Grey", rgbFrames);
#endif

		cv::goodFeaturesToTrack(image_next_Gray, points1, MAX_COUNT,
			0.01, 10, cv::Mat(), 3, 0, 0.04);
	}

	std::swap(points2, points1);
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
