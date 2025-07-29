#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    // 读取图像
    cv::Mat image = cv::imread("仓鼠.png");

    // 检查图像是否成功加载
    if (image.empty()) {
        std::cout << "无法加载图像！" << std::endl;
        return -1;
    }

    // 创建窗口并显示图像
    cv::namedWindow("Example", cv::WINDOW_AUTOSIZE);
    cv::imshow("Example", image);

    // 等待按键
    cv::waitKey(0);

    return 0;
}