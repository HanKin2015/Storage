#include <opencv2/dnn.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace dnn;

int main() {
    // 加载模型
    Net net = readNetFromTensorflow("model.pb", "config.pbtxt");

    // 读取图像
    Mat image = imread("test.jpg");
    if (image.empty()) return -1;

    // 预处理
    Mat blob = blobFromImage(image, 1.0, Size(300, 300), Scalar(127.5, 127.5, 127.5), true, false);
    net.setInput(blob);

    // 推理
    Mat output = net.forward();

    // 处理输出
    // ...

    return 0;
}