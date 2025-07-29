/*******************************************************************************
* 文 件 名: 访问和修改像素值.cpp
* 文件描述: 访问和修改像素值
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

    // 访问像素值（BGR格式）
    Vec3b pixel = image.at<Vec3b>(100, 100); // 获取(100, 100)位置的像素值
    cout << "B: " << (int)pixel[0] << ", G: " << (int)pixel[1] << ", R: " << (int)pixel[2] << endl;

    // 修改像素值
    image.at<Vec3b>(100, 100) = Vec3b(255, 0, 0); // 将(100, 100)位置的像素设置为蓝色

    // 显示修改后的图像
    imshow("Modified Image", image);
    waitKey(0);
    destroyAllWindows();

    return 0;
}