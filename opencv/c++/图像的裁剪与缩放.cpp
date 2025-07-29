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

int main() {
    // 读取图像
    Mat image = imread("仓鼠.png");

    if (image.empty()) {
        cout << "错误：无法加载图像，请检查路径是否正确。" << endl;
        return -1;
    }

    // 裁剪图像
    Rect roi(100, 100, 100, 100); // (x, y, width, height)
    Mat croppedImage = image(roi);

    // 缩放图像
    Mat resizedImage;
    resize(image, resizedImage, Size(400, 400)); // 缩放到400x400

    // 显示裁剪和缩放后的图像
    imshow("Cropped Image", croppedImage);
    imshow("Resized Image", resizedImage);
    waitKey(0);
    destroyAllWindows();

    return 0;
}