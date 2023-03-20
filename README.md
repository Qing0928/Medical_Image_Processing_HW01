# Medical_Image_Processing_HW01

## Gray Level Transforms

## 初始化

```
Mat src_img = imread("Original.png", 0);//以灰階圖像載入
Mat negatives_img, log_img, power_law_img;
Transformation trans;
```

## Negatives

```
trans.toNegatives(src_img, negatives_img);
```

## Log

```
trans.logTransform(src_img, log_img);
```

## Power-Law(Gamma)

```
double gamma = 0.04;
trans.powerLaw(src_img, power_law_img, gamma);
```

## 處理用class
```
class Transformation
{
public:
	void toNegatives(Mat src, Mat &output) {
		output = 255 - src;
	}

	void logTransform(Mat src, Mat& output) {
		double c;
		double r_min, r_max;//r_min用不到
		minMaxLoc(src, &r_min, &r_max);//訂出極值
		c = 255 / log(1 + r_max);//放大常數
		//c = 30;
		src.convertTo(src, CV_32F);
		src += 1;
		log(src, output);//取log >> 輸出一個size跟src一樣的array
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
```
