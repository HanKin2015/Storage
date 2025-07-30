#include <opencv2/calib3d.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // 读取图像
    Mat image1 = imread("test.jpg");
    Mat image2 = imread("mouse.png");
    if (image1.empty() || image2.empty()) return -1;

    // 特征点检测与匹配
    Ptr<Feature2D> detector = ORB::create();
    vector<KeyPoint> keypoints1, keypoints2;
    Mat descriptors1, descriptors2;
    detector->detectAndCompute(image1, noArray(), keypoints1, descriptors1);
    detector->detectAndCompute(image2, noArray(), keypoints2, descriptors2);

    BFMatcher matcher(NORM_HAMMING);
    vector<DMatch> matches;
    matcher.match(descriptors1, descriptors2, matches);

    // 计算基础矩阵
    vector<Point2f> points1, points2;
    for (const auto& match : matches) {
        points1.push_back(keypoints1[match.queryIdx].pt);
        points2.push_back(keypoints2[match.trainIdx].pt);
    }
    Mat fundamentalMatrix = findFundamentalMat(points1, points2, FM_RANSAC);

    // 输出基础矩阵
    cout << "Fundamental Matrix:\n" << fundamentalMatrix << endl;

    return 0;
}