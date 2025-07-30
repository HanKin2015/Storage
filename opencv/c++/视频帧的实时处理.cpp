#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    // 创建 VideoCapture 对象并打开视频文件
    VideoCapture cap("example.mp4");

    // 检查视频是否成功打开
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open video file." << std::endl;
        return -1;
    }

    Mat prevFrame, nextFrame, diffFrame;
    cap >> prevFrame;
    cvtColor(prevFrame, prevFrame, COLOR_BGR2GRAY);

    while (true) {
        cap >> nextFrame;
        if (nextFrame.empty()) {
            break;
        }

        cvtColor(nextFrame, nextFrame, COLOR_BGR2GRAY);

        // 计算帧间差异
        absdiff(prevFrame, nextFrame, diffFrame);

        // 显示差异帧
        imshow("Motion Detection", diffFrame);

        // 更新前一帧
        prevFrame = nextFrame.clone();

        if (waitKey(30) == 27) {
            break;
        }
    }

    // 释放 VideoCapture 对象
    cap.release();
    // 关闭所有窗口
    destroyAllWindows();
    return 0;
}