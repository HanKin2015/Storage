#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    VideoCapture cap(0);

    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open camera." << std::endl;
        return -1;
    }
    
    Mat frame;
    while (true) {
        cap >> frame;
        if (frame.empty()) {
            break;
        }

        // 应用Canny边缘检测
        Mat edges;
        Canny(frame, edges, 100, 200);

        // 显示边缘检测结果
        imshow("Edges", edges);

        if (waitKey(30) == 27) {
            break;
        }
    }

    cap.release();
    destroyAllWindows();

    // 释放 VideoCapture 对象
    cap.release();
    // 关闭所有窗口
    destroyAllWindows();
    return 0;
}