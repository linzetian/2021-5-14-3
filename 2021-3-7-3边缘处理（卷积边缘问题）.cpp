//边缘处理（卷积边缘问题）
#include<opencv2/opencv.hpp>
#include<opencv2\imgproc\types_c.h>
#include<opencv2\imgproc.hpp>
#include<iostream>
#include<math.h>
using namespace std;
using namespace cv;

int main()
{
	Mat src, dst;
	src = imread("F:/image/1.2.png");
	if (!src.data)
	{
		printf("can not load the picture");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	namedWindow("边缘处理", WINDOW_AUTOSIZE);
	imshow("input", src);
	int top =(int) (0.05 * src.rows);
	int bottom= (int)(0.05 * src.rows);
	int left = (int)(0.05 * src.cols);
	int right = (int)(0.05 * src.cols);
	//printf("width=%d\nheight=%d\npixel=%d",src.cols,src.rows, src.cols* src.rows);
	RNG rng(12345);
	//Scalar color = Scalar(rng.uniform(0,255), rng.uniform(0, 255), rng.uniform(0, 255));
	int c = 0;
	int borderType= BORDER_DEFAULT;//初始值设置为默认的default
	while (true)
	{
		c = waitKey(500);
		if ((char)c == 27)//27==ESC退出
		{
			break;
		}
		else if ((char)c == 'r')//单引号，从键盘中输入的
		{
			borderType = BORDER_CONSTANT;
		}
		else if ((char)c == 'g')
		{
			borderType = BORDER_REPLICATE;
		}
		else if((char)c == 'b')
		{
			borderType = BORDER_WRAP;
		}
		/*else
			borderType = BORDER_DEFAULT;*/
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		copyMakeBorder(src, dst, top, bottom, left, right, borderType, color);
		imshow("边缘处理", dst);
	}
	return 0;
}