#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // 打开视频文件或摄像头
    VideoCapture cap("video.mp4");
    if (!cap.isOpened()) {
        cout << "错误：无法打开视频文件或摄像头！" << endl;
        return -1;
    }

    // 读取第一帧
    Mat oldFrame, oldGray;
    cap >> oldFrame;
    cvtColor(oldFrame, oldGray, COLOR_BGR2GRAY);

    // 选择特征点
    vector<Point2f> oldPoints;
    goodFeaturesToTrack(oldGray, oldPoints, 100, 0.3, 7);

    // 处理视频帧
    Mat frame, gray;
    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        // 转换为灰度图像
        cvtColor(frame, gray, COLOR_BGR2GRAY);

        // 计算光流
        vector<Point2f> newPoints;
        vector<uchar> status;
        vector<float> err;
        calcOpticalFlowPyrLK(oldGray, gray, oldPoints, newPoints, status, err);

        // 绘制光流轨迹
        for (size_t i = 0; i < oldPoints.size(); i++) {
            if (status[i]) {
                line(frame, oldPoints[i], newPoints[i], Scalar(0, 255, 0), 2);
                circle(frame, newPoints[i], 3, Scalar(0, 0, 255), -1);
            }
        }

        // 更新帧和特征点
        oldGray = gray.clone();
        oldPoints = newPoints;

        // 显示结果
        namedWindow("Optical Flow", WINDOW_NORMAL);   // WINDOW_AUTOSIZE
        imshow("Optical Flow", frame);

        // 按下 ESC 键退出
        if (waitKey(30) == 27) break;
    }

    // 释放资源
    cap.release();
    destroyAllWindows();

    return 0;
}