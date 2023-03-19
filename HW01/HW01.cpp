#include <iostream>
#include <string.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

class Transformation
{
public:
	void toNegatives(Mat src, Mat &output) {
		output = 255 - src;
	}

	void logTransform(Mat src, Mat& output) {
		double c;//放大常數
		double r_min, r_max;//r_min用不到
		minMaxLoc(src, &r_min, &r_max);//訂出極值
		c = 255 / log(1 + r_max);
		//c = 30;
		src.convertTo(src, CV_32F);
		src += 1;
		log(src, output);//輸出一個size跟src一樣的array
		output = c * output;
		output.convertTo(output, CV_8UC1);
	}
	
	void powerLaw(Mat src, Mat& output, double gamma) {
		double c;
		double r_min, r_max;
		minMaxLoc(src, &r_min, &r_max);
		c = 255 / pow(r_max, gamma);
		src.convertTo(src, CV_32F);
		pow(src, gamma, output);
		output = c * output;
		output.convertTo(output, CV_8UC1);
	}
};

int main()
{
	Mat src_img = imread("Original.png", 0);//以灰階圖像載入
	Mat negatives_img, log_img, power_law_img;
	if (! src_img.data)
	{
		cout << "Can't read the file" << endl; 
		return 0;
	}
	imshow("originalIMG", src_img);
	Transformation trans;

	//negatives
	trans.toNegatives(src_img, negatives_img);
	imshow("negativesIMG", negatives_img);

	//log
	trans.logTransform(src_img, log_img);
	imshow("logIMG", log_img);

	//power-law
	double gamma = 0.04;
	trans.powerLaw(src_img, power_law_img, gamma);
	imshow("Power-LawlIMG", power_law_img);
	
	waitKey(0);
	return 0;
}