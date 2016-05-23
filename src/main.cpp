#include <iostream>
#include <opencv2\opencv.hpp>
#include <opencv\highgui.h>
#include <SFML\Graphics.hpp>
#include <GL\glew.h>

using namespace cv;

void saturate(Mat* mat) {
	Scalar intensity = mat->at<uchar>(0, 1);
}

int main() {
	sf::Window window(sf::VideoMode(800, 600), "OpenGL");

	bool running = true;
	while (running)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				running = false;
			}
			else if (event.type == sf::Event::Resized)
			{
				glViewport(0, 0, event.size.width, event.size.height);
			}
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		window.display();
	}
}

#if 0
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
#endif