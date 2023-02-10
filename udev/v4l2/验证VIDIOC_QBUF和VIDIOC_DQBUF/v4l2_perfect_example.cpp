/**
* 文 件 名: v4l2_perfect_example.cpp
* 文件描述: 来源于https://mp.weixin.qq.com/s/bbh9uY5q0CrqXDCc8rzLQA
* 备    注: 翻车没有找到close函数定义，缺少unistd.h头文件，居然两次获取的代码不一样
* 作    者: HanKin
* 创建日期: 2023.02.10
* 修改日期：2023.02.10
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
#include <assert.h>
#include <linux/videodev2.h>

struct USER_BUFFER {
    void *start;
    unsigned int length;
}*usr_buf;
const int buf_num = 4;
int fd = -1;

static int init_camera(const char *video_dev_node)
{
    assert(video_dev_node);
    
    // 1.打开视频设备节点
    fd = open(video_dev_node, O_RDWR);
    if (fd < 0) {
        perror("open /dev/video0");
        exit(EXIT_FAILURE);
    }
    
    // 2.查询设备的能力
    struct v4l2_capability cap;
    if (ioctl(fd, VIDIOC_QUERYCAP, &cap) < 0) {
        perror("VIDIOC_QUERYCAP");
        exit(EXIT_FAILURE);
    }
    printf("driver : %s\n", cap.driver);
    printf("device : %s\n", cap.card);
    printf("bus : %s\n", cap.bus_info);
    printf("version : %d\n", cap.version);
    if (cap.capabilities & V4L2_BUF_TYPE_VIDEO_CAPTURE) {   /*判断是否为视频捕获设备*/
        if (cap.capabilities & V4L2_CAP_STREAMING) {        /*判断是否支持视频流捕获*/
            printf("support capture\n");
        } else {
            printf("unsupport capture\n");
        }
    } else {
        perror("V4L2_BUF_TYPE_VIDEO_CAPTURE");
        exit(EXIT_FAILURE);
    }
    
    // 3.获取摄像头支持的格式，并进行像素格式设置
    struct v4l2_fmtdesc fmtdesc;
    fmtdesc.index = 0;
    fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    while (ioctl(fd, VIDIOC_ENUM_FMT, &fmtdesc) < 0) {
        printf("\t%d.%s\n", fmtdesc.index + 1, fmtdesc.description);
        fmtdesc.index++;
    }
    
    struct v4l2_format fmt;
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE; /*摄像头缓冲*/
    fmt.fmt.pix.width = 640;
    fmt.fmt.pix.height = 480;
    //fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
    //fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUV422P;
    if (ioctl(fd, VIDIOC_S_FMT, &fmt) < 0) {
        perror("VIDIOC_S_FMT");
        printf("set format:V4L2_PIX_FMT_MJPEG failed\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}

// 4.内存映射到用户空间并进行队列操作
int mmap_v4l2_buffer()
{
    usr_buf = (struct USER_BUFFER *)calloc(buf_num, sizeof(struct USER_BUFFER));
    if (!usr_buf) {
        perror("calloc frame buffer");
        exit(EXIT_FAILURE);
    }
    
    struct v4l2_requestbuffers req;
    req.count = buf_num;                    // 帧缓存数量
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE; // 视频捕获缓冲区类型（必须永远是V4L2_BUF_TYPE_VIDEO_CAPTURE）
    req.memory = V4L2_MEMORY_MMAP;          // 内存映射方式（V4L2_MEMORY_MMAP 或 V4L2_MEMORY_USERPTR）
    if (ioctl(fd, VIDIOC_REQBUFS, &req) < 0) {
        perror("VIDIOC_REQBUFS");
        exit(EXIT_FAILURE);
    }

    /*映射内核缓存区到用户空间缓冲区*/
    for (unsigned int i = 0; i < buf_num; i++) {
        /*查询内核缓冲区信息*/
        struct v4l2_buffer v4l2_buf;
        memset(&v4l2_buf, 0, sizeof(v4l2_buf));
        v4l2_buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        v4l2_buf.memory = V4L2_MEMORY_MMAP;
        v4l2_buf.index = i;
        if (ioctl(fd, VIDIOC_QUERYBUF, &v4l2_buf) < 0) {
            perror("VIDIOC_QUERYBUF");
            exit(EXIT_FAILURE);
        }
    
        usr_buf[i].length = v4l2_buf.length;
        usr_buf[i].start = (char *)mmap(NULL, v4l2_buf.length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, v4l2_buf.m.offset);
        if (usr_buf[i].start == MAP_FAILED) { /*若映射失败，打印错误*/
            perror("mmap");
            exit(EXIT_FAILURE);
        } else {     /*若映射成功则将内核缓冲区入队*/
            if (ioctl(fd, VIDIOC_QBUF, &v4l2_buf) < 0) {
                perror("VIDIOC_QBUF");
                exit(EXIT_FAILURE);
            }
        }
    }
    return 0;
}

// 5.开启摄像头获取视频流
int camera_stream_on()
{
    enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (ioctl(fd, VIDIOC_STREAMON, &type) < 0) {
        perror("VIDIOC_STREAMON");
        exit(EXIT_FAILURE);
    }
    return 0;
}

// 6.从缓冲区中把视频数据取出
int write_video_frame()
{
    struct v4l2_buffer v4l2_buf;
    memset(&v4l2_buf, 0, sizeof(v4l2_buf));
    v4l2_buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    v4l2_buf.memory = V4L2_MEMORY_MMAP;
    if (ioctl(fd, VIDIOC_DQBUF, &v4l2_buf) < 0) {   /*内核缓冲区出队列*/
        perror("VIDIOC_DQBUF");
        exit(EXIT_FAILURE);
    }
    /*图片数据保存到本地*/
    const char *dir_name = "MJPEG";
    if (access(dir_name, F_OK) != 0) {
        char cmd[BUFSIZ] = { 0 };
        snprintf(cmd, sizeof(cmd), "mkdir -p %s", dir_name);
        pid_t status = system(cmd);
        if (!(status != -1 && WIFEXITED(status) && WEXITSTATUS(status) == 0)) {
            printf("mkdir path failed, strerror[%s]", strerror(errno));
            return -1;
        }
    }
    char buffer[256] = { 0 };
    snprintf(buffer, sizeof(buffer), "./%s/%d.mjpg", dir_name, v4l2_buf.index);
    //int file_fd = open(buffer, O_WRONLY | O_CREAT, 00700);
    int file_fd = open(buffer, O_RDWR | O_CREAT);   /*若打开失败则不存储该帧图像*/
    if (file_fd > 0) {
        printf("saving %d images\n", v4l2_buf.index);
        write(file_fd, usr_buf[v4l2_buf.index].start, v4l2_buf.bytesused);
        close(file_fd);
    }
    
    if (ioctl(fd, VIDIOC_QBUF, &v4l2_buf) < 0) {    /*缓冲区重新入队*/
        perror("VIDIOC_QBUF");
        exit(EXIT_FAILURE);
    }
    return v4l2_buf.index;
}

// 7.关闭摄像头获取流
int camera_stream_off()
{
    /*关闭视频流*/
    enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (ioctl(fd, VIDIOC_STREAMOFF, &type) < 0) {
        perror("VIDIOC_STREAMOFF");
        exit(EXIT_FAILURE);
    }
    return 0;
}

// 8.解除映射缓冲区
int unmap_v4l2_bufffer()
{
    /*解除内核缓冲区到用户缓冲区的映射*/
    for (unsigned int i =0; i < buf_num; i++) {
        int ret = munmap(usr_buf[i].start, usr_buf[i].length);
        if (ret < 0) {
            perror("munmap");
            return -1;
        }
    }
    free(usr_buf);  /*释放用户缓冲区内存*/
    return 0;
}

// 9.释放所有的资源
void release_camera()
{
    close(fd);
}

int main(int argc, char *argv[])
{
    int ret = init_camera("/dev/video0");
    if (ret < 0) {
        printf("init_camera error\n");
        return -1;
    }
    
    ret = mmap_v4l2_buffer();
    if (ret < 0) {
        printf("mmap_v4l2_buffer error\n");
        return -1;
    }
    
    ret = camera_stream_on();
    if (ret < 0) {
        printf("camera_stream_on error\n");
        return -1;
    }
    
    for (int i = 0; i < 20; i++) {
        write_video_frame();
    }
    
    ret = camera_stream_off();
    if (ret < 0) {
        printf("camera_stream_off error\n");
        return -1;
    }
    
    ret = unmap_v4l2_bufffer();
    if (ret < 0) {
        printf("unmap_v4l2_bufffer error\n");
        return -1;
    }
    
    release_camera();
    
    return 0;
}
/*
root@UOS10500001:/home/hankin# g++ v4l2.cpp -g -o v4l2
root@UOS10500001:/home/hankin# ./v4l2
driver : uvcvideo
device : Lanseyaoji: Lanseyaoji
bus : usb-0000:00:18.7-15
version : 267098
support capture
saving 0 images
saving 1 images
saving 2 images
saving 3 images
saving 0 images
saving 1 images
saving 2 images
saving 3 images
saving 0 images
saving 1 images
saving 2 images
saving 3 images
saving 0 images
saving 1 images
saving 2 images
saving 3 images
saving 0 images
saving 1 images
saving 2 images
saving 3 images
root@UOS10500001:/home/hankin# ls -l MJPEG/
总用量 2400
---------- 1 hankin hankin 614400 2月  10 10:59 0.mjpg
---------- 1 hankin hankin 614400 2月  10 10:59 1.mjpg
---------- 1 hankin hankin 614400 2月  10 10:59 2.mjpg
---------- 1 hankin hankin 614400 2月  10 10:59 3.mjpg

该图片不能直接打开，修改后缀为jpg也不行，还是通过YUVviewerPlus.exe软件进行打开查看。
*/
