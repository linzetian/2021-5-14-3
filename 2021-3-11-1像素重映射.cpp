//像素重映射
#include<opencv2/opencv.hpp>
#include<opencv2\imgproc\types_c.h>
#include<iostream>
#include<math.h>

using namespace std;
using namespace cv;

Mat src, dst,map_x, map_y;
int index = 0;
const char* output = "像素重映射";
void update_map(void);//进行像素操作（对像素点进行操作）
int main()
{
	src = imread("F:/image/2.8.png");
	if (!src.data)
	{
		printf("can not load the picture");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	namedWindow(output, WINDOW_AUTOSIZE);
	imshow("input", src);

	map_x.create(src.size(),CV_32FC1);//与copyTo区分开
	map_y.create(src.size(),CV_32FC1);

	unsigned int c = 0;
	while (true)
	{
		c = waitKey(500);
		if ((char)c == 27)
		{
			break;
		}
		index = c % 4;
		update_map();
		remap(src,dst,map_x,map_y,INTER_LINEAR,BORDER_CONSTANT,Scalar(0,255,255));
		imshow(output,dst);
	}
		//waitKey(0);
	return 0;
}
void update_map(void)
{
	for (int row = 0; row < src.rows; row++)
	{
		for (int col = 0; col < src.cols; col++)
		{
			switch (index)
			{
			case 0:
				if (col > (src.cols * 0.25) && col <(src.cols * 0.75) && row > (src.rows * 0.25) && row <(src.rows * 0.75))
				{
					map_x.at<float>(row, col) = 2 * (col - (src.cols * 0.25) );
					map_y.at<float>(row, col) = 2 * (row - (src.rows * 0.25) );
				}
				else
				{
					map_x.at<float>(row, col) = 0;
					map_y.at<float>(row, col) = 0;
				}
				break;
			case 1:
				map_x.at<float>(row, col) = (src.cols - col - 1);
				map_y.at<float>(row, col) = row;
				break;
			case 2:
				map_x.at<float>(row, col) = col;
				map_y.at<float>(row, col) = (src.rows - row - 1);
				break;
			case 3:
				map_x.at<float>(row, col) = (src.cols - col - 1);
				map_y.at<float>(row, col) = (src.rows - row - 1);
				break;
			}
		}
	}
}