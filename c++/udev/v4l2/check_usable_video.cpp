#include <sys/ioctl.h>
#include <cstdio>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/videodev2.h>
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <sys/mman.h>
#include <stdlib.h>
#include <assert.h>
using namespace std;

#define CLEAR(x) memset(&(x), 0, sizeof(x))
#define BUF_FRAME_CNT 4
#define BUF_MAX_LEN 256
int fd = -1;
char video_path[BUF_MAX_LEN];

struct buffer {
    void   *start;
    size_t  length;
} *buffers;

static void errno_exit(const char *s)
{
    fprintf(stderr, "%d: %s error %d, %s\n", __LINE__, s, errno, strerror(errno));
    exit(EXIT_FAILURE);
}

static int xioctl(int fh, int request, void *arg)
{
    int r;

    do {
        r = ioctl(fh, request, arg);
    } while (-1 == r && EINTR == errno);

    return r;
}

static void init_mmap()
{
    struct v4l2_requestbuffers req;

    CLEAR(req);

    req.count = BUF_FRAME_CNT;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;

    if (-1 == xioctl(fd, VIDIOC_REQBUFS, &req)) {
        if (EINVAL == errno) {
            fprintf(stderr, "%s does not support "
                 "memory mapping\n", video_path);
            exit(EXIT_FAILURE);
        } else {
            errno_exit("VIDIOC_REQBUFS");
        }
    }

    if (req.count < 2) {
        fprintf(stderr, "Insufficient buffer memory on %s\n", video_path);
        exit(EXIT_FAILURE);
    }

    buffers = (buffer *)calloc(req.count, sizeof(*buffers));

    if (!buffers) {
        fprintf(stderr, "Out of memory\n");
        exit(EXIT_FAILURE);
    }

    for (unsigned int i = 0; i < req.count; i++) {
        struct v4l2_buffer buf;

        CLEAR(buf);

        buf.type        = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory      = V4L2_MEMORY_MMAP;
        buf.index       = i;

        if (-1 == xioctl(fd, VIDIOC_QUERYBUF, &buf)) {
            errno_exit("VIDIOC_QUERYBUF");
        }

        buffers[i].length = buf.length;
        buffers[i].start =
            mmap(NULL /* start anywhere */,
              buf.length,
              PROT_READ | PROT_WRITE /* required */,
              MAP_SHARED /* recommended */,
              fd, buf.m.offset);

        if (MAP_FAILED == buffers[i].start)
            errno_exit("mmap");
    }
}

static int read_frame()
{
    struct v4l2_buffer buf;
    CLEAR(buf);

    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;
    printf("buf.length = %d, buf.bytesused = %d\n", buf.length, buf.bytesused);
    if (-1 == xioctl(fd, VIDIOC_DQBUF, &buf)) {
        switch (errno) {
        case EAGAIN:
            return -1;

        case EIO:
            /* Could ignore EIO, see spec. */

            /* fall through */

        default:
            errno_exit("VIDIOC_DQBUF");
        }
    }
    printf("buf.length = %d, buf.bytesused = %d\n", buf.length, buf.bytesused);
    assert(buf.index < BUF_FRAME_CNT);

    //process_image(buffers[buf.index].start, buf.bytesused);

    if (-1 == xioctl(fd, VIDIOC_QBUF, &buf)) {
        errno_exit("VIDIOC_QBUF");
    }
    return 0;
}

static int mainloop()
{
    unsigned int count = 70;

    while (count-- > 0) {
        for (;;) {
            fd_set fds;
            struct timeval tv;
            int r;

            FD_ZERO(&fds);
            FD_SET(fd, &fds);

            /* Timeout. */
            tv.tv_sec = 2;
            tv.tv_usec = 0;

            r = select(fd + 1, &fds, NULL, NULL, &tv);

            if (-1 == r) {
                if (EINTR == errno)
                    continue;
                errno_exit("select");
            }

            if (0 == r) {
                fprintf(stderr, "select timeout\n");
                //exit(EXIT_FAILURE);
                return -1;
            }

            if (read_frame() == 0)
                return 0;
            /* EAGAIN - continue select loop. */
        }
    }
    return 0;
}

//VIDIOC_STREAMON
static void start_capturing()
{
    enum v4l2_buf_type type;
    for (int i = 0; i < BUF_FRAME_CNT; ++i) {
        struct v4l2_buffer buf;

        CLEAR(buf);
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = i;

        if (-1 == xioctl(fd, VIDIOC_QBUF, &buf)) {
            errno_exit("VIDIOC_QBUF");
        }
    }
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (-1 == xioctl(fd, VIDIOC_STREAMON, &type)) {
        errno_exit("VIDIOC_STREAMON");
    }
}

static int init_device()
{
    struct v4l2_capability cap;
    struct v4l2_cropcap cropcap;
    struct v4l2_crop crop;
    struct v4l2_format fmt;
    unsigned int min;

    if (-1 == xioctl(fd, VIDIOC_QUERYCAP, &cap)) {
        if (EINVAL == errno) {
            fprintf(stderr, "%s is no V4L2 device\n",
                 video_path);
            exit(EXIT_FAILURE);
        } else {
            errno_exit("VIDIOC_QUERYCAP");
        }
    }

    if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)) {
        fprintf(stderr, "%s is no video capture device\n",
             video_path);
        exit(EXIT_FAILURE);
    }

    if (!(cap.capabilities & V4L2_CAP_STREAMING)) {
        fprintf(stderr, "%s does not support streaming i/o\n",
             video_path);
        exit(EXIT_FAILURE);
    }


    /* Select video input, video standard and tune here. */
    CLEAR(cropcap);

    cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    if (0 == xioctl(fd, VIDIOC_CROPCAP, &cropcap)) {
        crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        crop.c = cropcap.defrect; /* reset to default */

        if (-1 == xioctl(fd, VIDIOC_S_CROP, &crop)) {
            switch (errno) {
            case EINVAL:
                /* Cropping not supported. */
                break;
            default:
                /* Errors ignored. */
                break;
            }
        }
    } else {
        /* Errors ignored. */
    }


    CLEAR(fmt);

    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    /* Preserve original settings as set by v4l2-ctl for example */
    if (-1 == xioctl(fd, VIDIOC_G_FMT, &fmt)) {
        perror("VIDIOC_G_FMT");
        return -1;
        //errno_exit("VIDIOC_G_FMT");
    }

    /* Buggy driver paranoia. */
    min = fmt.fmt.pix.width * 2;
    if (fmt.fmt.pix.bytesperline < min)
        fmt.fmt.pix.bytesperline = min;
    min = fmt.fmt.pix.bytesperline * fmt.fmt.pix.height;
    if (fmt.fmt.pix.sizeimage < min)
        fmt.fmt.pix.sizeimage = min;

    init_mmap();
    return 0;
}

//释放申请的内存
static void uninit_device()
{
    for (int i = 0; i < BUF_FRAME_CNT; ++i) {
        if (-1 == munmap(buffers[i].start, buffers[i].length)) {
            errno_exit("munmap");
        }
    }
    free(buffers);
}

//VIDIOC_STREAMOFF
static void stop_capturing()
{
    enum v4l2_buf_type type;
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (-1 == xioctl(fd, VIDIOC_STREAMOFF, &type)) {
        errno_exit("VIDIOC_STREAMOFF");
    }
}

static int check_usable_videox()
{
    struct v4l2_capability capability;

    for (int i = 0; ; i++) {
        memset(video_path, 0, BUF_MAX_LEN);
        sprintf(video_path, "/dev/video%d", i);

        printf("\n****************%s****************\n", video_path);

        // 打开video
        fd = open(video_path, O_RDWR);
        if (fd < 0) {
            printf("open camera path [ /dev/video%d ] failed.\n", i);
            break;
        }
        
        int ret = init_device();
        if (ret != 0) {
            printf("/dev/video%d can't be open\n", i);
            goto FAILED;
        }
        start_capturing();
        ret = mainloop();
        if (ret == 0) {
            printf("/dev/video%d can be open\n", i);
        } else {
            printf("/dev/video%d can't be open\n", i);
        }
        stop_capturing();
        uninit_device();
FAILED:
        close(fd);
        fd = -1;
    }
    return 0;
}

int main()
{
    check_usable_videox();
    return 0;
}