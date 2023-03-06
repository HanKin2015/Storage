# https://blog.csdn.net/NSJim/article/details/126446670
# Python+OpenCV判断图像是黑底还是白底
# 二值化操作指的是根据阈值来判断是为1还是0，没太大区别
# 暂时准确

# This script is used to judge a image is black based or white based
import cv2

# binarization
def BorW_binary(img, bwThresh):
    gray = cv2.cvtColor(img.copy(), cv2.COLOR_BGR2GRAY)  # gray image
    ret, thresh = cv2.threshold(gray, bwThresh, 255, cv2.THRESH_BINARY)  # binarization
    # get h and w of img
    imgShape = img.shape
    h = imgShape[0]
    w = imgShape[1]
    # init black and white point number
    blackNum, whiteNum = 0, 0
    k = h / w
    for x in range(w):
        y1 = int(k * x)
        y2 = int((-k) * x + h - 1)
        # prevent overflow
        if 0 <= y1 <= (h - 1) and 0 <= y2 <= (h - 1):
            # first diagonal line
            if thresh[y1][x] == 0:
                blackNum += 1
            else:
                whiteNum += 1
            # second diagonal line
            if thresh[y2][x] == 0:
                blackNum += 1
            else:
                whiteNum += 1
    print(blackNum, whiteNum)
    if blackNum > whiteNum:
        print("black based image")
    else:
        print("white based image")


# not binary
def BorW_not_binary(img, bwThresh):
    #img = cv2.resize(img, (256, 256))
    #cv2.imwrite("result.png", img)

    gray = cv2.cvtColor(img.copy(), cv2.COLOR_BGR2GRAY)  # gray image
    # ret, thresh = cv2.threshold(gray, 127, 255, cv2.THRESH_BINARY)  # binarization
    # get h and w of img
    imgShape = img.shape
    print(imgShape)
    h = imgShape[0]
    w = imgShape[1]
    # init black and white point number
    blackNum, whiteNum = 0, 0
    k = h / w
    for x in range(w):
        y1 = int(k * x)
        y2 = int((-k) * x + h - 1)
        # prevent overflow
        if 0 <= y1 <= (h - 1) and 0 <= y2 <= (h - 1):
            print(gray[y1][x], gray[y2][x])
            # first diagonal line
            if gray[y1][x] <= bwThresh:
                blackNum += 1
            else:
                whiteNum += 1
            # second diagonal line
            if gray[y2][x] <= bwThresh:
                blackNum += 1
            else:
                whiteNum += 1
    print(blackNum, whiteNum)
    if blackNum > whiteNum:
        print("black based image")
    else:
        print("white based image")


if __name__ == "__main__":
    img = cv2.imread("tmp.png")
    bwThresh = 245  # threshold value of black or white
    BorW_binary(img, bwThresh)
    BorW_not_binary(img, bwThresh)

