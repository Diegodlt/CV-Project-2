#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc.hpp>

using namespace std;


int main() {
	cv::Mat image = cv::imread("bicycle.bmp");
	if (image.empty()) {
		cout << "Image is Empty" << endl;
		exit(0);
	}
	cv::imshow("Image", image);

	cv::waitKey(0);
	return 0;
}