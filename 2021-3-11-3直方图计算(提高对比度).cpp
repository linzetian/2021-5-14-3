//直方图计算(提高对比度)
#include<opencv2/opencv.hpp>
#include<opencv2\imgproc\types_c.h>
#include<iostream>
#include<math.h>

using namespace std;
using namespace cv;

int main()
{
	Mat src, dst, gray;
	const char* output = "直方图计算";
	src = imread("F:/image/2.8.png");
	if (!src.data)
	{
		printf("can not load the picture");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	namedWindow(output, WINDOW_AUTOSIZE);
	imshow("input", src);
	//分通道显示
	vector<Mat>bgr_planes;
	split(src, bgr_planes);//多通道分为多个单通道
	//imshow(output,bgr_planes[0]);
	//imshow(output, dst);
	//计算直方图
	int histSize = 256;//直方图级数
	float range[] = {0,256};
	const float* histRange = { range };
	Mat b_hist, g_hist, r_hist;
	calcHist(&bgr_planes[0],1,0,Mat(), b_hist,1,&histSize, &histRange,true,false);
	calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, true, false);
	calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, true, false);
	//归一化
	int hist_height = 800;
	int  hist_width = 1200;
	int bin = hist_width / histSize;//直方图宽度
	Mat histImage(hist_width,hist_height,CV_8UC3,Scalar(0,0,0));//定义一张图,3表示3通道
	normalize(b_hist, b_hist,0, hist_height,NORM_MINMAX,-1,Mat());
	normalize(g_hist, g_hist, 0, hist_height, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, hist_height, NORM_MINMAX, -1, Mat());
	//绘制直方图
	for (int i = 1; i < histSize; i++)
	{
		line(histImage,Point((i-1)*bin, hist_height-cvRound(b_hist.at<float>(i-1))), Point((i) * bin, hist_height - cvRound(b_hist.at<float>(i))),Scalar(255,0,0),2,LINE_AA);
		line(histImage, Point((i - 1) * bin, hist_height - cvRound(g_hist.at<float>(i - 1))), Point((i)*bin, hist_height - cvRound(g_hist.at<float>(i))), Scalar(0, 255, 0), 2, LINE_AA);
		line(histImage, Point((i - 1) * bin, hist_height - cvRound(r_hist.at<float>(i - 1))), Point((i)*bin, hist_height - cvRound(r_hist.at<float>(i))), Scalar(0, 0, 255), 2, LINE_AA);
	}
	imshow(output,histImage);
	waitKey(0);
	return 0;
}