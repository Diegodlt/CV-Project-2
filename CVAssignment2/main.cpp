#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc.hpp>

using namespace std;


int main() {
	cv::Mat image = cv::imread("bicycle.bmp");
	int boxSize = 3;

	if (image.empty()) {
		cout << "Image is Empty" << endl;
		exit(0);
	}

	cout << image.cols << " + " << image.rows << endl;

	cv::Mat newImage(cv::Size(image.cols, image.rows), CV_8UC3);

	for (int i = 1; i < image.rows - 1; i++) {
		for (int j = 1; j < image.cols - 1; j++) {
			for (int c = 0; c < image.channels(); c++) {
				newImage.at<cv::Vec3b>(i, j)[c] = (
					image.at<cv::Vec3b>(i - 1, j - 1)[c] + image.at<cv::Vec3b>(i - 1, j)[c] + image.at<cv::Vec3b>(i - 1, j + 1)[c]
					+ image.at<cv::Vec3b>(i, j - 1)[c] + image.at<cv::Vec3b>(i, j)[c] + image.at<cv::Vec3b>(i, j + 1)[c]
					+ image.at<cv::Vec3b>(i + 1, j - 1)[c] + image.at<cv::Vec3b>(i + 1, j)[c] + image.at<cv::Vec3b>(i + 1, j + 1)[c]
					)/9;
			}
		}
	}
	cv::Mat result;
	cv::blur(image, result, cv::Size(5, 5));

	cv::imshow("Blur", result);
	cv::imshow("Image", image);
	cv::imshow("New", newImage);

	cv::waitKey(0);
	return 0;
}