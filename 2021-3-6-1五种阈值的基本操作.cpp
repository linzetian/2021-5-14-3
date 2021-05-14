//五种阈值的基本操作
#include<opencv2/opencv.hpp>
#include<opencv2\imgproc\types_c.h>
#include<opencv2\imgproc.hpp>
#include<iostream>
#include<math.h>
using namespace std;
using namespace cv;
Mat src,dst,gray;
char input[] = "input";
const char* output = "output_threshold";
int threshold_value = 127;
int threshold_max = 255;
int thresh_type = 2;
int thresh_typemax = 4;
void threshold_demo(int ,void*);
int main()
{
	src = imread("F:/image/2.8.png");
	if (!src.data)
	{
		printf("can not load the picture");
		return -1;
	}
	namedWindow(input, WINDOW_AUTOSIZE);
	namedWindow(output, WINDOW_AUTOSIZE);
	imshow("input", src);
	createTrackbar("threshold",output,&threshold_value,threshold_max,threshold_demo);
	createTrackbar("thresh_type", output, &thresh_type, thresh_typemax, threshold_demo);
	threshold_demo(0,0);
	
	waitKey(0);
	return 0;
}
void threshold_demo(int, void*)
{
	cvtColor(src, gray, CV_BGR2GRAY);
	threshold(gray,dst,threshold_value,threshold_max, thresh_type);//thresh_type表示阈值操作类型的起始值
	imshow(output, dst);
}