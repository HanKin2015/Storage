/*******************************************************************************
* 文 件 名: 图像颜色空间转换.cpp
* 文件描述: 图像颜色空间转换
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.28
* 修改日期：2025.07.28
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // 读取图像
    Mat image = imread("仓鼠.png");

    if (image.empty()) {
        cout << "错误：无法加载图像，请检查路径是否正确。" << endl;
        return -1;
    }

    // 转换为灰度图像
    Mat grayImage;
    cvtColor(image, grayImage, COLOR_BGR2GRAY);

    // 显示灰度图像
    imshow("Gray Image", grayImage);
    waitKey(0);
    destroyAllWindows();

    return 0;
}