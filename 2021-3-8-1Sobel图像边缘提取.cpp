//Sobel图像边缘提取
#include<opencv2/opencv.hpp>
#include<opencv2\imgproc\types_c.h>
#include<iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat src, dst;
	src = imread("F:/image/2.8.png");
	if (!src.data)
	{
		printf("can not load the picture");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	//namedWindow("sobelImg", WINDOW_AUTOSIZE);
	imshow("input", src);
	Mat gray,blurImg;
	GaussianBlur(src, blurImg, Size(3, 3), 0, 0);
	cvtColor(blurImg, gray, CV_BGR2GRAY);
	imshow("gray", gray);
	Mat xgrad, ygrad;
	Sobel(gray,xgrad,CV_16S,1,0,3);
	Sobel(gray, ygrad, CV_16S, 0, 1, 3);//CV_16S大于等于CV_8U//取绝对值
	convertScaleAbs(xgrad, xgrad);
	convertScaleAbs(ygrad, ygrad);
	//addWeighted(xgrad,0.5,ygrad,0.5,0,xygrad);//最终梯度//可以手工改进提高边缘识别度
	//通过G=|GX|+|GY|实现（自定义）
	Mat xygrad = Mat(xgrad.size(),xgrad.type());
	int width = xgrad.cols;
	int height = xgrad.rows;
	for (int row = 0; row < height; row++)
	{
		for (int col=0; col < width; col++)
		{
			int x = xgrad.at<uchar>(row, col);
			int y = ygrad.at<uchar>(row,col);
			int xy = x + y;
			xygrad.at<uchar>(row, col) = saturate_cast<uchar>(xy);
		}
	}
	imshow("xgrad", xgrad);
	imshow("ygrad", ygrad);
	imshow("xygrad", xygrad);
	waitKey(0);
	return 0;
}