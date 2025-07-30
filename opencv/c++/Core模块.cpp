#include <opencv2/core.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // 创建一个 3x3 的矩阵
    Mat mat = (Mat_<int>(3, 3) << 1, 2, 3, 4, 5, 6, 7, 8, 9);

    // 输出矩阵
    cout << "Matrix:\n" << mat << endl;

    // 访问矩阵元素
    int value = mat.at<int>(1, 1);
    cout << "Value at (1, 1): " << value << endl;

    return 0;
}