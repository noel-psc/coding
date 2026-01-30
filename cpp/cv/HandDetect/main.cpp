#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;

int main(void)
{
	std::cout << "read cam\n";
	VideoCapture cap(0);
	if (!cap.isOpened()) {
		std::cout << "Error opening video stream or file" << std::endl;
		return -1;
	}
	Mat frame;

	while (true)
	{
		cap.read(frame);
		if (frame.empty())
			break;
		imshow("Frame", frame);
		waitKey(1);
	}

	return 0;
}