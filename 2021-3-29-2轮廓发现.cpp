//轮廓发现
#include<opencv2/opencv.hpp>
#include<opencv2\imgproc\types_c.h>
#include<iostream>

using namespace std;
using namespace cv;

int threshold_value = 100;
int threshold_max = 255;
Mat src, dst;
void demo_contours(int ,void*);
int main()
{
	src=imread("F:/image/3.9.png");
	if (!src.data)
	{
		printf("can not load the picture");
	}
	namedWindow("input",WINDOW_AUTOSIZE);
	namedWindow("output",WINDOW_AUTOSIZE);
	imshow("input",src);
	cvtColor(src,src,CV_BGR2GRAY);
	createTrackbar("阈值","output",&threshold_value,threshold_max,demo_contours);
	demo_contours(0, 0);
	waitKey(0);
	return 0;
}

void demo_contours(int , void*)
{
	vector<vector<Point>>contours;//定义轮廓对象
	vector<Vec4i>hierachy;//定义拓扑结构图
	//要先进行二值化，可以通过canny进行
	Mat canny_img;
	Canny(src, canny_img, threshold_value,threshold_value*2,3,false);
	//发现轮廓
	findContours(canny_img,contours,RETR_TREE,CHAIN_APPROX_SIMPLE,Point(0,0));

	RNG rng(12345);
	dst = Mat::zeros(src.size(), CV_8UC3);
	//绘制轮廓
	for (size_t i = 0; i < contours.size(); i++)
	{
		Scalar color=Scalar(rng.uniform(0,255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(dst, contours,i, color,1,8, hierachy,1,Point(0,0));
	}
	imshow("output",dst);
}