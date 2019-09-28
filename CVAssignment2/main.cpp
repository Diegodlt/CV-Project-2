#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc.hpp>

using namespace std;


int main() {
	cv::Mat image = cv::imread("bicycle.bmp");
	int boxSize = 3; // Default box size

	if (image.empty()) {
		cout << "Image is Empty" << endl;
		exit(0);
	}

	cout << image.cols << " + " << image.rows << endl;
	cout << "Enter box size: "; cin >> boxSize;

	cv::Mat newImage(cv::Size(image.cols, image.rows), CV_8UC3);

	int div = boxSize / 2;

	for (int i = div; i < image.rows - div ; i++) {
		for (int j = div; j < image.cols - div; j++) {
			for (int c = 0; c < image.channels(); c++) {
				int  avg = 0;
				for (int k = 0; k < boxSize; k++) {
					for (int n = 0; n < boxSize; n++) {
						int x = div - k;
						int y = div - n;
						avg += image.at<cv::Vec3b>(i - x, j - y)[c];
					}
				}
				newImage.at<cv::Vec3b>(i, j)[c] = (avg) / (boxSize*boxSize);
			}
		}
	}
	cv::Mat result;
	cv::blur(image, result, cv::Size(boxSize, boxSize));

	cv::imshow("CV Blur", result);
	cv::imshow("Original", image);
	cv::imshow("Custom Blur", newImage);

	cv::waitKey(0);
	return 0;
}