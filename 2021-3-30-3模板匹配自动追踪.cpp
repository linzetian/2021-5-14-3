//模板匹配自动追踪
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include<opencv2\imgproc\types_c.h>
#include <opencv2//highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int match_method =CV_TM_SQDIFF;
int method_max = 5;
const char* output = "templatematch";
const char* input = "input";
const char* match = "matchtemplate";
Mat src,temp,dst;
void templatematch_demo(int, void*);
int main() 
{
	temp = imread("F:/image/4.7.png");
	VideoCapture cap;
	// 读取摄像头
	cap.open(0);
	// 判断摄像头是否打开
	if (!cap.isOpened()) {
		std::cerr << "Could't open capture" << std::endl;
		return -1;
	}
	//Mat src;
	// 接收键盘上的输入
	namedWindow("input", WINDOW_AUTOSIZE);
	namedWindow(match,WINDOW_AUTOSIZE);
	char keyCode;
	// 保存的图片名称
	std::string imgName = "123.jpg";
	while (1) {
		// 把读取的摄像头传入Mat对象中
		cap >> src;
		// 判断是否成功
		if (src.empty()||temp.empty()) {
			break;
		}
		// 把每一帧图片表示出来
		imshow("input", src);
		createTrackbar("匹配算法方法", match, &match_method, method_max, templatematch_demo);
		templatematch_demo(0, 0);
		//waitKey(0);
		// 在30毫秒内等待是否存在键盘输入
		keyCode = waitKey(30);
		if (keyCode == 's') {
			// 把图片保存起来
			imwrite(imgName, src);
			imgName.at(0)++;
			src.release();
		}
		else if (keyCode == 27) {
			break;
		}
	}
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