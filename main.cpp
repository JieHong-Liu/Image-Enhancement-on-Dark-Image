#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;
void LocalEnhancement(Mat& src, Mat& dst);
void GlobalHistogramEqualization(Mat& image, Mat& dst); // for 3 channel
void BGR2HSV(Mat& src,Mat& dst);
double calculateHue(double R,double G,double B,double V);
double findMax(double a, double b, double c)
{
	double max = a;
	if (b > a && b > c)
	{
		max = b;
	}
	else if (c > a && c > b)
	{
		max = c;
	}
	return max;
}
double findMin(double a, double b, double c)
{
	double min = a;
	if (b < a && b < c)
	{
		min = b;
	}
	else if (c < a && c < b)
	{
		min = c;
	}
	return min;
}
int main()
{
	Mat src = imread("night.jpg");
	Mat dst = Mat::zeros(src.rows, src.cols, CV_8UC3);
	Mat HSV_src,local_dst,global_dst,tmpHSV;
	cvtColor(src, HSV_src, COLOR_BGR2HSV);

	vector<Mat> channels;
	split(HSV_src, channels);
	Mat H = channels.at(0);
	Mat S = channels.at(1);
	Mat V = channels.at(2);

	LocalEnhancement(V, local_dst);
	equalizeHist(local_dst, global_dst);

	vector<Mat> tmpVector;
	tmpVector.push_back(H);
	tmpVector.push_back(S);
	tmpVector.push_back(global_dst);
	merge(tmpVector, tmpHSV);

	cvtColor(tmpHSV, dst, COLOR_HSV2BGR);
	imshow("src", src);
#if 1
	imwrite("night-HSV.jpg", HSV_src);
	imwrite("night-local-dst.jpg", local_dst);
	imwrite("night-global-dst.jpg", global_dst);
#endif
	imwrite("night-proposed_img.jpg", dst);
	waitKey(0);
	return 0;
}

void LocalEnhancement(Mat& src, Mat& dst)
{
	// Performing Gaussian Blur
	Mat gaussian_blur;
	Mat sharpened_img = Mat::zeros(src.rows, src.cols, CV_8UC1);
	Mat mask = Mat::zeros(src.rows, src.cols, CV_8UC1);
	GaussianBlur(src, gaussian_blur, Size(3, 3), 0, 0);

#if 1
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			if (src.at<uchar>(i, j) - gaussian_blur.at<uchar>(i, j) < 0)
			{
				mask.at<uchar>(i, j) = 0;

			}
			else
			{
				mask.at<uchar>(i, j) = src.at<uchar>(i, j) - gaussian_blur.at<uchar>(i, j);

			}
			if (src.at<uchar>(i, j) + 1 * mask.at<uchar>(i, j) > 255)
			{
				sharpened_img.at<uchar>(i, j) = 255;
			}
			else
			{
				sharpened_img.at<uchar>(i, j) = src.at<uchar>(i, j) + 1 * mask.at<uchar>(i, j);

			}
		}
	}
#endif
#if 1
	imwrite("local_before-blurred.jpg", src);
	imwrite("Gaussian-Blurred.jpg", gaussian_blur);
	imwrite("Mask.jpg", mask);
	imwrite("Sharpened-image.jpg", sharpened_img);
	waitKey();
	destroyAllWindows();
#endif	
	sharpened_img.copyTo(dst);
}

void BGR2HSV(Mat& src, Mat& dst)
{
	// BGR TO HSV. 
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			double B = src.at<Vec3b>(i, j)[0] / 255.0;
			double G = src.at<Vec3b>(i, j)[1] / 255.0;
			double R = src.at<Vec3b>(i, j)[2] / 255.0;
			double V = findMax(R, G, B);
			dst.at<Vec3b>(i,j)[2] = 255.0 * V;						// V
			dst.at<Vec3b>(i,j)[1] = 255.0 * (V - findMin(R, G, B)) / V;	// S
			dst.at<Vec3b>(i,j)[0] = calculateHue(R, G, B, V);// Calculate 
		}
	}
}

double calculateHue(double R, double G, double B,double V)
{
	double H = 0;
	if (V == R)
	{
		H = fmod((60 * (G - B)) / (V - findMin(R, G, B)),360.0);
	}
	else if (V == G)
	{
		H = fmod(120 + (60 * (B - R)) / (V - findMin(R, G, B)),360.0);
	}
	else if (V == B)
	{
		H = fmod(240 + (60 * (R - G)) / (V - findMin(R, G, B)),360.0);
	}
	else if (R == G && G == B)
	{
		H = 0;
	}
	return H;
}


void GlobalHistogramEqualization(Mat& image, Mat& dst) // for 3 channel
{

#if 0

	equalizeHist(V, V);
	

#endif
}