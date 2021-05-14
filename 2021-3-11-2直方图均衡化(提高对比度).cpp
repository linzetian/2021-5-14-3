//直方图均衡化(提高对比度)
#include<opencv2/opencv.hpp>
#include<opencv2\imgproc\types_c.h>
#include<iostream>
#include<math.h>

using namespace std;
using namespace cv;

int main()
{
	Mat src, dst,gray;
	const char* output = "Histogram";
	src = imread("F:/image/2.8.png");
	if (!src.data)
	{
		printf("can not load the picture");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	namedWindow(output, WINDOW_AUTOSIZE);
	cvtColor(src,gray,CV_BGR2GRAY);
	imshow("input", src);
	equalizeHist(gray,dst);
	imshow(output, dst);
	waitKey(0);
	return 0;
}