//凸包convexhull
#include<opencv2/opencv.hpp>
#include<opencv2\imgproc\types_c.h>
#include<iostream>

using namespace std;
using namespace cv;

int threshold_value = 100;
int threshold_max = 255;
Mat src, dst,src_gray;
void demo_convexhull(int, void*);
int main()
{
	src = imread("F:/image/4.1.png");
	if (!src.data)
	{
		printf("can not load the picture");
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	namedWindow("output", WINDOW_AUTOSIZE);
	//namedWindow("output1", WINDOW_AUTOSIZE);
	imshow("input", src);
	cvtColor(src, src_gray, CV_BGR2GRAY);
	blur(src_gray, src_gray,Size(3,3),Point(-1,-1),4);
	createTrackbar("阈值", "output", &threshold_value, threshold_max, demo_convexhull);
	demo_convexhull(0, 0);
	waitKey(0);
	return 0;
}

void demo_convexhull(int, void*)
{
	vector<vector<Point>>contours;//定义轮廓对象
	vector<Vec4i>hierachy;//定义拓扑结构图
	//要先进行二值化，可以通过canny进行
	Mat threshold_img;

	threshold(src_gray, threshold_img, threshold_value, threshold_max ,THRESH_BINARY);
	//发现轮廓
	findContours(threshold_img, contours, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	vector<vector<Point>>convexnull(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		convexHull(contours[i], convexnull[i],false,true);//凸包调用
	}

	RNG rng(12345);
	dst = Mat::zeros(src.size(), CV_8UC3);
	//dst2 = Mat::zeros(src.size(), CV_8UC3);
	//绘制轮廓
	for (int i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(dst, contours, i, color, 1, 8, hierachy, 1, Point(0, 0));
		drawContours(dst, convexnull, i, color, 1, 8, Mat(), 1, Point(0, 0));
	}
	imshow("output", dst);
	
}