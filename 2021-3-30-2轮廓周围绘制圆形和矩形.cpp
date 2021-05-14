//轮廓周围绘制圆形和矩形
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include<opencv2\imgproc\types_c.h>
#include <opencv2//highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int threshold_value = 169;
int threshold_max = 255;
Mat src,src_gray ,dst;
void demo_contours(int, void*);
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
	blur(src_gray, src_gray,Size(3,3),Point(-1,-1),4);
	createTrackbar("阈值", "output", &threshold_value, threshold_max, demo_contours);
	demo_contours(0, 0);
	waitKey(0);
	return 0;
}

void demo_contours(int, void*)
{
	vector<vector<Point>>contours;//定义轮廓对象
	vector<Vec4i>hierachy;//定义拓扑结构图
	//要先进行二值化，可以通过canny进行
	Mat canny_img;
	threshold(src_gray, canny_img, threshold_value, threshold_max,THRESH_BINARY);
	//imshow("canny",canny_img);
	//发现轮廓
	findContours(canny_img, contours, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	vector<vector<Point>>contours_ploy(contours.size());
	vector<Rect>ploy_rect(contours.size());
	vector<Point2f>ccs(contours.size());//定义圆心并初始化
	vector<float>radius(contours.size());//定义半径初始化

	vector<RotatedRect>minRects(contours.size());//旋转矩阵
	vector<RotatedRect>myellipse(contours.size());
	
	for (int k = 0; k < contours.size(); k++)
	{
		approxPolyDP(Mat(contours[k]), contours_ploy[k],3,true);
		ploy_rect[k]=boundingRect(contours_ploy[k]);
		minEnclosingCircle(contours_ploy[k],ccs[k],radius[k]);
		if (contours_ploy[k].size() > 5)//要大于5才行
		{
			myellipse[k] = fitEllipse(contours_ploy[k]);
			minRects[k] = minAreaRect(contours_ploy[k]);
		}
	}

	RNG rng(12345);
	//绘制
	dst = Mat::zeros(src.size(), src.type());
	//src.copyTo(dst);
	Point2f pts[4];
	for (int i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		//rectangle(dst, ploy_rect[i],color,2,8);
		//circle(dst, ccs[i], radius[i],color,2,8);
		
		if (contours_ploy[i].size() > 5)
		{
			ellipse(dst, myellipse[i],color,2,8);
			minRects[i].points(pts);//
			for (int t=0;t<4;t++)
			{
				line(dst,pts[t],pts[(t+1)%4],color,1,8);
			}
		}
	}
	imshow("output", dst);
}