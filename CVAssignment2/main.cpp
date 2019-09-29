#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc.hpp>

using namespace std;

int num = 0;
int boxSize = 3;// Default box size

const int sobelX[3][3] = {
	{-1, 0 , 1},
	{-2, 0, 2},
	{-1, 0, 1}
};

const int sobelY[3][3] = {
	{-1, -2, -1},
	{0, 0, 0},
	{1, 2, 1}
};

void applyBoxFilter(cv::Mat& image, cv::Mat& dest);
void applySobelFilter(cv::Mat& image, cv::Mat& dest, bool xdir);

int main() {
	cv::Mat image = cv::imread("einstein.jpg", cv::IMREAD_GRAYSCALE);

	// Exit if image is empty
	if (image.empty()) {
		cout << "Image is Empty" << endl;
		exit(0);
	}

	// Get input from user
	cout << image.cols << " + " << image.rows << endl;
	cout << "Number of channels: " << image.channels() << endl;
	cout << "Enter box size: "; cin >> boxSize;

	// Create new image and assign the dimension of the box
	cv::Mat newImage(cv::Size(image.cols, image.rows), CV_8U);
	num = boxSize / 2;

	//applyBoxFilter(image, newImage);
	applySobelFilter(image, newImage, true);
	cv::imshow("Sobel X", newImage);

	applySobelFilter(image, newImage, false);
	cv::imshow("Sobel Y", newImage);
	
	// Built-in OpenCV function
	//cv::Mat cvBlur;
	//cv::blur(image, cvBlur, cv::Size(boxSize, boxSize));

	//cv::imshow("CV Blur", cvBlur);
	cv::imshow("Original", image);
	cv::imshow("Custom Blur", newImage);

	cv::waitKey(0);
	return 0;
}

void applyBoxFilter(cv::Mat& image, cv::Mat& dest ) {

	for (int i = num; i < image.rows - num; i++) {
		for (int j = num; j < image.cols - num; j++) {
			for (int c = 0; c < image.channels(); c++) {
				int  avg = 0;
				for (int k = 0; k < boxSize; k++) {
					for (int n = 0; n < boxSize; n++) {
						int x = num - k;
						int y = num - n;
						avg += image.at<cv::Vec3b>(i - x, j - y)[c];
					}
				}
				dest.at<cv::Vec3b>(i, j)[c] = (avg) / (boxSize*boxSize);
			}
		}
	}
}

void applySobelFilter(cv::Mat& image, cv::Mat& dest, bool xdir) {


	for (int i = num; i < image.rows - num; i++) {
		for (int j = num; j < image.cols - num; j++) {
			int sum = 0;
			for (int k = 0; k < boxSize; k++) {
				for (int n = 0; n < boxSize; n++) {
					int x = num - k;
					int y = num - n;
					if (xdir) {
						sum += image.at<uchar>(i - x, j - y) * sobelX[k][n];
					}
					else {
						sum += image.at<uchar>(i - x, j - y) * sobelY[k][n];
					}
				}
			}
			dest.at<uchar>(i, j) = cv::saturate_cast<uchar>(sum);
		}
	}
}