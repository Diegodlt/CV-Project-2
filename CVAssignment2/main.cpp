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
void calculateTotalSobel(cv::Mat xImage, cv::Mat yImage, cv::Mat& dest);

int main() {
	cv::Mat image = cv::imread("einstein.jpg", cv::IMREAD_GRAYSCALE);
	num = boxSize / 2;

	// Exit if image is empty
	if (image.empty()) {
		cout << "Image is Empty" << endl;
		exit(0);
	}
	// Create some images and assign them dimension of the input image
	cv::Mat sobelCustom(cv::Size(image.cols, image.rows), CV_8U);
	cv::Mat blurCustom(cv::Size(image.cols, image.rows), CV_8U);
	cv::Mat gaussBlur(cv::Size(image.cols, image.rows), CV_8U);
	cv::Mat xImage(cv::Size(image.cols, image.rows), CV_8U);
	cv::Mat yImage(cv::Size(image.cols, image.rows), CV_8U);
	cv::Mat sobelX(cv::Size(image.cols, image.rows), CV_8U);
	cv::Mat sobelY(cv::Size(image.cols, image.rows), CV_8U);

	// Get input from user
	cout << image.cols << " + " << image.rows << endl;
	cout << "Number of channels: " << image.channels() << endl;
	cout << "Enter box size: "; cin >> boxSize;

	// Box filter
	//applyBoxFilter(image, blurCustom);

	// Sobel X-direction
	applySobelFilter(image, xImage, true);
	//cv::imshow("Sobel X", xImage);
	// Sobel Y-direction
	applySobelFilter(image, yImage, false);
	//cv::imshow("Sobel Y", yImage);
	
	calculateTotalSobel(xImage, yImage, sobelCustom);

	// Built-in OpenCV functions
	cv::Mat cvBlur;
	cv::blur(image, cvBlur, cv::Size(boxSize, boxSize));

	cv::Sobel(image, sobelX, CV_8U, 1, 0);
	cv::Sobel(image, sobelY, CV_8U, 0, 1);
	cv::Mat sobelCV = abs(sobelX) + abs(sobelY);

	cv::GaussianBlur(image, gaussBlur, cv::Size(0,0), 1);

	/* Resutls */
	//cv::imshow("CV Blur", cvBlur);
	cv::imshow("Original", image);
	cv::imshow("OpenCV Sobel", sobelCV);
	cv::imshow("Custom Sobel", sobelCustom);
	cv::imshow("Gauss Blur", gaussBlur);

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

void calculateTotalSobel(cv::Mat xImage, cv::Mat yImage, cv::Mat& dest) {
	
	for (int i = 0; i < xImage.rows; i++) {
		for (int j = 0; j < xImage.cols; j++) {
			int result = sqrt( ( xImage.at<uchar>(i, j)*xImage.at<uchar>(i, j) ) + (yImage.at<uchar>(i, j)*yImage.at<uchar>(i, j)));
			dest.at<uchar>(i, j) = cv::saturate_cast<uchar>(result);
		}
	}

}