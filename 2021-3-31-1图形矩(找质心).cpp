//图形矩(找质心)
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include<opencv2\imgproc\types_c.h>
#include <opencv2//highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int threshold_value = 165;
int threshold_max = 255;
Mat src, src_gray, dst;
void demo_moments(int, void*);
int main() {
	src = imread("F:/image/4.2.png");
	if (!src.data)
	{
		printf("can not load the picture");
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	namedWindow("output", WINDOW_AUTOSIZE);
	imshow("input", src);
	cvtColor(src, src_gray, CV_BGR2GRAY);
	GaussianBlur(src_gray, src_gray, Size(3, 3),11,11);
	createTrackbar("阈值", "output", &threshold_value, threshold_max, demo_moments);
	demo_moments(0, 0);
	waitKey(0);
	return 0;
}

void demo_moments(int, void*)
{
	vector<vector<Point>>contours;//定义轮廓对象
	vector<Vec4i>hierachy;//定义拓扑结构图
	//要先进行二值化，可以通过canny进行
	Mat canny_img;
	threshold(src_gray, canny_img, threshold_value, threshold_max, THRESH_BINARY);
	//imshow("canny",canny_img);
	//发现轮廓
	findContours(canny_img, contours, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	vector<Moments>contours_moments(contours.size());
	vector<Point2f>ccs(contours.size());//定义圆心并初始化
	vector<float>radius(contours.size());//定义半径初始化


	for (int k = 0; k < contours.size(); k++)
	{
		contours_moments[k]=moments(contours[k]);
		ccs[k] = Point(static_cast<float>(contours_moments[k].m10/ contours_moments[k].m00) , static_cast<float>(contours_moments[k].m01 / contours_moments[k].m00));
	}

	RNG rng(12345);
	//绘制
	//dst = Mat::zeros(src.size(), src.type());
	src.copyTo(dst);
	Point2f pts[4];
	for (int i = 0; i < contours.size(); i++)
	{
		if (contours[i].size() < 30)
		{
			continue;
		}
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		//rectangle(dst, ploy_rect[i],color,2,8);
		printf(" x=%.2f y=%.2f\n", ccs[i].x, ccs[i].y);
		printf(" rank i=%d contourarea=%.2f arclength=%.2f\n",i,contourArea(contours[i]),arcLength(contours[i],true));
		drawContours(dst, contours,i,color,2,8, hierachy,0,Point(0,0));
		circle(dst, ccs[i], 3,color,1,8);
	}
	printf("piex.x=%d piex.y=%d",src.cols,src.rows);
	imshow("output", dst);
}