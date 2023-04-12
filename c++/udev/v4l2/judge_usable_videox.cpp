#include <sys/ioctl.h>
#include <cstdio>
//#include <asm-generic/int-l64.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
//#include <asm/types.h>
#include <linux/videodev2.h>
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <sys/mman.h>
#include <stdlib.h>
using namespace std;

#define CAMERAS_DEVICES_ID_MAX 4    // /dev/video*最大设备个数
#define CLEAR(x) memset(&(x), 0, sizeof(x))

static int judge_usable_videox()
{
    char cam_path[20];
    struct v4l2_capability capability;
    int fd = -1;

    for (int i = 0; i < CAMERAS_DEVICES_ID_MAX; i++) {
        memset(cam_path, 0x00, 20);
        sprintf(cam_path, "/dev/video%d", i);

        printf("\n****************%s****************\n", cam_path);

        // 打开video
        fd = open(cam_path, O_RDWR);
        if (fd < 0) {
            printf("open camera path [ /dev/video%d ] failed.\n", i);
            continue;
        }
        
        // 显示所有支持的格式
        struct v4l2_fmtdesc fmtdesc;
        fmtdesc.index = 0;
        fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        printf("\nsupport format:\n");
        while (ioctl(fd, VIDIOC_ENUM_FMT, &fmtdesc) != -1) {
            printf("\t%d.%s\n", fmtdesc.index+1, fmtdesc.description);
            fmtdesc.index++;
        }
        if (fmtdesc.index == 0) {
            perror("no supportive format");
            continue;
        }

        // 显示当前帧的相关信息
        struct v4l2_format fmt;
        fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        ioctl(fd, VIDIOC_G_FMT, &fmt);
        printf("current data format information(default):\n\twidth:%d\n\theight:%d\n", \
            fmt.fmt.pix.width, fmt.fmt.pix.height);
        fmtdesc.index = 0;
        fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        while(ioctl(fd, VIDIOC_ENUM_FMT,&fmtdesc) != -1) {
            if(fmtdesc.pixelformat & fmt.fmt.pix.pixelformat) {
                printf("\tformat:%s\n", fmtdesc.description);
                break;
            }
            fmtdesc.index++;
        }
        
        // 检查是否支持某种帧格式
        fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_RGB32;
        if (ioctl(fd, VIDIOC_TRY_FMT, &fmt) == -1) {
            if (errno == EINVAL) {
                printf("not support format RGB32!\n");
            } else {
                printf("errno: %d, EINVAL: %d, %s\n", errno, EINVAL, strerror(errno)); 
            }
        }
        
        // 判断它是否具有VIDIOC_S_FMT能力
        CLEAR(fmt);
        fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        bool force_format = true;
        if (force_format) {
            fmt.fmt.pix.width       = 640;
            fmt.fmt.pix.height      = 480;
            fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
            fmt.fmt.pix.field       = V4L2_FIELD_INTERLACED;

            if (ioctl(fd, VIDIOC_S_FMT, &fmt) == -1) {
                perror("VIDIOC_S_FMT");
            }

            /* Note VIDIOC_S_FMT may change width and height. */
        } else {
            /* Preserve original settings as set by v4l2-ctl for example */
            if (ioctl(fd, VIDIOC_G_FMT, &fmt) == -1) {
                perror("VIDIOC_G_FMT");
            }
        }
        
        // 列举当前输入视频所支持的视频格式
        struct v4l2_input input;
        struct v4l2_standard standard;
        memset(&input, 0, sizeof(input));

        //首先获得当前输入的 index,注意只是 index，要获得具体的信息，就的调用列举操作
        if (ioctl(fd, VIDIOC_G_INPUT, &input.index) == -1) {
            perror("VIDIOC_G_INPUT");
            return -1;
        }

        //调用列举操作，获得 input.index 对应的输入的具体信息
        if (ioctl(fd, VIDIOC_ENUMINPUT, &input) == -1) {
            perror("VIDIOC_ENUM_INPUT");
            return -1;
        }

        printf("current input %s supports:\n", input.name);
        memset(&standard, 0, sizeof(standard));
        standard.index = 0;

        // 列举所有的所支持的 standard，如果 standard.id 与当前 input 的 input.std 有共同的
        // bit flag，意味着当前的输入支持这个 standard,这样将所有驱动所支持的 standard 列举一个
        // 遍，就可以找到该输入所支持的所有 standard 了。

        while (ioctl(fd, VIDIOC_ENUMSTD, &standard) == 0) {
            if (standard.id & input.std) {
                printf("%s\n", standard.name);
            }
            standard.index++;
        }

        /* EINVAL indicates the end of the enumeration, which cannot be empty unless this device falls under the USB exception. */
        if (errno != EINVAL || standard.index == 0) {
            perror("VIDIOC_ENUMSTD");
            //return -1;
        }
        
        // 查询当前输入支持什么标准
        v4l2_std_id std_id; //这个就是个64bit得数
        // VIDIOC_G_STD就是获得当前输入使用的standard，不过这里只是得到了该标准的id
        // 即flag，还没有得到其具体的属性信息，具体的属性信息要通过列举操作来得到。
        if (ioctl(fd, VIDIOC_G_STD, &std_id) == -1) { //获得了当前输入使用的standard
            // Note when VIDIOC_ENUMSTD always returns EINVAL this is no video device
            // or it falls under the USB exception, and VIDIOC_G_STD returning EINVAL
            // is no error.
            perror ("VIDIOC_G_STD");
            //return -1;
        }

        memset(&standard, 0, sizeof(standard));
        standard.index = 0; //从第一个开始列举

        // VIDIOC_ENUMSTD用来列举所支持的所有的video标准的信息，不过要先给standard
        // 结构的index域制定一个数值，所列举的标 准的信息属性包含在standard里面，
        // 如果我们所列举的标准和std_id有共同的bit，那么就意味着这个标准就是当前输
        // 入所使用的标准，这样我们就得到了当前输入使用的标准的属性信息

        while (ioctl(fd, VIDIOC_ENUMSTD, &standard) == 0) {
            if (standard.id & std_id) {
                printf("current video standard: %s\n", standard.name);
                //return -1;
            }
            standard.index++;
        }

        /* EINVAL indicates the end of the enumeration, which cannot be empty unless this device falls under the USB exception. */
        if (errno == EINVAL || standard.index == 0) {
            perror("VIDIOC_ENUMSTD");
            //return -1;
        }
        
        // 申请和管理缓冲区
        // 应用程序和设备有三种交换数据的方法，直接 read/write、内存映射(memory mapping)
        // 和用户指针。这里只讨论内存映射(memory mapping)。
        // 1.申请一个拥有四个缓冲帧的缓冲区
        struct v4l2_requestbuffers req; 
        req.count = 4;
        req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE; 
        req.memory = V4L2_MEMORY_MMAP; 
        ioctl(fd, VIDIOC_REQBUFS, &req);
        
        // 2.将四个已申请到的缓冲帧映射到应用程序，用buffers 指针记录。
        struct buffer {
            void* start;
            unsigned int length;

        } *buffers;
        buffers = (buffer*)calloc(req.count, sizeof(*buffers));
        if (!buffers) {
            // 映射
            fprintf(stderr, "out of memory\n");
            return -1;
        }

        for (unsigned int n_buffers = 0; n_buffers < req.count; n_buffers++) {
            struct v4l2_buffer buf;
            memset(&buf, 0, sizeof(buf));
            buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            buf.memory = V4L2_MEMORY_MMAP;
            buf.index = n_buffers;
            
            // 查询序号为n_buffers 的缓冲区，得到其起始物理地址和大小
            if (ioctl(fd, VIDIOC_QUERYBUF, &buf) == -1) {   // 获取缓冲帧的地址，长度：VIDIOC_QUERYBUF
                perror("VIDIOC_QUERYBUF");
                return -1;
            }
            buffers[n_buffers].length = buf.length;

            // 转换成相对地址 映射内存(这里的读写权限要和open地方权限一致，不然冲突)
            buffers[n_buffers].start = mmap(NULL, buf.length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, buf.m.offset);
            if (buffers[n_buffers].start == MAP_FAILED) {
                perror("mmap");
                return -1;
            }
        }
        
        // 3.把四个缓冲帧放入缓冲队列，并启动数据流
        enum v4l2_buf_type type;
        for (unsigned int j = 0; j < 4; j++) {  // 将缓冲帧放入队列
            struct v4l2_buffer buf;
            buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            buf.memory = V4L2_MEMORY_MMAP;
            buf.index = j;
            if (ioctl(fd, VIDIOC_QBUF, &buf) == -1) {
                perror("VIDIOC_QBUF");
                return -1;
            }
        }

        type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        ioctl(fd, VIDIOC_STREAMON, &type);
        // 这有个问题，这些buf看起来和前面申请的buf没什么关系，为什么呢?

#if 0
struct v4l2_buffer {
    u32 index;                  // buffer 序号
    enum v4l2_buf_type type;    // buffer 类型
    u32 bytesused;              // buffer 中已使用的字节数
    u32 flags;                  // 区分是MMAP 还是USERPTR
    enum v4l2_field field;
    struct timeval timestamp;   // 获取第一个字节时的系统时间
    struct v4l2_timecode timecode;
    u32 sequence;               // 队列中的序号
    enum v4l2_memory memory;    // IO 方式，被应用程序设置
    union m {
        u32 offset;             // 缓冲帧地址，只对MMAP 有效
        unsigned long userptr;
    };
    u32 length;                 // 缓冲帧长度
    u32 input;
    u32 reserved;
};
#endif

        // 4.获取一帧并处理
        struct v4l2_buffer buf;
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = 0;
        printf("buf.length = %d, buf.bytesused = %d\n", buf.length, buf.bytesused);
        if (ioctl(fd, VIDIOC_DQBUF, &buf) == -1) { // 从缓冲区取出一个缓冲帧(这里居然会对只能官方软件打开的阻塞)
            perror("VIDIOC_DQBUF");
            return -1;
        }
        // …………视频处理算法
        printf("buf.length = %d, buf.bytesused = %d\n", buf.length, buf.bytesused);
        // 重新放入缓存队列
        if (ioctl(fd, VIDIOC_QBUF, &buf) == -1) {
            perror("VIDIOC_QBUF");
             return -1;
        }
    }
    // 关闭视频设备
    close(fd);
    return 0;
}

int main()
{
    judge_usable_videox();
    return 0;
}
