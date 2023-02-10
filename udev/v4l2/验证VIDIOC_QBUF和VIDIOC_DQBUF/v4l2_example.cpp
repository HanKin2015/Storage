/**
* 文 件 名: v4l2_example.cpp
* 文件描述: 来源于chatGPT，https://chat.forchange.cn/
* 备    注: 翻车没有找到close函数定义，缺少unistd.h头文件，居然两次获取的代码不一样
* 作    者: HanKin
* 创建日期: 2023.02.09
* 修改日期：2023.02.09
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <errno.h>
#include <linux/videodev2.h>

int main(int argc, char *argv[])
{
    int fd = -1;
    struct v4l2_capability cap;
    struct v4l2_format fmt;
    struct v4l2_buffer buf;
    void *mem = NULL;
    unsigned int i = 0;
    // 打开视频设备
    fd = open("/dev/video0", O_RDWR);
    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    // 获取设备属性
    if (ioctl(fd, VIDIOC_QUERYCAP, &cap) < 0) {
        perror("VIDIOC_QUERYCAP");
        exit(EXIT_FAILURE);
    }
    // 设置视频格式
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width = 640;
    fmt.fmt.pix.height = 480;
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
    fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
    if (ioctl(fd, VIDIOC_S_FMT, &fmt) < 0) {
        perror("VIDIOC_S_FMT");
        exit(EXIT_FAILURE);
    }
    // 申请缓冲区
    struct v4l2_requestbuffers req;
    req.count = 4;                          // 缓存数量，也就是说在缓存队列里保持多少张照片
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE; // 数据流类型，必须永远是V4L2_BUF_TYPE_VIDEO_CAPTURE
    req.memory = V4L2_MEMORY_MMAP;          // V4L2_MEMORY_MMAP 或 V4L2_MEMORY_USERPTR
    ioctl(fd, VIDIOC_REQBUFS, &req);
    struct buffer {
        void *start;
        unsigned int length;
    } *buffers;
    buffers = (struct buffer*)calloc(req.count, sizeof(*buffers));
    printf("req.count * sizeof(*buffers) = %lu\n", req.count * sizeof(*buffers));
    printf("fmt.fmt.pix.sizeimage = %d\n", fmt.fmt.pix.sizeimage);
    //mem = malloc(fmt.fmt.pix.sizeimage);
    if (!buffers) {
        perror("calloc");
        exit(EXIT_FAILURE);
    }
    // 映射缓冲区（把VIDIOC_REQBUFS中分配的数据缓存转换成物理地址）
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;
    buf.index = 0;
    if (ioctl(fd, VIDIOC_QUERYBUF, &buf) < 0) {
        perror("VIDIOC_QUERYBUF");
        exit(EXIT_FAILURE);
    }
    
    mem = mmap(NULL, buf.length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, buf.m.offset);
    if (mem == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    // 开始获取视频帧
    if (ioctl(fd, VIDIOC_STREAMON, &buf.type) < 0) {
        perror("VIDIOC_STREAMON");
        exit(EXIT_FAILURE);
    }
    // 读取视频帧
    for (i = 0; i < 10; i++) {
        // 如果只删除这个会在ioctl(fd, VIDIOC_DQBUF, &buf)函数中卡住
        if (ioctl(fd, VIDIOC_QBUF, &buf) < 0) {
            perror("VIDIOC_QBUF");
            exit(EXIT_FAILURE);
        }
        printf("length = %d, bytesused = %d\n", buf.length, buf.bytesused);
        // 如果只删除这个会报错VIDIOC_QBUF: Invalid argument
        if (ioctl(fd, VIDIOC_DQBUF, &buf) < 0) {
            perror("VIDIOC_DQBUF");
            exit(EXIT_FAILURE);
        }
        printf("length = %d, bytesused = %d\n", buf.length, buf.bytesused);
        printf("Got frame %u(MISSING)\n", i);
        
        // 图片数据保存到本地
        const char *dir_path = "YUYV";
        if (access(dir_path, F_OK) != 0) {
            char cmd[BUFSIZ] = { 0 };
            snprintf(cmd, sizeof(cmd), "mkdir -p %s", dir_path);
            pid_t status = system(cmd);
            if (!(status != -1 && WIFEXITED(status) && WEXITSTATUS(status) == 0)) {
                printf("mkdir path failed, strerror[%s]", strerror(errno));
                return -1;
            }
        }
        char path[BUFSIZ] = { 0 };
        snprintf(path, sizeof(path), "./%s/yuyv%d.yuv", dir_path, i);
        int fd_yuyv = open(path, O_WRONLY|O_CREAT, 00700);
        int ret = write(fd_yuyv, buffers[buf.index].start, buffers[buf.index].length);
        close(fd_yuyv);
    }
    // 停止获取视频帧
    if (ioctl(fd, VIDIOC_STREAMOFF, &buf.type) < 0) {
        perror("VIDIOC_STREAMOFF");
        exit(EXIT_FAILURE);
    }
    // 释放缓冲区
    munmap(mem, buf.length);
    // 释放
    free(buffers);
    // 关闭视频设备
    close(fd);
    return 0;
}