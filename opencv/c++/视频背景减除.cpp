#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // 打开视频文件或摄像头
    VideoCapture cap("example.mp4");
    if (!cap.isOpened()) {
        cout << "错误：无法打开视频文件或摄像头！" << endl;
        return -1;
    }

    // 创建背景减除器
    Ptr<BackgroundSubtractor> bgSubtractor = createBackgroundSubtractorMOG2();

    // 处理视频帧
    Mat frame, fgMask;
    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        // 应用背景减除
        bgSubtractor->apply(frame, fgMask);

        // 显示结果
        imshow("Frame", frame);
        imshow("Foreground Mask", fgMask);

        // 按下 ESC 键退出
        if (waitKey(30) == 27) break;
    }

    // 释放资源
    cap.release();
    destroyAllWindows();

    return 0;
}