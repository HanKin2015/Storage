# 方法二很严谨

import cv2

# 方式一
def img_similarity(img1_path, img2_path):
    """
    # 自定义计算两个图片相似度函数
    :param img1_path: 图片1路径
    :param img2_path: 图片2路径
    :return: 图片相似度
    """
    img1 = cv2.imread(img1_path, cv2.IMREAD_GRAYSCALE)
    img2 = cv2.imread(img2_path, cv2.IMREAD_GRAYSCALE)
    w1, h1 = img1.shape
    w2, h2 = img2.shape
    img1 = cv2.resize(img1, (h1, w1))
    img2 = cv2.resize(img2, (h2, w2))
    # 初始化ORB检测器
    orb = cv2.ORB_create()
    kp1, des1 = orb.detectAndCompute(img1, None)
    kp2, des2 = orb.detectAndCompute(img2, None)
    # 提取并计算特征点
    bf = cv2.BFMatcher(cv2.NORM_HAMMING)
    # knn筛选结果
    matches = bf.knnMatch(des1, trainDescriptors=des2, k=2)
    # 查看最大匹配点数目
    good = [m for (m, n) in matches if m.distance < 0.75 * n.distance]
    print(float(len(good)), len(matches))
    if float(len(good)) == len(matches):
        similary = 1
    else:
        similary = float(len(good)) / len(matches)
    if similary > 0.1:
        print("判断为ture,两张图片相似度为:%s" % similary)
    else:
        print("判断为false,两张图片相似度为:%s" % similary)
    return similary

# 方式二
def img_similarity_2(img1_path, img2_path):
    img = cv2.imread(img1_path)
    img1 = cv2.imread(img2_path)
    # 计算图img的直方图
    H1 = cv2.calcHist([img], [1], None, [256], [0, 256])
    H1 = cv2.normalize(H1, H1, 0, 1, cv2.NORM_MINMAX, -1)  # 对图片进行归一化处理

    # 计算图img2的直方图
    H2 = cv2.calcHist([img1], [1], None, [256], [0, 256])
    H2 = cv2.normalize(H2, H2, 0, 1, cv2.NORM_MINMAX, -1)

    # 利用compareHist()进行比较相似度
    similarity = cv2.compareHist(H1, H2, 0)
    print(int(similarity))

if __name__ == "__main__":
    img1_path = 'save_diff.png'
    img2_path = 'tmp.png'
    img_similarity(img1_path, img2_path)
    img_similarity_2(img1_path, img2_path)