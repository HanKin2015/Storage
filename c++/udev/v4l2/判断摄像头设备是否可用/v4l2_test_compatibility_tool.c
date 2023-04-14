/**
* 文 件 名: v4l2_test_compatibility_tool.c
* 文件描述: v4l2视频工具，频繁的打开和关闭摄像头，兼容性测试
* 备    注: 使用docker交叉编译Android版本
*           source build/env.sh
*           lunch
*           编辑Android.mk文件
*           mm
*
*           gcc v4l2_test_compatibility_tool.c -lpthread
* 作    者: HanKin
* 创建日期: 2023.02.10
* 修改日期：2023.04.13
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/prctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <errno.h>
#include <time.h>
#include <stdarg.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/epoll.h>
#include <assert.h>
#include <inttypes.h>
#include <time.h>
#include <linux/usb/video.h>
#include <linux/videodev2.h>
#if __GLIBC__ == 2 && __GLIBC_MINOR__ < 30
#include <sys/syscall.h>
#define gettid() syscall(SYS_gettid)
#endif

#define bool  int
#define true  1
#define false 0

/**
 *日志级别
 **/
typedef enum {
	CAMERA_LOG_LEVEL_ERROR           = 0,    // 错误
	CAMERA_LOG_LEVEL_WARN	         = 1,    // 警告
	CAMERA_LOG_LEVEL_INFO            = 2,    // 信息
	CAMERA_LOG_LEVEL_DEBUG           = 3,    // 调试
	CAMERA_LOG_LEVEL_UNKNOWN         = 4     // 未知
} CAMERA_LOG_LEVEL;

FILE *g_log_fd = NULL;

/**
* 打印日志
*
* @param [in] level 日志级别
* @param [in] fmt 日志内容
*/
void camera_log_print(int level, const char* fmt, ...)
{
    assert(fmt);

    va_list al;
    char buffer[BUFSIZ] = { 0 };

    va_start(al, fmt);
    vsnprintf(buffer, BUFSIZ, fmt, al);
    va_end(al);
    
    const char *type_names[] = { "[ERROR]", "[WARN]", "[INFO]", "[DEBUG]",  "[UNKNOWN]" };
    time_t timep = time(NULL);
    struct tm *lt = localtime(&timep);
    char ntime[BUFSIZ] = {0};
    strftime(ntime, sizeof(ntime), "%Y-%m-%d %H:%M:%S", lt);
    
    char logmsg[BUFSIZ] = { 0 };
    snprintf(logmsg, BUFSIZ, "%s %s [%" PRIu64 ":%" PRIu64 "] %s\n",
        ntime, type_names[level], (uint64_t)getpid(),
        (uint64_t)gettid(), buffer);

    printf("%s", logmsg);
    if (g_log_fd) {
        fprintf(g_log_fd, "%s", logmsg);
    }
    return;
}

/**
 * 打印INFO日志
 * @param [in] fmt 日志信息格式
 **/
#define CAMERA_LOGI(fmt, ...)  do { \
    assert(fmt); \
	(void)camera_log_print(CAMERA_LOG_LEVEL_INFO, \
						fmt " {%s:%d}" , \
						## __VA_ARGS__, \
						__FUNCTION__, __LINE__); \
} while(0)
	
/**
 * 打印WARN日志
 * @param [in] fmt 日志信息格式
 **/
#define CAMERA_LOGW(fmt, ...)  do { \
    assert(fmt); \
	(void)camera_log_print(CAMERA_LOG_LEVEL_WARN, \
						fmt " {%s:%d}" , \
						## __VA_ARGS__, \
						__FUNCTION__, __LINE__); \
} while(0)
	
/**
 * 打印ERROR日志
 * @param [in] fmt 日志信息格式
 **/
#define CAMERA_LOGE(fmt, ...)  do { \
    assert(fmt); \
	(void)camera_log_print(CAMERA_LOG_LEVEL_ERROR, \
						fmt " {%s:%d}" , \
						## __VA_ARGS__, \
						__FUNCTION__, __LINE__); \
} while(0)

typedef struct uvc_message
{
    uint32_t    type;		//消息类型
    uint32_t    length;		//消息data长度
    uint32_t    id;  		//消息ID
    uint8_t     data[0];	
} uvc_message;

/*34个字节
struct uvc_streaming_control {
    __u16 bmHint;
    __u8 bFormatIndex;
    __u8 bFrameIndex;

    __u32 dwFrameInterval;
    __u16 wKeyFrameRate;
    __u16 wPFrameRate;
    __u16 wCompQuality;

    __u16 wCompWindowSize;
    __u16 wDelay;
    __u32 dwMaxVideoFrameSize;
    __u32 dwMaxPayloadTransferSize;

    __u32 dwClockFrequency;
    __u8 bmFramingInfo;
    __u8 bPreferedVersion;
    __u8 bMinVersion;

    __u8 bMaxVersion;
} __attribute__((__packed__));
*/

typedef struct uvcmsg_probe_data{
    uvc_message			msg_head;
    struct uvc_streaming_control	commit;
    /*
     * &brief video format sub_type
     *        yuy2 UVC_VS_FORMAT_UNCOMPRESSED 0x04
     *        mjpg UVC_VS_FORMAT_MJPEG 0x06
     */
    uint16_t    format; 
    uint16_t    width;
    uint16_t    height;

} uvcmsg_probe_data;

struct st_driver_buffer {
    void  *virt;        // 虚拟起始地址
    unsigned long phys; // 物理地址
    size_t length;      // 对齐后大小长度
};
typedef struct camera_ctx {
    char camera_dev[BUFSIZ];    // 视频设备节点/dev/video0
    int fd;

    //init buffer
    struct v4l2_requestbuffers reqbuf;  //请求信息
    struct st_driver_buffer*   buffers; //缓冲区信息
    struct v4l2_buffer         buf;

    //fmt and size
    struct v4l2_fmtdesc		fmt[4];
    struct v4l2_frmsizeenum	size[32];
    uint16_t				fmt_max;
    uint16_t				fmt_idx;
    uint16_t				size_max;
    uint16_t				size_idx;

    uint32_t is_start; //是否已经启动
} camctx;

/**
* 消息事件结构体
*/
typedef struct st_uvc_cli_event
{
	uint32_t type;	//事件状态
	int flag;
	uint32_t msg_len;	//消息长度
	uint8_t  msg[0];	//消息内容
} uvc_cli_event;

/**
* 消息事件 上下文
*
*/
struct st_uvc_cli_ctx {
    int device_id;
    camctx*			cam_ctx;    //uvc驱动 interface 

    int32_t			main_state; //工作状态
    pthread_t		main_thread;//工作线程id
    pthread_mutex_t mutex;      //状态锁
    bool is_running; //正在运行
    bool has_err;    //出错
    bool is_cfged;   //是否已经配置摄像头格式和分辨率

    int event_wfd;  //事件发送
    int event_rfd;  //事件接收

    int event_buff_len;     //消息缓冲区长度
    uint8_t *event_rbuff;   //消息读缓冲区
    uint8_t *event_wbuff;   //消息读缓冲区

    uint32_t fps;
    uint32_t bps;
    uint32_t encode_time;
    uint64_t last_time;
    uint64_t last_frame_time;
    uint32_t frame_interval;

    struct uvc_streaming_control		probe; 	//启动参数
};
typedef struct st_uvc_cli_ctx uvc_cli_ctx;

static int uvc_cli_do_start(uvc_cli_ctx *cli);
static int uvc_cli_do_probe(uvc_cli_ctx* cli, struct uvc_streaming_control probe);

// 初始化摄像头上下文
camctx *libcam_init()
{
    camctx* ctx = (camctx*)malloc(sizeof(camctx));
    if (!ctx){
        return NULL;
    }

    memset(ctx, 0, sizeof(camctx));
    ctx->fd = -1;

    return ctx;
}

// 释放摄像头上下文
void libcam_fini(camctx* ctx)
{
    free(ctx);
    ctx = NULL;
}

int libcam_setdev_byid(camctx* ctx, const uint8_t id)
{
    int len = snprintf(ctx->camera_dev, BUFSIZ, "/dev/video%d", id);
    assert(len > 0);
    return 0;
}

int libcam_open(camctx* ctx)
{
    assert(ctx);
    assert(ctx->fd == -1);

    ctx->fd = open(ctx->camera_dev, O_RDWR);
    assert(ctx->fd >= 0);
    return 0;
}

int libcam_close(camctx* ctx)
{
    assert(ctx);
    assert(ctx->fd >= 0);

    close(ctx->fd);
    ctx->fd = -1;
    return 0;
}

/**
* 设置线程名称
*
* @param [in] 摄像头id
*/
void camera_set_thread_name(int id) 
{
    char name[20] = {0};
    snprintf(name, 20, "%s%d", "camera", id);

    prctl(PR_SET_NAME, name);
}

/**
* 获取当前时间
*
* @return 返回ms
*/
uint64_t get_current_time()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ts.tv_sec * (1000ULL) + ts.tv_nsec / (1000000ULL));
}

//单个事件消息的最大长度
#define UVC_CLI_EVENT_LEN_MAX (8192)

//sock监听最大个数
#define UVC_SOCK_SIZE_MAX (4)

//sock监听的事件数量
#define UVC_EPOLL_EVENT_SIZE (4)

typedef enum em_event {
    UVC_CLI_READY,	
    UVC_CLI_START, //开启图片传输,并从CAMERA_READY进入CAMERA_RUN状态
    UVC_CLI_STOP,  //关闭图片传输，并从CAMERA_RUN退回CAMERA_READY状态
    UVC_CLI_EXIT,  //退出，直接退出工作县线程
    UVC_CLI_CMD,   //有命令，处理命令
    UVC_CLI_INFO,  //获取信息，只在CAMERA_INIT状态执行
    UVC_CLI_FAKE,  //有fake命令
    UVC_CLI_PROBE,  //有设置分辨率的请求，只在CAMERA_INIT状态执行
    UVC_CLI_PERF
} em_event;

typedef enum em_camera_state{
    CAMERA_INIT,	//初始状态
    CAMERA_READY,	//初始化内存之后进入
    CAMERA_RUN,		//开启图片传输后进入，关闭后退出
    CAMERA_EXIT,	//上层发起退出时进入
} em_camera_state;

// STREAMOFF失败时最大的尝试次数
#define UVC_STREAMOFF_TRYTIMES_MAX (10)

int libcam_getpic(camctx* ctx, struct st_driver_buffer* data)
{
    assert(ctx);
    int ret = 0;

    memset(&ctx->buf, 0, sizeof(struct v4l2_buffer));
    ctx->buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    ctx->buf.memory = V4L2_MEMORY_MMAP;

    if (ioctl(ctx->fd, VIDIOC_DQBUF, &ctx->buf) < 0) {
        CAMERA_LOGE("VIDIOC_DQBUF failed, err:%d(%s)", errno, strerror(errno));
        perror("VIDIOC_DQBUF");
        return -1;
    }

    data->virt = ctx->buffers[ctx->buf.index].virt;
    data->phys = ctx->buffers[ctx->buf.index].phys;
    data->length = ctx->buf.bytesused;

    return 0;
}

int libcam_putpic(camctx* ctx)
{
    CAMERA_LOGI("libcam_putpic");
    
    assert(ctx);

    if (ioctl(ctx->fd, VIDIOC_QBUF, &ctx->buf) < 0) {
        CAMERA_LOGE("VIDIOC_DQBUF failed, err:%d(%s)", errno, strerror(errno));
        perror("VIDIOC_QBUF");
        return -1;
    }

    return 0;
}

/**
*	@brief	[CAMERA_STOP]停止预览
*	@param	cli	uvc优化客户端环境变量
*	@return	0  成功 非0 失败
*/
static int uvc_cli_do_stop(uvc_cli_ctx *cli)
{
    assert(cli);
    CAMERA_LOGI("camera stop!");
    camctx* cam_ctx = cli->cam_ctx;

    enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    int try_times = 0;
    int i = 0;
    
    // 未启动或者已经关闭情况下
    if (!cam_ctx->is_start) {
        CAMERA_LOGW("camera do not start or close.");
        return 0;
    }
    
    do {
        if (ioctl(cam_ctx->fd, VIDIOC_STREAMOFF, &type) >= 0) {
            break;
        }
        
        try_times++;
        usleep(1000LL);
    } while (try_times < UVC_STREAMOFF_TRYTIMES_MAX);
    if (try_times == UVC_STREAMOFF_TRYTIMES_MAX) {
        CAMERA_LOGI("libcam:%p STREAMOFF failed, fd:%d, err:%d(%s)", cam_ctx, cam_ctx->fd, errno, strerror(errno));
    } else {
        cam_ctx->is_start = 0;
        CAMERA_LOGI("libcam:%p STREAMOFF success.", cam_ctx);
    }

    if (cam_ctx) {
        if (cam_ctx->reqbuf.count == 0 || cam_ctx->buffers == NULL) return 0;
        for (i = 0 ; i < cam_ctx->reqbuf.count ; i++) {
            if (cam_ctx->buffers[i].length > 0 && cam_ctx->buffers[i].virt != NULL) {
                munmap(cam_ctx->buffers[i].virt, cam_ctx->buffers[i].length);
            }
        }
        if (cam_ctx->buffers) {
            free(cam_ctx->buffers);
            cam_ctx->buffers = NULL;
        }
        
        memset(&cam_ctx->reqbuf, 0, sizeof(struct v4l2_requestbuffers));
        cam_ctx->reqbuf.count = 0;
        cam_ctx->reqbuf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        cam_ctx->reqbuf.memory = V4L2_MEMORY_MMAP;
        if (ioctl(cam_ctx->fd, VIDIOC_REQBUFS, &cam_ctx->reqbuf) < 0) {
            CAMERA_LOGI("failed to finibuff camera fd:%d err:%d(%s)",
            cam_ctx->fd, errno, strerror(errno));
        }
        
        cam_ctx->reqbuf.reserved[0] = 0;
        cam_ctx->reqbuf.reserved[1] = 0;
    }
    return 0;
}

/*
* 图片数据保存到本地
*/
static int save_image_to_local(int index, void *data, int length)
{
    const char *dir_name = "MJPEG";
    if (access(dir_name, F_OK) != 0) {
        char cmd[BUFSIZ] = { 0 };
        snprintf(cmd, sizeof(cmd), "mkdir -p %s", dir_name);
        pid_t status = system(cmd);
        if (!(status != -1 && WIFEXITED(status) && WEXITSTATUS(status) == 0)) {
            CAMERA_LOGE("mkdir path failed, strerror[%s]", strerror(errno));
            return -1;
        }
    }
    char buffer[256] = { 0 };
    snprintf(buffer, sizeof(buffer), "./%s/%d.mjpg", dir_name, index);
    //int file_fd = open(buffer, O_WRONLY | O_CREAT, 00700);
    int file_fd = open(buffer, O_RDWR | O_CREAT, 0644);   /*若打开失败则不存储该帧图像*/
    if (file_fd > 0) {
        CAMERA_LOGI("saving %d images", index);
        write(file_fd, data, length);
        close(file_fd);
    }
    return 0;
}

/**
*	@function	uvc_cli_proc
*	@brief	[CAMEAR_RUN]循环从uvc驱动获取VideoFrame
*	@param	cli	uvc优化客户端环境变量
*/
static void uvc_cli_proc(uvc_cli_ctx* cli)
{
    assert(cli);
    CAMERA_LOGI("camera capture image!");

    camctx* cam_ctx		= cli->cam_ctx;
    uint64_t last_time	=	0;
    uint64_t now_time	=	0;
    uint64_t diff_time	=	0;
    uint8_t* dstdata	=	NULL;
    uint32_t dstsize	=	0;
    int ret = 0;

    struct st_driver_buffer data;
    memset(&data, 0, sizeof(struct st_driver_buffer));

    last_time = get_current_time();
    // 获取原始数据
    ret = libcam_getpic(cam_ctx, &data);
    if (ret < 0) {
        CAMERA_LOGE("getpic failed ret:%d", ret);
        goto END;
    }

    dstsize = data.length;
    CAMERA_LOGI("handle pic size:%d", dstsize);

    now_time = get_current_time();
    if (dstsize > 0) {
        cli->fps++;
        cli->bps += dstsize;
        cli->encode_time += (int)(now_time - last_time);
    }
    
    save_image_to_local(cam_ctx->buf.index, data.virt, data.length);
    
    libcam_putpic(cam_ctx);

END:
    now_time = get_current_time();
    // 由ms转us进行比较
    diff_time = (now_time - cli->last_frame_time)*1000;

    if(diff_time < cli->frame_interval) {
        // 如果一帧图片所需时间小于所规定的时间，则休眠。用于控制帧率
        usleep((cli->frame_interval - diff_time));
    }

    cli->last_frame_time = get_current_time();
}

/**
* 接收len长度的数据到buff
*
* @param [in] fd 事件句柄
* @param [in] buff 缓冲区
* @param [in] len 要接收的数据长度
*
* @return 接收到的数据长度
*/
static int uvc_cli_recv_data(int fd, uint8_t* buff, int len)
{
    assert(fd != -1);
    assert(buff && len > 0);

    int ret = 0;
    int try_times = 0;

    int left = len;
    uint8_t* pos = buff;

    do {
        ret = read(fd, buff, len);
        if (ret < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR) {
                try_times++;
                continue;
            }
            break;
        } else if (ret == 0) {
            try_times++;
            continue;
        }
        
        left -= ret;
        pos += ret;
    } while(left > 0 && try_times < 100);

    return (len - left);
}

/**
* 接收事件event
*
* @param [in] fd 事件句柄
* @param [in] event 事件
*
* @return 0:接收成功 非0：接收失败
*/
static int uvc_cli_recv_event(uvc_cli_ctx*	cli, int fd, uvc_cli_event* event)
{
    assert(cli);
    assert(fd != -1);
    assert(event);

    int len = sizeof(uvc_cli_event);
    uint8_t* buff = (uint8_t*)event;
    int ret = uvc_cli_recv_data(fd, buff, len);
    if (ret != len) {
        CAMERA_LOGE("uvc client recv event header failed, errno:%d.", errno);
        return -1;
    }

    if (event->msg_len > 0) {
        buff += len;
        ret = uvc_cli_recv_data(fd, buff, event->msg_len);
        if (ret != event->msg_len) {
            CAMERA_LOGE("uvc client recv event data failed, errno:%d.", errno);
            return -1;
        }
    }

    return 0;
}

/**
* 事件类型转换为字符串
* 
* @param [in] event 事件类型
*/
const char* uvc_event2str(em_event event)
{
    switch(event)
    {
        case UVC_CLI_READY:
            return "UVC_CLI_READY";
        case UVC_CLI_START:
            return "UVC_CLI_START";
        case UVC_CLI_STOP:
            return "UVC_CLI_STOP";	
        case UVC_CLI_EXIT:
            return "UVC_CLI_EXIT";
        case UVC_CLI_CMD:
            return "UVC_CLI_CMD";
        case UVC_CLI_INFO:
            return "UVC_CLI_INFO";
        case UVC_CLI_FAKE:
            return "UVC_CLI_FAKE";
        case UVC_CLI_PROBE:
            return "UVC_CLI_PROBE";
        case UVC_CLI_PERF:
            return "UVC_CLI_PERF";
        default:
            return "UVC_CLI_UNEXPECTED";
    }
}

/**
* 工作状态类型转换为字符串
* 
* @param [in] state 工作状态
*/
const char* uvc_state2str(em_camera_state state)
{
    switch(state)
    {
        case CAMERA_INIT:
            return "CAMERA_INIT";
        case CAMERA_READY:
            return "CAMERA_READY";
        case CAMERA_RUN:
            return "CAMERA_RUN";	
        case CAMERA_EXIT:
            return "CAMERA_EXIT";
        default:
            return "UVC_CLI_UNEXPECTED";
    }
}

/*
*	@function is_vaild_event
*	@breif 事件是否需要处理
*
*/
static bool is_valid_event(uvc_cli_ctx* cli, em_event ev)
{
    assert(cli);

    em_camera_state state = cli->main_state;
    CAMERA_LOGI("current work state:(%d)%s", state, uvc_state2str(state));
    switch(ev){
        case UVC_CLI_READY:
            return true;

        case UVC_CLI_START://需要已经init过buff
            if(state != CAMERA_READY)
                return false;

            break;

        case UVC_CLI_STOP://需要处于RUN状态
            if(state != CAMERA_RUN)
                return false;

            break;

        case UVC_CLI_CMD:
            if(state != CAMERA_READY && state != CAMERA_RUN)
                return false;

            break;

        case UVC_CLI_FAKE:
            if(state != CAMERA_READY && state != CAMERA_RUN)
                return false;

            break;

        case UVC_CLI_PROBE:
        case UVC_CLI_INFO:
            if(state != CAMERA_READY)
                return false;

            break;

        case UVC_CLI_PERF:
        case UVC_CLI_EXIT:
            return true;

        default:
            return false;
    }

    return true;
}

/*
*	@function uvc_cli_deal_event
*	@breif 事件处理函数
*/
static int uvc_cli_deal_event(uvc_cli_ctx* cli, uvc_cli_event* event)
{
    int ret = 0;
    uvc_message* msg = NULL;
    uint32_t msg_len = 0;
    uvcmsg_probe_data* req = NULL;
    
    em_event ev	= (em_event)event->type;
    CAMERA_LOGI("get event:(%d)%s.", ev, uvc_event2str(ev));
    
    if (!is_valid_event(cli, ev)) {
        CAMERA_LOGI("get unexpected event:(%d)%s.", ev, uvc_event2str(ev));
        return 0;
    }

    switch (ev) {
    case UVC_CLI_START:
        if (!cli->is_cfged) {
            CAMERA_LOGE("uvc's configure had not inited:%d.", ret);
            return -1;
        }

        ret = uvc_cli_do_start(cli);
        if (ret == 0) {
            cli->main_state = CAMERA_RUN;
        }
        break;

    case UVC_CLI_STOP:
        (void)uvc_cli_do_stop(cli);
        cli->main_state = CAMERA_READY;
        break;

    case UVC_CLI_PROBE:
        msg = (uvc_message*)event->msg;
        msg_len = event->msg_len;
        req = (uvcmsg_probe_data*)msg;
        CAMERA_LOGI("msg->type %d msg->length %d msg_len %d.", msg->type, msg->length, msg_len);
        ret = uvc_cli_do_probe(cli, req->commit);
        if (ret != 0) {
            cli->is_cfged = false;
            CAMERA_LOGE("probe failed :%d", ret);
        } else {
            cli->is_cfged = true;
        }

        break;

    case UVC_CLI_EXIT:
        (void)uvc_cli_do_stop(cli);
        cli->main_state = CAMERA_EXIT;
        break;
    default:
        CAMERA_LOGE("unexpected camera event:(%d)%s", ev, uvc_event2str(ev));
        break;
    }

    return ret;
}

/**
* 子线程(用于获取设备图像的线程)的主函数
*
* @param [in] pri 传入线程的指针
* 
* @return 
*/
static void* uvc_cli_main_loop(void* pri)
{
    CAMERA_LOGI("uvc_cli_main_loop");
    
    uvc_cli_ctx* cli = (uvc_cli_ctx *)pri;
    assert(cli);

    camera_set_thread_name(cli->device_id);
    camctx* cam_ctx = cli->cam_ctx;

    // 非阻塞模式还有问题，先屏蔽该接口
    //uvc_sock_set_blocking(cam_ctx->fd, false);

    struct epoll_event ev, events[UVC_EPOLL_EVENT_SIZE];
    memset(&ev, 0, sizeof(struct epoll_event));
    memset(&events, 0, sizeof(struct epoll_event)*UVC_EPOLL_EVENT_SIZE);

    int epfd = epoll_create(UVC_SOCK_SIZE_MAX); 
    assert(epfd != -1);

    ev.data.fd = cli->event_rfd;
    ev.events = EPOLLIN;
    
    int i = 0, num = 0;
    uvc_cli_event *event = NULL;
    
    int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, cli->event_rfd, &ev);
    if (ret == -1) {
        CAMERA_LOGI("uvc epoll add fd:%d failed, errno:%d.", cli->event_rfd, errno);
        goto FUNC_END;
    }

    cli->has_err = false;
    cli->main_state = CAMERA_READY;

    CAMERA_LOGI("cli->is_running: %d, cli->has_err: %d", cli->is_running, cli->has_err);
    while (cli->is_running && !cli->has_err) {
        num = epoll_wait(epfd, events, UVC_EPOLL_EVENT_SIZE, 30*1000);
        CAMERA_LOGI("num: %d", num);
        if (num < 0) {
            if (errno == EINTR) {
                continue;
            }
            CAMERA_LOGI("uvc epoll wait failed, errno:%d.", errno);
            break;
        } else if (num == 0) {
            continue;
        }
        
        for (i = 0; i < num; i++) {
            //处理消息事件
            if (events[i].data.fd == cli->event_rfd) {
                event = (uvc_cli_event*)cli->event_rbuff;

                if (uvc_cli_recv_event(cli, cli->event_rfd, event) != 0) {
                    CAMERA_LOGI("uvc epoll recv event failed.");
                    cli->has_err = true;
                    break;
                } 

                ret = uvc_cli_deal_event(cli, event);
                if (ret < 0) {
                    CAMERA_LOGI("uvc deal event:(%d) failed.", event->type);
                    continue;
                }

                if (event->type == UVC_CLI_START) {
                    ev.data.fd = cam_ctx->fd;
                    ev.events = EPOLLIN;
                    
                    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, cam_ctx->fd, &ev);
                } else if (event->type == UVC_CLI_STOP) {
                    ret = epoll_ctl(epfd, EPOLL_CTL_DEL, cam_ctx->fd, NULL);
                }
                
                // 不需要退出，仅打日志方便定位问题
                if (ret < 0) {
                    CAMERA_LOGI("uvc epoll  fd:%d add/del failed, errno:%d.", cam_ctx->fd, errno);
                }
                
                CAMERA_LOGI("type: %d", event->type);
                memset(cli->event_rbuff, 0, cli->event_buff_len);
                continue;
            } 
            
            // 读取uvc数据
            if (events[i].data.fd == cam_ctx->fd) {
                uvc_cli_proc(cli);
            }
        }
    }

FUNC_END:
    close(epfd);
    if (cli->main_state == CAMERA_RUN) {
        (void)uvc_cli_do_stop(cli);
        cli->main_state = CAMERA_EXIT;
    }   

    CAMERA_LOGI("camera thread client:%p loop exit.", cli);
    return NULL;
}

/**
* 通知camera线程事件
*
* @param cli 客户端对象
* @param event 事件消息
*/
static int uvc_cli_write_data(int fd, uint8_t* data, int len)
{
    assert(fd != -1);
    assert(data);
    assert(len > 0);

    int ret = 0;
    int left = len;
    int try_times = 0;

    do {
        ret = write(fd, data, left);
        if (ret < 0) {
            if (errno == EAGAIN || errno == EINTR){
                try_times++;
                continue;
            }

            CAMERA_LOGE("uvc client:%d post event failed,errno:%d.", fd, errno);
            break;
        } else if (ret == 0) {
            try_times++;
            continue;
        }

        data += ret;
        left -= ret;
    } while (left > 0 && try_times < 100);

    return (len - left);
}

/**
* 通知camera线程事件
*
* @param cli 客户端对象
* @param event 事件消息
*/
static void uvc_cli_send_event(uvc_cli_ctx* cli, int type, uint8_t* data, int len)
{
    assert(cli);
    assert(len < UVC_CLI_EVENT_LEN_MAX);

    int ret = 0;
    uvc_cli_event* event = (uvc_cli_event*)cli->event_wbuff;    // 这个event_wbuff只是一个分配空间的作用
    event->type = type;
    event->flag = 0;
    event->msg_len = len;
    CAMERA_LOGI("copy data to msg, len %d.", len);
    memcpy(event->msg, data, len);

    ret = uvc_cli_write_data(cli->event_wfd, cli->event_wbuff, (sizeof(uvc_cli_event)+len));
    if (ret != (sizeof(uvc_cli_event)+len)) {
        CAMERA_LOGE("uvc client post event:%d len:%d ret:%d.", type, (sizeof(uvc_cli_event)+len), ret);
    }
    
    return;
}

/**
* uvc client 打开camera，启动线程抓数据
*
* @param [in] uvc_cli 
*/
int uvc_cli_open(uvc_cli_ctx* uvc_cli)
{
    assert(uvc_cli);
    
    // camctx初始化	
    uvc_cli->cam_ctx = libcam_init();
    assert(uvc_cli->cam_ctx);

    // 绑定id
    int ret = libcam_setdev_byid(uvc_cli->cam_ctx, uvc_cli->device_id);
    if (ret != 0) {
        CAMERA_LOGI("libcam:%d setdev failed, ret:%d.", uvc_cli->device_id, ret);
        free(uvc_cli->cam_ctx);
        return -1;
    }

    // 打开设备
    ret = libcam_open(uvc_cli->cam_ctx);
    if (ret != 0) {
        CAMERA_LOGI("libcam:%d open failed，ret:%d.", uvc_cli->device_id, ret);
        free(uvc_cli->cam_ctx);
        return -1;
    }

    // 设置初始事件，并启动工作线程
    uvc_cli->is_running = true;
    
    /*线程id 一般为NULL 线程执行函数 函数传入的参数*/
    ret = pthread_create(&uvc_cli->main_thread, NULL, uvc_cli_main_loop, (void *)uvc_cli);	
    if (ret != 0) {
        uvc_cli->is_running = false;
        CAMERA_LOGI("create pthread failed:%d errno:%d(%s)", ret, errno, strerror(errno));
        libcam_close(uvc_cli->cam_ctx);
        free(uvc_cli->cam_ctx);
        return -1;
    }
    
    return 0;
}

/**
* uvc client 关闭camera，停止线程抓数据
*
* @param [in] uvc_cli
*/
void uvc_cli_close(uvc_cli_ctx* uvc_cli)
{
    if (!uvc_cli) {
        return;
    }

    CAMERA_LOGI("uvc_cli_close ......begin.");

    uvc_cli->is_running = false;
    
    uvc_cli_send_event(uvc_cli, UVC_CLI_EXIT, NULL, 0);
    
    if (uvc_cli->main_thread) {
        pthread_join(uvc_cli->main_thread, NULL);
        uvc_cli->main_thread = 0;
    }

    pthread_mutex_lock(&uvc_cli->mutex);

    if (uvc_cli->cam_ctx) {
        libcam_close(uvc_cli->cam_ctx);
        libcam_fini(uvc_cli->cam_ctx);
        uvc_cli->cam_ctx = NULL;
    }

    pthread_mutex_unlock(&uvc_cli->mutex);

    CAMERA_LOGI("uvc_cli_close ......end.");
}

/**
* uvc client 释放
*
* @param [in] uvc_cli
*/
void uvc_cli_deinit(uvc_cli_ctx* uvc_cli)
{
    if (!uvc_cli) {
        return;
    }

    CAMERA_LOGI("uvc_cli deinit cli:%p, cam_ctx:%p.", uvc_cli, uvc_cli->cam_ctx);

    uvc_cli_close(uvc_cli);

    if (uvc_cli->event_rfd != -1) {
        close(uvc_cli->event_rfd);
        uvc_cli->event_rfd = -1;
    }

    if (uvc_cli->event_wfd != -1) {
        close(uvc_cli->event_wfd);
        uvc_cli->event_wfd = -1;
    }

    if (uvc_cli->event_rbuff) {
        free(uvc_cli->event_rbuff);
        uvc_cli->event_rbuff = NULL;
    }

    if (uvc_cli->event_wbuff) {
        free(uvc_cli->event_wbuff);
        uvc_cli->event_wbuff = NULL;
    }
    #if UVC_USE_LOCAL_YUV
    if (uvc_cli->yuv2) {
        free(uvc_cli->yuv2);
        uvc_cli->yuv2 = NULL;
    }
    #endif

    pthread_mutex_destroy(&uvc_cli->mutex);

    free(uvc_cli);
}

/**
*  获取摄像头格式
*  @param	cli	uvc优化客户端环境变量
*  @param   省去了查询设备的能力这一步
*  @return  0成功 非0 失败
*/
int libcam_getfmt(camctx* ctx)
{
    assert(ctx);
    assert(ctx->fd >= 0);

    ctx->fmt_max = 0;
    struct v4l2_fmtdesc* fmt;
    do {
        if (ctx->fmt_max > 0) {
            int i = ctx->fmt_max - 1;
            CAMERA_LOGI("[%d]idx:%d pixelformat:%d", i, ctx->fmt[i].index, ctx->fmt[i].pixelformat);
        }
        
        ctx->fmt[ctx->fmt_max].index	=	ctx->fmt_max;
        ctx->fmt[ctx->fmt_max].type		=	V4L2_BUF_TYPE_VIDEO_CAPTURE;
        fmt = &ctx->fmt[ctx->fmt_max];
        ctx->fmt_max++;
    } while (ioctl(ctx->fd, VIDIOC_ENUM_FMT, fmt) >= 0);

    ctx->fmt_max--;//最后一次获取失败，必须减掉
    if (ctx->fmt_max != 0) {
        return 0;
    }

    return -1;
}

/**
*  获取摄像头分辨率
*  @param	cli	uvc优化客户端环境变量
*  @return  0成功 非0 失败
*/
int libcam_getframesizes(camctx* ctx)
{
    assert(ctx);
    if (ctx->fd == -1 || ctx->fmt_idx >= ctx->fmt_max) {
        CAMERA_LOGI("libcam_getsize invalid fmt fd:%d id:%d max:%d.", ctx->fd, ctx->fmt_idx, ctx->fmt_max);
        ctx->size_max = 0;
        return -1;
    }

    int ret = 0;
    ctx->size_max = 0;
    struct v4l2_frmsizeenum* size;
    do {
        if (ctx->size_max > 0) {
            int i = ctx->size_max - 1;
            CAMERA_LOGI("[%d]idx:%d, width:%d, height:%d", i, ctx->size[i].index, ctx->size[i].discrete.width, ctx->size[i].discrete.height);
        }
        
        ctx->size[ctx->size_max].index			= ctx->size_max;
        ctx->size[ctx->size_max].pixel_format	= ctx->fmt[ctx->fmt_idx].pixelformat;
        size = &ctx->size[ctx->size_max];
        ctx->size_max++;
    } while ((ret = ioctl(ctx->fd, VIDIOC_ENUM_FRAMESIZES, size)) >= 0);
    ctx->size_max--; // 最后一次获取失败，必须减掉
    if (ctx->size_max == 0) {
        return -1;
    }
    return 0;
}

/**
*  设置摄像头分辨率和格式
*  @param	cli	uvc优化客户端环境变量
*  @return  0成功 非0 失败
*/
int libcam_setprop(camctx* ctx)
{
    assert(ctx);
    CAMERA_LOGI("setprop");

    struct v4l2_format format;
    memset(&format, 0, sizeof(struct v4l2_format));

    format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    format.fmt.pix.pixelformat = ctx->fmt[ctx->fmt_idx].pixelformat;
    format.fmt.pix.width = ctx->size[ctx->size_idx].discrete.width;
    format.fmt.pix.height = ctx->size[ctx->size_idx].discrete.height;

    if (ioctl(ctx->fd, VIDIOC_S_FMT, &format) < 0) {
        CAMERA_LOGI("set format failed[width:%d, heigth:%d] errno:%d(%s).",
            format.fmt.pix.width, format.fmt.pix.height, errno, strerror(errno));
        return -1;
    }
    return 0;
}

/**
*  处理设置分辨率的请求
*  @param	cli	uvc优化客户端环境变量
*  @param   probe 
*  @return  0成功 非0 失败
*/
static int uvc_cli_do_probe(uvc_cli_ctx* cli, struct uvc_streaming_control probe)
{
    assert(cli);
    cli->probe = probe;

    CAMERA_LOGI("camera init format:%d frame:%d", cli->probe.bFormatIndex, cli->probe.bFrameIndex);

    camctx*	 cam_ctx = cli->cam_ctx;

    int ret = libcam_getfmt(cam_ctx);
    assert(!ret);
    int id = cli->probe.bFormatIndex;
    assert(id != 0 && cam_ctx->fmt_max && id <= cam_ctx->fmt_max);
    cam_ctx->fmt_idx = id - 1; // 索引下标比实际下标小1(数组索引下标从0开始，枚举index值从1开始)

    ret = libcam_getframesizes(cam_ctx);
    assert(!ret);
    id = cli->probe.bFrameIndex;
    assert(id !=0 && cam_ctx->fmt_max && id <= cam_ctx->size_max);
    cam_ctx->size_idx = id - 1; // 索引下标比实际下标小1(数组索引下标从0开始，枚举index值从1开始)
    
    CAMERA_LOGI("libcam:%p dev:%s, fd:%d", cam_ctx, cam_ctx->camera_dev, cam_ctx->fd);
	CAMERA_LOGI("[fmt]max:%d idx:%d", cam_ctx->fmt_max, cam_ctx->fmt_idx);
    CAMERA_LOGI("[size]max:%d idx:%d", cam_ctx->size_max, cam_ctx->size_idx);
    
    ret = libcam_setprop(cam_ctx);
    assert(!ret);
    return ret;
}

int libcam_finibuff(camctx* ctx)
{
    assert(ctx->reqbuf.count > 0);
    assert(ctx->buffers);
    
    int i = 0;
    for (i = 0 ; i < ctx->reqbuf.count ; i++){
        if (ctx->buffers[i].length > 0 && ctx->buffers[i].virt != NULL)
            munmap(ctx->buffers[i].virt, ctx->buffers[i].length);
    }
    free(ctx->buffers);
    ctx->buffers = NULL;

    //set count to zero, to free privileges
    memset(&ctx->reqbuf, 0, sizeof(struct v4l2_requestbuffers));
    ctx->reqbuf.count = 0;
    ctx->reqbuf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    ctx->reqbuf.memory = V4L2_MEMORY_MMAP;
    if (ioctl(ctx->fd, VIDIOC_REQBUFS, &ctx->reqbuf) < 0 ) {
        CAMERA_LOGE("failed to finibuff camera fd:%d err:%d(%s)",
            ctx->fd, errno, strerror(errno));
        return -1;
    }

    ctx->reqbuf.reserved[0] = 0;
    ctx->reqbuf.reserved[1] = 0;

    return 0;
}

static int libcam_initbuff(camctx* ctx, uint32_t buf_count) 
{
    CAMERA_LOGI("libcam_initbuff");
    
    assert(ctx);
    assert(buf_count > 0);

    uint32_t	i	= 0;
    int			ret	= 0;
    struct v4l2_buffer buf;

    // 申请内核VideoFrame缓冲区
    ctx->reqbuf.count		= buf_count;
    ctx->reqbuf.type		= V4L2_BUF_TYPE_VIDEO_CAPTURE;
    ctx->reqbuf.memory		= V4L2_MEMORY_MMAP;
    ctx->reqbuf.reserved[0] = 0;
    ctx->reqbuf.reserved[1] = 0;

    CAMERA_LOGI("init uvc buff, count:%d", buf_count);
    if (ioctl(ctx->fd, VIDIOC_REQBUFS, &ctx->reqbuf) < 0) {
        CAMERA_LOGE("REQBUFS count %d failed: ret:%d errno:%d(%s)", 
            buf_count, ret, errno, strerror(errno));
        goto failed;
    }
    if (ctx->reqbuf.count == 0) {
        CAMERA_LOGE("REQBUFS count %d success. but return count zero");
        ret = -1;
        goto failed;
    }
    if (ctx->reqbuf.count != buf_count) {
        CAMERA_LOGI("REQBUFS buf %d, but just get buf %d", buf_count, ctx->reqbuf.count);
    }

    // 申请buf内存映射内核地址
    ctx->buffers = (struct st_driver_buffer *)calloc(ctx->reqbuf.count, sizeof (struct st_driver_buffer));
    if (!ctx->buffers) {
        CAMERA_LOGE("uvc calloc failed, count:%d.", ctx->reqbuf.count);
        goto failed;
    }

    // 获取内核地址并映射
    for (i = 0 ; i < ctx->reqbuf.count ; i++) {
        memset(&buf, 0, sizeof(struct v4l2_buffer));
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = i;
        if (ioctl(ctx->fd, VIDIOC_QUERYBUF, &buf) < 0) {
            CAMERA_LOGE("QUERYBUF buf[%d] failed: ret:%d errno:%d(%s)", 
                    i, ret, errno, strerror(errno));
            goto failed;
        }
        
        ctx->buffers[i].length = buf.length;
        CAMERA_LOGI("init uvc buff[%d] len:%d", i, buf.length);
        ctx->buffers[i].virt = mmap(NULL, buf.length, PROT_READ|PROT_WRITE,
            MAP_SHARED, ctx->fd, buf.m.offset);
        if (MAP_FAILED == ctx->buffers[i].virt) {
            CAMERA_LOGE("mmap buffer[%d] failed: errno:%d(%s)", 
                    i, errno, strerror(errno));
            ret = -1;
            goto failed;
        }
        
        CAMERA_LOGI("uvc buff[%d] virt:0x%p phys:0x%x len:%d.", i, ctx->buffers[i].virt, ctx->buffers[i].phys, ctx->buffers[i].length);
    }

    for (i = 0 ; i < ctx->reqbuf.count ; i++){
        memset(&buf, 0, sizeof(struct v4l2_buffer));
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = i;
        
        if (ioctl(ctx->fd, VIDIOC_QBUF, &buf) < 0) {
            CAMERA_LOGE("QBUF buf[%d] failed: ret:%d errno:%d(%s)", 
                    i, ret, errno, strerror(errno));
            goto failed;
        }
    }

    CAMERA_LOGI("uvc buff init success.");
    return 0;

failed:
    libcam_finibuff(ctx);
    return -1;
}

int libcam_start(camctx* ctx)
{
    assert(ctx);

    enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (ioctl(ctx->fd, VIDIOC_STREAMON, &type) < 0) {
        CAMERA_LOGE("libcam:%p STREAMON failed, fd:%d err:%d(%s)",
            ctx, ctx->fd, errno, strerror(errno));
        return -1;
    }
    
    ctx->is_start = 1;
    CAMERA_LOGI("libcam:%p STREAMON success.", ctx);
    return 0;
}

/**
* 	@function	uvc_cli_do_init
*	@brief	[CAMERA_INIT]初始化预览环境
*	@param 	cli	uvc优化客户端环境变量
*	@return 0  成功 非0 失败
*/
static int uvc_cli_do_start(uvc_cli_ctx *cli)
{
    assert(cli);   
    CAMERA_LOGI("camera init format:%d frame:%d", cli->probe.bFormatIndex, cli->probe.bFrameIndex);

    int	ret = 0;
    camctx*	cam_ctx	=	cli->cam_ctx;

    // 获取width和height
    uint32_t width	=	cam_ctx->size[cam_ctx->size_idx].discrete.width;
    uint32_t height	=	cam_ctx->size[cam_ctx->size_idx].discrete.height; 
    
    // 获取格式
    uint32_t format = cam_ctx->fmt[cam_ctx->fmt_idx].pixelformat; 
    CAMERA_LOGI("INIT frame[%d %d] fmt:%d.", width, height, format);  

    // 初始化空间(说明会保存5张照片在本地)
    ret = libcam_initbuff(cam_ctx, 5);
    if (ret != 0) {
        CAMERA_LOGE("initbuff failed %d", ret);
        goto failed;
    }	

    CAMERA_LOGI("camera start format:%d Frame:%d width:%d height:%d", cli->probe.bFormatIndex, cli->probe.bFrameIndex, width, height);
    ret = libcam_start(cam_ctx);
    if (ret != 0) {
        CAMERA_LOGE("Faild to start camera %p", cli);
        goto failed;
    }

    cli->frame_interval = 1000000/30;   // 即1s有30帧
    cli->last_frame_time = 0;
    cli->last_time = get_current_time();

    return ret;
    
failed:
    if (cli->cam_ctx) {
        ret = libcam_finibuff(cli->cam_ctx);
    }
    return ret;
}

/**
* uvc client 初始化
*
* @param [in] camera_id 摄像头id
*
* @return NULL:初始化失败 非NULL:指针
*/
uvc_cli_ctx* uvc_cli_init(uint32_t camera_id)
{
    uvc_cli_ctx *uvc_cli = (uvc_cli_ctx *)malloc(sizeof(uvc_cli_ctx));
    assert(uvc_cli);
    memset(uvc_cli, 0, sizeof(uvc_cli_ctx));
    
    uvc_cli->device_id = camera_id;
    
    //Fix me 暂时不考虑SSL连接
    int fds[2];
    if (pipe(fds) == -1) {
        CAMERA_LOGE("uvc_cli pipe open failed， errno:%d.", errno);
        free(uvc_cli);
        uvc_cli = NULL;
        return NULL;
    }
    uvc_cli->event_rfd = fds[0];
    uvc_cli->event_wfd = fds[1];
    
    uvc_cli->event_buff_len = sizeof(struct st_uvc_cli_event) + 8192;
    uvc_cli->event_rbuff = (uint8_t *)malloc(uvc_cli->event_buff_len);
    uvc_cli->event_wbuff = (uint8_t *)malloc(uvc_cli->event_buff_len);
    memset(uvc_cli->event_rbuff, 0, uvc_cli->event_buff_len);
    memset(uvc_cli->event_wbuff, 0, uvc_cli->event_buff_len);
    return uvc_cli;
}

#define MESSAGE_HEAD_LEN (sizeof(uvc_message))
int main(int argc, char *argv[])
{
    // 初始化日志(a模式只能进行写操作，而a+模式可以进行读写操作)
    g_log_fd = fopen("./v4l2_test_compatibility_tool.log", "a+");
    if (g_log_fd == NULL) {
        perror("fopen log file failed.\n");
        return -1;
    }
    
    // 1、初始化摄像头客户端指针变量
    uvc_cli_ctx *uvc_cli = uvc_cli_init(0); assert(uvc_cli);
    
    // 2、打开摄像头
    int ret = uvc_cli_open(uvc_cli); assert(!ret);
    
    struct uvc_streaming_control probe;
    probe.bFormatIndex = 1;
    probe.bFrameIndex = 1;
    //ret = uvc_cli_do_probe(uvc_cli, probe); assert(!ret);
    
    //ret = uvc_cli_do_start(uvc_cli); assert(!ret);

    long long count = 0;
    int i = 0, j = 0;
    uvc_message* msg = (uvc_message*)malloc(1024);
    uint8_t data[40] = {0x01, 0x0, 0x01, 0x03, 0x15, 0x16, 0x05, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x20, 0x00, 0x00, 0x96, 0x0, 0x0, 0x80, 0x0a, 0x0, 0x0, 0x33, 0x51, 0xb2, 0x7f, 0x0, 0x0, 0x76, 0x6e, 0x04, 0x00, 0xa0, 0x00, 0x78, 0x00};
    em_event events[3] = {UVC_CLI_PROBE, UVC_CLI_START, UVC_CLI_STOP};  // 一次摄像头打开关闭需要三个步骤
    while (1) {
        count++;
        CAMERA_LOGW("current count %lld.", count);
        
        #if 0
        if (count > 3) {
            CAMERA_LOGW("current count %lld, stop demo.", count); 
            break;      // 停止程序
        }
        #endif
        
        for (i = 0; i < 3; i++) {   // 切换三种分辨率
            memset(msg, 0, 1024);
            msg->type   = UVC_CLI_PROBE;
            msg->length = 40;
            msg->id     = 0;
            
            //CAMERA_LOGI("MESSAGE_HEAD_LEN %d.", MESSAGE_HEAD_LEN);
            
            data[3] = 0x3;
            if (i == 1) {   // 切换成320*240分辨率
                data[3] = 0x6;
            }
            memcpy(msg->data, data, 40);
            for (j = 0; j < 3; j++) {
                uvc_cli_send_event(uvc_cli, events[j], (uint8_t *)msg, MESSAGE_HEAD_LEN+msg->length);
                sleep(1);
            }
        }
        sleep(1);
    }
    
    /*
    uvc_cli_deinit -- free uvc_cli
                   |--libcam_close
                   |--libcam_fini free cam_ctx
    */
    uvc_cli_deinit(uvc_cli);
    return 0;
}
/*
[admin@HanKin ~]$ ll
total 115876
-rw-r--r-- 1 admin admin    49630 Apr 11 15:20 1.mjpg
---S--sr-- 1 admin admin   349120 Apr 13 15:18 3.mjpg
drwxrwxr-x 2 admin admin     4096 Mar 23 14:45 android4

居然还会有图片拖曳不出去问题，修改3.mjpg的文件权限为0644即可。
*/