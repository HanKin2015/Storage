/*******************************************************************************
* 文 件 名: write_image.cpp
* 文件描述: 保存图片
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.18
* 修改日期：2025.07.18
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    const std::string read_image_path = "仓鼠.png";
    const std::string write_image_path = "mouse.png";

    // 打开图片
    cv::Mat image = cv::imread(read_image_path);
    if (image.empty()) {
        std::cout << "imread failed" << std::endl;
        return -1;
    }

    cv::namedWindow("HanKin", cv::WINDOW_AUTOSIZE);
    cv::imshow("HanKin", image);

    int key = cv::waitKey(0);
    int ascii = static_cast<int>('s'); 
    if (key == ascii) {
        cv::imwrite(write_image_path, image);
        std::cout << "write success" << std::endl;
    } else {
        std::cout << "write fail" << std::endl;
    }
    cv::destroyAllWindows();
    return 0;
}