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

    // 获取视频的帧率和帧大小
    double fps = cap.get(CAP_PROP_FPS);
    Size frameSize(cap.get(CAP_PROP_FRAME_WIDTH), cap.get(CAP_PROP_FRAME_HEIGHT));
    cout << fps << ' ' << frameSize << endl;

    // 创建 VideoWriter 对象
    VideoWriter writer("output.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, frameSize);

    Mat frame;
    while (true) {
        // 读取下一帧
        cap >> frame;

        // 如果帧为空，说明视频已经结束
        if (frame.empty()) {
            break;
        }

        // 显示当前帧
        //imshow("Video", frame);

        // 将帧转换为灰度图像
        Mat grayFrame;
        cvtColor(frame, grayFrame, COLOR_BGR2GRAY);

        // 显示灰度帧
        imshow("Gray Video", grayFrame);
        
        // 将帧写入输出视频文件
        writer.write(frame);

        // 等待30毫秒，按下ESC键退出
        if (waitKey(30) == 27) {
            break;
        }
    }

    // 释放 VideoCapture 和 VideoWriter 对象
    cap.release();
    writer.release();
    // 关闭所有窗口
    destroyAllWindows();
    return 0;
}