/*******************************************************************************
* 文 件 名: 获取图像属性.cpp
* 文件描述: 获取图像属性
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

int main()
{
    // 读取图像
    Mat image = imread("仓鼠.png");

    if (image.empty()) {
        cout << "错误：无法加载图像，请检查路径是否正确。" << endl;
        return -1;
    }

    // 获取图像属性
    int width = image.cols;  // 图像宽度
    int height = image.rows; // 图像高度
    int channels = image.channels(); // 图像通道数

    cout << "图像宽度: " << width << endl;
    cout << "图像高度: " << height << endl;
    cout << "图像通道数: " << channels << endl;

    return 0;
}