#include "OpticalFlow.h"

OpticalFlow::OpticalFlow(CamCapture* cam)
{
	capture = cam;

	opticalFlow = cv::Mat(capture->GetFrameHeight(), capture->GetFrameWidth(), CV_32FC3);

	termcrit = CvTermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03);
	subPixWinSize = CvSize(10, 10);
	winSize = CvSize(31, 31);
}

void OpticalFlow::GetFlow()
{
	this->frame = capture->GetFrame().getMatRef();
	frame.copyTo(rgbFrames);
	cvCvtColor(&rgbFrames, &image_next_Gray, CV_BGR2GRAY);

	if (needToInitialize) {
		goodFeaturesToTrack(image_next_Gray, points1, MAX_COUNT, 0.01, 5, cv::Mat(), 3, 0, 0.04);
		needToInitialize = false;
	}
	else if (!points2.empty())
	{
		//Print("Calculating  calcOpticalFlowPyrLK", true);
		calcOpticalFlowPyrLK(image_prev_Gray, image_next_Gray, points2, points1, status, err, winSize, 3, termcrit, 0, 0.0001);


		for (int i = k = 0; i < points2.size(); i++)
		{
			//Print("X = " + std::to_string(int(points1[i].x - points2[i].x)) +
			//	" Y = " + std::to_string(int(points1[i].y - points2[i].y)), false);
			points1[k++] = points1[i];
		}
	}


	std::swap(points2, points1);
	points1.clear();
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
