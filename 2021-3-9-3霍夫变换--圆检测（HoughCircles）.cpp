//霍夫变换--圆检测（HoughCircles）
#include<opencv2/opencv.hpp>
#include<opencv2\imgproc\types_c.h>
#include<iostream>
#include<math.h>

using namespace std;
using namespace cv;

int main()
{
	Mat src, dst,srcblur;
	const char* output = "Houghcircles";
	src = imread("F:/image/2.9.png");
	if (!src.data)
	{
		printf("can not load the picture");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	namedWindow(output, WINDOW_AUTOSIZE);
	imshow("input", src);
	medianBlur(src, srcblur,3);
	cvtColor(srcblur, srcblur,CV_BGR2GRAY);
	imshow("gray", srcblur);
	vector<Vec3f>circles;
	src.copyTo(dst);
	HoughCircles(srcblur,circles,HOUGH_GRADIENT,1,10,100,25,5,40);
	for (size_t i = 0; i < circles.size(); i++)
	{
		Vec3f point1 = circles[i];
		circle(dst, Point(point1[0], point1[1]),point1[2], Scalar(0, 0, 255), 2, LINE_AA);//画圆
		circle(dst, Point(point1[0], point1[1]),2, Scalar(100, 255, 150), 2, LINE_AA);//找出圆心
	}
	imshow(output, dst);
	waitKey(0);
	return 0;
}