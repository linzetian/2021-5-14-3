//图像金字塔，上采样（分辨率变大，图像放大），下采样反之，DOG(高斯不同)
#include<opencv2/opencv.hpp>
#include<opencv2\imgproc\types_c.h>
#include<opencv2\imgproc.hpp>
#include<iostream>
using namespace std;
using namespace cv;
int main()
{
	Mat src,up,down;
	src = imread("F:/image/1.7.png");
	if (!src.data)
	{
		printf("can not load the picture");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);
	//上采样
	pyrUp(src,up,Size(src.cols*2,src.rows*2));//*2表示图像放大两倍
	//降采样
	pyrDown(src,down, Size(src.cols/2, src.rows/2));//*2表示图像放大两倍
	//namedWindow("bigImg", WINDOW_AUTOSIZE);
	Mat g1, g2, dogImg,gray;
	cvtColor(src,gray,CV_BGR2GRAY);
	GaussianBlur(gray,g1,Size(5,5),0,0);
	GaussianBlur(g1, g2, Size(5,5), 0, 0);
	//两次高斯相减
	subtract(g1, g2, dogImg,Mat());
	//归一化显示
	normalize(dogImg,dogImg,255,0,NORM_MINMAX);
	imshow("bigImg", up);
	//namedWindow("smallImg", WINDOW_AUTOSIZE);
	imshow("smallImg",down);
	imshow("DOG",dogImg);
	waitKey(0);
	return 0;
}
