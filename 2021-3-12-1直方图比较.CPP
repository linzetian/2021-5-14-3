//直方图比较
#include<opencv2/opencv.hpp>
#include<opencv2\imgproc\types_c.h>
#include<iostream>
#include<math.h>

using namespace std;
using namespace cv;

String converToString(double d);//
int main()
{
	Mat src, test1,test2;
	const char* output = "直方图计算";
	src = imread("F:/image/2.8.png"); 
	test1 = imread("F:/image/3.2.png");
	test2 = imread("F:/image/1.7.png");
	if (!src.data&&(!test1.data)&&(!test2.data))
	{
		printf("can not load the picture");
		return -1;
	}
	//namedWindow("input", WINDOW_AUTOSIZE);
	//namedWindow(output, WINDOW_AUTOSIZE);
	//imshow("input", src);
	cvtColor(src,src,CV_BGR2HSV);
	cvtColor(test1, test1, CV_BGR2HSV);
	cvtColor(test2, test2, CV_BGR2HSV);
	int channels[] = {0,1};//由于HSV是双通道，数组有两个元素
	int b_h = 50, b_s = 60;
	const int histsize[] = {b_h,b_s};
	float h_hist[] = {0,180};//色度范围
	float s_hist[] = { 0,360};//饱和度范围
	const  float* ranges[] = { h_hist ,s_hist };//值域范围
	MatND hist_src;//多维，输出直方图数据
	MatND hist_test1;
	MatND hist_test2;
	calcHist(&src,1,channels,Mat(), hist_src,2,histsize,ranges,true,false);//计算直方图
	normalize(hist_src, hist_src,0,1,NORM_MINMAX,-1,Mat());//对输出的计算直方图进行归一化
	calcHist(&test1, 1, channels, Mat(), hist_test1, 2, histsize, ranges, true, false);//计算直方图
	normalize(hist_test1, hist_test1, 0, 1, NORM_MINMAX, -1, Mat());//对输出的计算直方图进行归一化
	calcHist(&test2, 1, channels, Mat(), hist_test2, 2, histsize, ranges, true, false);//计算直方图
	normalize(hist_test2, hist_test2, 0, 1, NORM_MINMAX, -1, Mat());//对输出的计算直方图进行归一化
	
	//进行直方图比较
	double srcsrc = compareHist(hist_src, hist_src,CV_COMP_CORREL);
	double srctest1 = compareHist(hist_src, hist_test1, CV_COMP_CORREL);
	double srctest2 = compareHist(hist_src, hist_test2, CV_COMP_CORREL);
	double test1test2 = compareHist(hist_test1, hist_test2, CV_COMP_CORREL);
	printf("test1test2=%lf\n", test1test2);

	//double转化为字符串
	Mat test12;
	test1.copyTo(test12);
	putText(src, converToString(srcsrc), Point(50, 50), FONT_HERSHEY_COMPLEX,1, Scalar(0, 200, 255), 2, LINE_AA);
	putText(test1, converToString(srctest1), Point(50, 50), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 200, 255), 2, LINE_AA);
	putText(test2, converToString(srctest2), Point(50, 50), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 200, 255), 2, LINE_AA);
	putText(test12, converToString(test1test2), Point(50, 50), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 200, 255), 2, LINE_AA);


	namedWindow("srcsrc", WINDOW_AUTOSIZE);
	namedWindow("srctest1", WINDOW_AUTOSIZE);
	namedWindow("srctest2", WINDOW_AUTOSIZE);
	namedWindow("test1test2", WINDOW_AUTOSIZE);
	imshow("srcsrc", src);
	imshow("srctest1",test1);
	imshow("srctest2", test2);
	imshow("test1test2", test12);
	waitKey(0);
	return 0;
}

String converToString(double d)
{
	ostringstream os;
	if (os << d)
		return os.str();
	return "invalid conersion";
}