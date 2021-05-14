//形态学操作应用————水平线垂直线
#include<opencv2/opencv.hpp>
#include<opencv2\imgproc\types_c.h>
#include<opencv2\imgproc.hpp>
#include<iostream>
using namespace std;
using namespace cv;
int main()
{
	Mat src,dst,binImg,output, output1;
	src = imread("F:/image/2.4.png");
	if (!src.data)
	{
		printf("can not load the picture");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input",src);
	cvtColor(src,dst,CV_BGR2GRAY);
	imshow("gray", dst);
	adaptiveThreshold(~dst,binImg,255,ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY,7,-2);
	//水平结构元素
	Mat pline = getStructuringElement(MORPH_RECT ,Size(src.cols/16,1),Point(-1,-1));
	//垂直结构元素
	Mat vline = getStructuringElement(MORPH_RECT, Size(1,src.rows/16), Point(-1, -1));
	//erode(binImg,output,pline,Point(-1,-1));
	//dilate(output,output1,pline,Point(-1,-1));腐蚀膨胀等价于开操作
	morphologyEx(binImg,output,MORPH_RECT,pline,Point(-1,-1));
	morphologyEx(binImg, output1, MORPH_RECT, vline, Point(-1, -1));
	Mat output2, output3;
	bitwise_not(output,output2);
	bitwise_not(output1, output3);
	namedWindow("binImg", WINDOW_AUTOSIZE);
	imshow("binImg", binImg);
	imshow("pline", output2);
	imshow("vlline", output3);
	waitKey(0);
	return 0;
}