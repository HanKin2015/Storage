/*******************************************************************************
* 文 件 名: 图像的几何变换.cpp
* 文件描述: 图像的几何变换
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

    // 旋转图像
    Mat rotatedImage;
    Point2f center(image.cols / 2, image.rows / 2); // 旋转中心
    double angle = 45; // 旋转角度
    double scale = 1.0; // 缩放比例
    Mat rotationMatrix = getRotationMatrix2D(center, angle, scale);
    warpAffine(image, rotatedImage, rotationMatrix, image.size());

    // 显示旋转后的图像
    imshow("Rotated Image", rotatedImage);
    waitKey(0);
    destroyAllWindows();

    return 0;
}