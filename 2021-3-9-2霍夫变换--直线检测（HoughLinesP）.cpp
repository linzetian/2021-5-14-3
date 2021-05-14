//霍夫变换--直线检测（HoughLinesP）
#include<opencv2/opencv.hpp>
#include<opencv2\imgproc\types_c.h>
#include<iostream>
#include<math.h>

using namespace std;
using namespace cv;

int main()
{
	Mat src,dst;
	const char* output = "Houghline";
	src = imread("F:/image/2.5.png");
	if (!src.data)
	{
		printf("can not load the picture");
		return -1;
	}
	namedWindow("canny", WINDOW_AUTOSIZE);
	namedWindow(output, WINDOW_AUTOSIZE);
	Mat src_gray;
	//先进行canny边缘检测
	Canny(src, src_gray,100,200,3);
	cvtColor(src_gray, dst, CV_GRAY2BGR);
	imshow("src_gray", src_gray);
	imshow("canny", dst);
	vector<Vec4f>plines;//定义一个存放直线信息的向量
	//HoughLinesp
	HoughLinesP(src_gray,plines,1,CV_PI/180,10,100,30);
	for (size_t i = 0; i < plines.size(); i++)
	{
		Vec4f point1 = plines[i];
		line(dst,Point(point1[0], point1[1]), Point(point1[2], point1[3]),Scalar(0,0,255),2,LINE_AA);
	}
	imshow(output,dst);
	waitKey(0);
	return 0;
}