//直方图反向投射
#include<opencv2/opencv.hpp>
#include<opencv2\imgproc\types_c.h>
#include<iostream>
#include<math.h>

using namespace std;
using namespace cv;

//String converToString(double d);//
Mat src, hsv, test;
int bin = 41;
const char* output = "histback";
void histback_demo(int ,void*);
int main()
{
	src = imread("F:/image/3.3.png");
	if (!src.data )
	{
		printf("can not load the picture");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	namedWindow(output,WINDOW_AUTOSIZE);
	imshow("input", src);
	cvtColor(src, hsv, CV_BGR2HSV);
	test.create(hsv.size(),hsv.depth());
	int nchannels[] = { 0,0 };//由于HSV是双通道，数组有两个元素
	mixChannels(&hsv,1,&test,1, nchannels,1);
	createTrackbar("histGram", output,&bin,180,histback_demo);
	histback_demo(0,0);
	waitKey(0);
	return 0;
}

void histback_demo(int, void*)
{
	float range[] = {0,180};
	const float* histrange = {range};
	Mat b_hist;
	calcHist(&test,1, 0,Mat(),b_hist,1,&bin,&histrange,true,false);
	normalize(b_hist,b_hist,0,255,NORM_MINMAX,-1,Mat());
	Mat backprojectImg;
	calcBackProject(&test,1,0,b_hist, backprojectImg, &histrange,1,true);
	imshow(output, backprojectImg);

	int hist_h = 400;
	int hist_w = 400;
	int bin_w = hist_w / bin;
	Mat histImage(hist_w,hist_h,CV_8UC3,Scalar(0,0,0));
	for (int i = 1; i < bin; i++)
	{
		rectangle(histImage,Point((i-1)*bin_w,hist_h-cvRound(b_hist.at<float>(i-1)*(400/255))),Point(i*bin_w,hist_h),Scalar(0,0,255),-1);
	}
	imshow("直方图",histImage);
	return;
}