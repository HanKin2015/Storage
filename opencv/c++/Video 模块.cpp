#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

int main() {
    // 打开摄像头
    VideoCapture cap(0);
    if (!cap.isOpened()) return -1;

    Mat frame;
    while (true) {
        // 读取一帧
        cap >> frame;
        if (frame.empty()) break;

        // 显示帧
        imshow("Camera Feed", frame);

        // 按下 ESC 键退出
        if (waitKey(30) == 27) break;
    }

    // 释放摄像头并关闭窗口
    cap.release();
    destroyAllWindows();

    return 0;
}