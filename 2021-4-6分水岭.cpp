//分水岭
#include<opencv2/opencv.hpp>
#include<opencv2\imgproc\types_c.h>
#include<iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat img = imread("F:/image/4.2.png");
	if (img.empty())
		return -1;
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", img);

	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			if (img.at<Vec3b>(i, j) == Vec3b(255, 255, 255)) {
				img.at<Vec3b>(i, j)[0] = 0;
				img.at<Vec3b>(i, j)[1] = 0;
				img.at<Vec3b>(i, j)[2] = 0;
			}
		}
	}

	Mat filter2d_img;
	Mat kernel = (Mat_<float>(3, 3) << 1, 1, 1, 1, -8, 1, 1, 1, 1);
	filter2D(img, filter2d_img, CV_32F, kernel);
	filter2d_img.convertTo(filter2d_img, CV_8UC3);
	imshow("filter2d_img", filter2d_img);

	Mat result_img;
	result_img = img - filter2d_img;
	imshow("result_img", result_img);

	Mat gray;
	cvtColor(result_img, gray, CV_BGR2GRAY);
	imshow("gray", gray);
	//    我们使用自适应阈值，将图片变为黑白图像
	Mat binary_img;
	threshold(gray, binary_img, 0, 255, THRESH_BINARY | THRESH_OTSU);
	imshow("binary", binary_img);

	//确定图像的背景区域
	Mat sure_bg;
	Mat kernel1 = getStructuringElement(MORPH_RECT, Size(9, 9), Point(-1, -1));
	dilate(binary_img, sure_bg, kernel1, Point(-1, -1), 3);
	sure_bg.convertTo(sure_bg, CV_8UC1);
	imwrite("sure_bg.jpg", sure_bg);

	//确定前景区域
	Mat sure_fg;
	//距离变换：计算源像素的每个像素到最近的零像素的距离
	Mat dist_img;
	distanceTransform(binary_img, dist_img, DIST_L1, 3, 5);
	//我们将距离变换的图像进行归一化
	normalize(dist_img, dist_img, 0, 1, NORM_MINMAX);
	//距离大于0.4的皆为前景
	//imshow("dist_img",dist_img);
	threshold(dist_img, sure_fg, 0.4, 1, THRESH_BINARY);
	normalize(sure_fg, sure_fg, 0, 255, NORM_MINMAX);
	sure_fg.convertTo(sure_fg, CV_8UC1);
	imwrite("sure_fg.jpg", sure_fg);
	imshow("sure_fg",sure_fg);

	Mat unknown;
	unknown = sure_bg - sure_fg;
	imwrite("unknown.jpg", unknown);

	//前景对象标记是从1开始的整数
	Mat marker1;
	connectedComponents(sure_fg, marker1);

	Mat markers = Mat::ones(marker1.size(), marker1.type());
	markers = marker1 + markers;
	markers.convertTo(markers, CV_8UC1);

	//我们将图像中的未知区域标记为0
	for (int row = 0; row < unknown.rows; row++) {
		for (int col = 0; col < unknown.cols; col++) {
			uchar c = unknown.at<uchar>(row, col);
			if (c == 255)
				markers.at<uchar>(row, col) = 0;
		}
	}
	normalize(markers, markers, 0, 255, NORM_MINMAX);
	imwrite("markers.jpg", markers);
	imshow("markers",markers);
	//实施分水岭算法，标签图像将会被修改便捷区域的标记为-1
	markers.convertTo(markers, CV_32SC1);
	watershed(img, markers);
	Mat mark = Mat::zeros(markers.size(), CV_8UC1);
	markers.convertTo(mark, CV_8UC1);
	//    bitwise_not(mark,mark);
	imshow("water_img", mark);

	vector<uchar> pixes;
	vector<Vec3b> colors;
	RNG rng;
	Mat final_rst(mark.size(), CV_8UC3);
	for (int i = 0; i < markers.rows; i++) {
		for (int j = 0; j < markers.cols; j++) {
			uchar c = mark.at<uchar>(i, j);
			bool target = false;
			for (int k = 0; k < pixes.size(); k++) {
				if (c == pixes[k]) {
					final_rst.at<Vec3b>(i, j) = colors[k];
					target = true;
					break;
				}
			}
			if (target == false) {
				pixes.push_back(c);
				int r = rng.uniform(0, 255);
				int g = rng.uniform(0, 255);
				int b = rng.uniform(0, 255);
				Vec3b color = Vec3b((uchar)b, (uchar)g, (uchar)r);
				final_rst.at<Vec3b>(i, j) = color;
				colors.push_back(color);
			}
		}
	}
	imshow("final_rst", final_rst);



	//Mat src = imread("F:/image/5.4.png");
	//if (src.empty())
	//{
	//	printf("can not find the picture");
	//}
	//namedWindow("input",WINDOW_AUTOSIZE);
	//imshow("input",src);
	//for(int row=0;row<src.rows;row++)
	//	for (int col = 0; col < src.cols; col++)
	//	{
	//		if ((src.at<Vec3b>(row, col) == Vec3b(255, 255, 255)))
	//		{
	//			src.at<Vec3b>(row, col)[0] = 0;
	//			src.at<Vec3b>(row, col)[1] = 0;
	//			src.at<Vec3b>(row, col)[2] = 0;
	//		}
	//	}
	//namedWindow("blackgroundImg", WINDOW_AUTOSIZE);
	//imshow("blackgroundImg", src);
	////set kernel
	//Mat kernel = (Mat_<float>(3, 3) << 1, 1, 1, 1, -8, 1, 1, 1, 1);
	//Mat imgLaplace;
	//Mat sharp = src;
	//filter2D(src, imgLaplace,CV_32F,kernel,Point(-1,-1),0,BORDER_DEFAULT);
	//src.convertTo(sharp, CV_32F);
	//Mat imgResult = sharp - imgLaplace;
	//imgResult.convertTo(imgResult, CV_8UC3);
	//imgLaplace.convertTo(imgLaplace, CV_8UC3);
	////imshow("imgLaplace", imgLaplace);
	//imshow("imgResult", imgResult);
	//Mat binaryImg;
	//cvtColor(src, imgResult,CV_BGR2GRAY);//进行二值化要先进行灰度处理
	//threshold(imgResult, binaryImg,40,255,THRESH_BINARY|THRESH_OTSU);
	//imshow("binaryImg", binaryImg);

	////Mat distImg;
	////distanceTransform(binaryImg,distImg,DIST_L1,3,5);
	//////namedWindow("distImg",WINDOW_AUTOSIZE);
	//////imshow("distImg",distImg);
	////normalize(distImg,distImg,0,1,NORM_MINMAX);
	////imshow("distImg result", distImg);
	////threshold(distImg,distImg,0.4,1,THRESH_BINARY);
	waitKey(0);
	return 0;
}
