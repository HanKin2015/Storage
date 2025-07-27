/*******************************************************************************
* 文 件 名: 图像的读取与显示.cpp
* 文件描述: 图像的读取与显示
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.24
* 修改日期：2025.07.24
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // 读取图像
    Mat image = imread("test.jpg");

    // 检查图像是否成功加载
    if (image.empty()) {
        cout << "错误：无法加载图像，请检查路径是否正确。" << endl;
        return -1;
    }

    // 显示图像
    namedWindow("Display Image", WINDOW_AUTOSIZE);
    imshow("Display Image", image);

    // 等待按键
    waitKey(0);

    // 关闭窗口
    destroyAllWindows();

    return 0;
}