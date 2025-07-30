#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // 加载 Haar 级联分类器
    CascadeClassifier faceCascade;
    if (!faceCascade.load("haarcascade_frontalface_default.xml")) {
        cout << "错误：无法加载 Haar 级联分类器！" << endl;
        return -1;
    }

    // 打开摄像头
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cout << "错误：无法打开摄像头！" << endl;
        return -1;
    }

    // 实时检测人脸
    Mat frame;
    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        // 转换为灰度图像
        Mat gray;
        cvtColor(frame, gray, COLOR_BGR2GRAY);

        // 检测人脸
        vector<Rect> faces;
        faceCascade.detectMultiScale(gray, faces, 1.1, 3, 0, Size(30, 30));

        // 绘制检测结果
        for (const auto& face : faces) {
            rectangle(frame, face, Scalar(0, 255, 0), 2);
        }

        // 显示结果
        imshow("Face Detection", frame);

        // 按下 ESC 键退出
        if (waitKey(30) == 27) break;
    }

    // 释放资源
    cap.release();
    destroyAllWindows();

    return 0;
}