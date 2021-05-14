//点多边形测试
#include<opencv2/opencv.hpp>
#include<opencv2\imgproc\types_c.h>
#include<iostream>
using namespace cv;
using namespace std;
int main()
{
	const int r = 100;
	Mat src = Mat::zeros(r * 4, r * 4, CV_8UC1);

	vector<Point2f> vert(6);
	vert[0] = Point(3 * r / 2, static_cast<int>(1.34 * r));
	vert[1] = Point(1 * r, 2 * r);
	vert[2] = Point(3 * r / 2, static_cast<int>(2.66 * r));
	vert[3] = Point(5 * r / 2, static_cast<int>(2.66 * r));
	vert[4] = Point(3 * r, 2 * r);
	vert[5] = Point(5 * r / 2, static_cast<int>(1.34 * r));

	for (int i = 0; i < 6; i++)
	{
		line(src, vert[i], vert[(i + 1) % 6], Scalar(255), 3, 8, 0);
	}
	namedWindow("input",WINDOW_AUTOSIZE);
	namedWindow("output", WINDOW_AUTOSIZE);
	imshow("input",src);
	vector<vector<Point>> contours; //轮廓
	vector<Vec4i> hierachy;
	findContours(src, contours, hierachy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));//获取轮廓
	Mat raw_dist = Mat::zeros(src.size(), CV_32FC1);
	for (int row = 0; row < raw_dist.rows; row++) {
		for (int col = 0; col < raw_dist.cols; col++) {
			double dist = pointPolygonTest(contours[0], Point2f(static_cast<float>(col), static_cast<float>(row)), true);
			//contours[0]: 输入的轮廓
			//Point2f(static_cast<float>(col), static_cast<float>(row)): 测试点
			//true:是否返回距离值，如果是false，1表示在内面，0表示在边界上，-1表示在外部，true返回实际距离
			raw_dist.at<float>(row, col) = static_cast<float>(dist); //把每一个像素点都用距离值代替
		}
	}
	double minValue, maxValue;
	minMaxLoc(raw_dist, &minValue, &maxValue, 0, 0, Mat());//在一个数组中找到全局最小值和全局最大值,该函数不能用于多通道数组
	Mat drawImg = Mat::zeros(src.size(), CV_8UC3);
	for (int row = 0; row < drawImg.rows; row++) {
		for (int col = 0; col < drawImg.cols; col++) {
			float dist = raw_dist.at<float>(row, col); //读取每一个点到轮廓的距离
			if (dist > 0) { //点在轮廓内
				drawImg.at<Vec3b>(row, col)[0] = (uchar)abs((dist / maxValue) * 255);//abs绝对值函数， 
				//蓝色：离轮廓越远，蓝色越深
			}
			else if (dist < 0) { //点在轮廓外
				drawImg.at<Vec3b>(row, col)[2] = (uchar)abs((dist / minValue) * 255);
				//红色：离轮廓越远，红色越深
			}
			else {//点在轮廓上dist=0
				drawImg.at<Vec3b>(row, col)[0] = (uchar)abs(255 - dist);
				drawImg.at<Vec3b>(row, col)[1] = (uchar)abs(255 - dist);
				drawImg.at<Vec3b>(row, col)[2] = (uchar)abs(255 - dist);
				// 255,255,255 白色
			}
		}
	}
	imshow("output",drawImg);
	waitKey(0);
	return 0;
}