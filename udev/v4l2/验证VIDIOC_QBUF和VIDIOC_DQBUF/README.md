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

## 3、在UOS1050环境执行
```
root@uos1050:/home# ./v4l2
VIDIOC_QUERYBUF: Invalid argument
```