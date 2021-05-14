// 从摄像头中读取
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include<opencv2\imgproc\types_c.h>
#include <opencv2//highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;


int threshold_value = 100;
int threshold_max = 255;
Mat src,dst;
void demo_contours(int ,void*);

int main() {
	//namedWindow("input", cv::WINDOW_AUTOSIZE);

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
	namedWindow("output",WINDOW_AUTOSIZE);
	char keyCode;
	// 保存的图片名称
	std::string imgName = "123.jpg";
	while (1) {
		// 把读取的摄像头传入Mat对象中
		cap >> src;
		// 判断是否成功
		if (src.empty()) {
			break;
		}
		// 把每一帧图片表示出来
		imshow("input", src);
		cvtColor(src, src, CV_BGR2GRAY);
		createTrackbar("阈值", "output", &threshold_value, threshold_max, demo_contours);
		demo_contours(0, 0);
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


void demo_contours(int , void*)
{
	vector<vector<Point>>contours;//定义轮廓对象
	vector<Vec4i>hierachy;//定义拓扑结构图
	//要先进行二值化，可以通过canny进行
	Mat canny_img;
	Canny(src, canny_img, threshold_value,threshold_value*2,3,false);
	//发现轮廓
	findContours(canny_img,contours,RETR_TREE,CHAIN_APPROX_SIMPLE,Point(0,0));

	RNG rng(12345);
	dst = Mat::zeros(src.size(), CV_8UC3);
	//绘制轮廓
	for (int i = 0; i < contours.size(); i++)
	{
		Scalar color=Scalar(rng.uniform(0,255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(dst, contours,i, color,1,8, hierachy,1,Point(0,0));
	}
	imshow("output",dst);
}