# 学习记录

## 1、说明
这个文件还是有存在的必要，免得下次再来排查又要重新学习一遍。

## 2、在盒子端执行文件
demo来自：https://chat.forchange.cn/
见：D:\Github\Storage\udev\v4l2\验证VIDIOC_QBUF和VIDIOC_DQBUF\v4l2_example.cpp
```
No LSB modules are available.
Distributor ID: Debian
Description:    Debian GNU/Linux 9.5 (stretch)
Release:        9.5
Codename:       stretch
```

g++ v4l2.cpp -g -o v4l2
两款摄像头不同的报错：
```
root@hankin:/home# ./v4l2
VIDIOC_S_FMT: Device or resource busy
root@hankin:/home# ./v4l2
VIDIOC_S_FMT: Input/output error
```
原因：由于摄像头没有留在本地，将摄像头留在本地后使用正确的代码测试正常，能正常获取图片数据。

## 3、在UOS1050环境执行
```
root@uos1050:/home# ./v4l2
VIDIOC_QUERYBUF: Invalid argument
```
原因：代码问题，直接从https://chat.forchange.cn/下载的代码申请缓冲区的部分有问题。

## 4、成功栗子
代码来源：https://mp.weixin.qq.com/s/bbh9uY5q0CrqXDCc8rzLQA
demo见：D:\Github\Storage\udev\v4l2\验证VIDIOC_QBUF和VIDIOC_DQBUF\v4l2_perfect_example.cpp
图片数据见：D:\Github\Storage\udev\v4l2\验证VIDIOC_QBUF和VIDIOC_DQBUF\3.mjpg
备注：直接使用Windows照片查看器进行查看







