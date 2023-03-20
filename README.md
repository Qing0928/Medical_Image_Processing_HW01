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
