// This sample code is to show the histogram equalization on RGB images.

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <iostream>
#include <vector>
#include <cmath>
using namespace cv;
using namespace std;

int main()
{
	Mat src = imread("night.jpg");
	Mat dst = Mat::zeros(src.rows, src.cols, CV_8UC3);

	vector<Mat> channels;
	split(src, channels);
	Mat B = channels.at(0);
	Mat G = channels.at(1);
	Mat R = channels.at(2);

	equalizeHist(B, B);
	equalizeHist(G, G);
	equalizeHist(R, R);

	vector<Mat> tmpVector;
	tmpVector.push_back(B);
	tmpVector.push_back(G);
	tmpVector.push_back(R);
	merge(tmpVector, dst);

	imshow("RGB image (src)", src);
	imshow("HE on RGB image", dst);
	waitKey(0);
	return 0;
}