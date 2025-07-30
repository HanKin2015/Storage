/*******************************************************************************
* 文 件 名:  图像的复制与克隆.cpp
* 文件描述:  图像的复制与克隆
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.29
* 修改日期：2025.07.29
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    // 读取图像
    Mat image = imread("仓鼠.png");

    if (image.empty()) {
        cout << "错误：无法加载图像，请检查路径是否正确。" << endl;
        return -1;
    }

    // 复制图像
    Mat copiedImage = image.clone();

    // 修改复制的图像
    circle(copiedImage, Point(100, 100), 50, Scalar(0, 255, 0), 2); // 在复制的图像上画一个圆

    // 显示原始图像和修改后的图像
    imshow("Original Image", image);
    imshow("Copied Image", copiedImage);
    waitKey(0);
    destroyAllWindows();

    return 0;
}