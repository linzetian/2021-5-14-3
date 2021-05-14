//Laplacian算子图像边缘处理
#include<opencv2/opencv.hpp>
#include<opencv2\imgproc\types_c.h>
#include<iostream>
#include<math.h>

using namespace std;
using namespace cv;

int main()
{
	Mat src;
	src = imread("F:/image/2.8.png");
	if (!src.data)
	{
		printf("can not load the picture");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);
	Mat gray, blurImg;
	GaussianBlur(src, blurImg, Size(3, 3), 0, 0);
	cvtColor(blurImg, gray, CV_BGR2GRAY);
	imshow("gray", gray);
	Mat laplanceImg,laplacianImg;
	Laplacian(gray,laplanceImg,CV_16S,3);//CV_16S大于等于CV_8U//取绝对值
	convertScaleAbs(laplanceImg, laplanceImg);//拉普拉斯后，值有正负值
	threshold(laplanceImg, laplacianImg,0,255,THRESH_OTSU|THRESH_BINARY);//阈值处理，提高轮廓度
	imshow("laplanceImg", laplacianImg);
	waitKey(0);
	return 0;
}