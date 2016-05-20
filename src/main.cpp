#include <iostream>
#include <opencv2\opencv.hpp>
#include <opencv\highgui.h>

using namespace cv;

void saturate(Mat* mat) {
	Scalar intensity = mat->at<uchar>(0, 1);
}

int main() {
	Mat image;
	VideoCapture cap;

	cap.open(0);

	namedWindow("window", 1);

	while (1) {
		cap >> image;
		imshow("window", image);
		waitKey(33);
	}
	return 0;
}