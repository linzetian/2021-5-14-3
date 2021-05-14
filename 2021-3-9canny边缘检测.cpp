//canny边缘检测
#include<opencv2/opencv.hpp>
#include<opencv2\imgproc\types_c.h>
#include<iostream>
#include<math.h>

using namespace std;
using namespace cv;

Mat src,dst,dst1;
Mat gray,cannyImg,cannyImg1;
const char* output = "canny";
int start_value = 163;
int max_value = 255;
void canny_demo(int ,void*);
int main()
{
	src = imread("F:/image/2.8.png");
	if (!src.data)
	{
		printf("can not load the picture");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	namedWindow(output, WINDOW_AUTOSIZE);
	imshow("input", src);
	createTrackbar("阈值",output,&start_value,max_value,canny_demo);
	canny_demo(0,0);
	waitKey(0);
	return 0; 
}

void canny_demo(int, void*)
{
	blur(src,dst,Size(3,3),Point(-1,-1), BORDER_DEFAULT);
	cvtColor(dst,gray,CV_BGR2GRAY);
	Canny(gray, cannyImg, start_value,start_value*2,3,false);
	//可以进行彩色阈值操作
	/*dst1.create(src.size(), src.type());
	src.copyTo(dst1,cannyImg1);*/
	imshow(output,cannyImg);
}