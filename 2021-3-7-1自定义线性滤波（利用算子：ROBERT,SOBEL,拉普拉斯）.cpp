//自定义线性滤波（利用算子：ROBERT,SOBEL,拉普拉斯）
#include<opencv2/opencv.hpp>
#include<opencv2\imgproc\types_c.h>
#include<opencv2\imgproc.hpp>
#include<iostream>
#include<math.h>
using namespace std;
using namespace cv;
//Mat src, dst, gray;
char input[] = "input";
const char* outputx = "robert_x";
const char* outputy = "robert_y";
int main()
{
	Mat src,dstx,dsty,dstx1,dsty1,dst2;
	src = imread("F:/image/2.8.png");
	if (!src.data)
	{
		printf("can not load the picture");
		return -1;
	}
	namedWindow(input, WINDOW_AUTOSIZE);
	namedWindow(outputx, WINDOW_AUTOSIZE);
	namedWindow(outputy, WINDOW_AUTOSIZE);
	namedWindow("sobelx", WINDOW_AUTOSIZE);
	namedWindow("sobely", WINDOW_AUTOSIZE);
	namedWindow("laplace", WINDOW_AUTOSIZE);
	imshow(input, src);
	//x方向Robert算子
	Mat kernelx = (Mat_<char>(2,2)<<1,0,0,-1);//Robert算子
	//y方向Robert算子
	Mat kernely = (Mat_<char>(2, 2) << 0, 1, -1, 0);//Robert算子
	//x方向Sobel算子
	Mat kernelx1 = (Mat_<char>(3, 3) << -1, 0, 1, -2,0,2,-1,0,1);
	//y方向Sobel算子
	Mat kernely1 = (Mat_<char>(3, 3) << -1,-2, -1, 0, 0, 0, 1, 2, 1);
	//Laplace算子
	Mat kernel2 = (Mat_<char>(3, 3) <<0,-1,0,-1,4,-1,0,-1,0);
	filter2D(src,dstx,-1,kernelx,Point(-1,-1),0.0);
	filter2D(src, dsty, -1, kernely, Point(-1, -1), 0.0);
	filter2D(src, dstx1, -1, kernelx1, Point(-1, -1), 0.0);
	filter2D(src, dsty1, -1, kernely1, Point(-1, -1), 0.0);
	filter2D(src, dst2, -1, kernel2, Point(-1, -1), 0.0);
	imshow(outputx, dstx);
	imshow(outputy, dsty);
	imshow("sobelx", dstx1);
	imshow("sobely", dsty1);
	imshow("laplace", dst2);
	waitKey(0);
	return 0;
}