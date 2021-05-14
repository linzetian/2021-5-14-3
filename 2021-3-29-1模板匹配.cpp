//模板匹配
#include<opencv2/opencv.hpp>
#include<opencv2\imgproc\types_c.h>
#include<iostream>
#include<math.h>

using namespace std;
using namespace cv;

Mat src,temp, dst;
int match_method =CV_TM_SQDIFF;
int method_max = 5;
const char* output = "templatematch";
const char* input = "input";
const char* match = "matchtemplate";

void templatematch_demo(int, void*);
int main()
{
	src = imread("F:/image/3.9.png");
	temp = imread("F:/image/4.0.png");
	if (src.empty()|| temp.empty())
	{
		printf("can not load the picture");
		return -1;
	}
	namedWindow(input, WINDOW_AUTOSIZE);
	namedWindow(output, WINDOW_AUTOSIZE);
	namedWindow(match, WINDOW_AUTOSIZE);
	imshow(input, temp);
	createTrackbar("匹配算法方法", output, &match_method, method_max, templatematch_demo);
	templatematch_demo(0, 0);
	waitKey(0);
	return 0;
}

void templatematch_demo(int, void*)
{
	int width = src.cols - temp.cols + 1;
	int height = src.rows - temp.rows + 1;
	Mat result(width,height,CV_32FC1);
	//imshow(output, result);
	matchTemplate(src,temp,result, match_method,Mat());
	normalize(result, result, 0, 1, NORM_MINMAX,-1,Mat());

	double min, max;
	Point minloc;
	Point maxloc;
	src.copyTo(dst);
	Point temploc;
	minMaxLoc(result,&min,&max,&minloc,&maxloc,Mat());
	
	if ((match_method == CV_TM_SQDIFF) || (match_method == CV_TM_SQDIFF_NORMED))
	{
		temploc = minloc;
	}
	else
	{
		temploc = maxloc;
	}
	rectangle(dst,Rect(temploc.x, temploc.y,temp.cols,temp.rows),Scalar(0,0,255),2,8);
	rectangle(result, Rect(temploc.x, temploc.y, temp.cols, temp.rows), Scalar(0, 0, 255), 2, 8);
	//imshow(output, result);//有问题
	imshow(match, dst);
	//return;
}