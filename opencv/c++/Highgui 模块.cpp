#include <opencv2/highgui.hpp>

using namespace cv;

int main() {
    // 读取图像
    Mat image = imread("test.jpg");
    if (image.empty()) return -1;

    // 创建窗口并显示图像
    namedWindow("Display Window", WINDOW_AUTOSIZE);
    imshow("Display Window", image);

    // 等待用户按键
    waitKey(0);

    // 关闭窗口
    destroyAllWindows();

    return 0;
}