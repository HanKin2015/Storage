#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

int main() {
    // 读取图像
    Mat image = imread("test.jpg");
    if (image.empty()) return -1;

    // 转换为灰度图像
    Mat grayImage;
    cvtColor(image, grayImage, COLOR_BGR2GRAY);

    // 高斯滤波
    Mat blurredImage;
    GaussianBlur(grayImage, blurredImage, Size(5, 5), 0);

    // 显示结果
    imshow("Original Image", image);
    imshow("Blurred Image", blurredImage);
    waitKey(0);

    return 0;
}