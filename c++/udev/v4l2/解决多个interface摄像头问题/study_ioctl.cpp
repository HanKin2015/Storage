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
using namespace std;

#define CAMERAS_DEVICES_ID_MAX 4    // /dev/video*最大设备个数

/* 
这部分无法实现，需要在uvc_v4l2.c文件中实现.unlocked_ioctl = uvc_v4l2_ioctl函数
case VIDIOC_GET_BUSID_DEVICEID:
{
	struct v412_usb_device_info *usb_info = arg;
	usb_info->devnum = stream->dev->udev->devnum;
	usb_info->busnum = stream->dev->udev->bus->busnum;
	break;
}
*/
#define VIDIOC_GET_BUSID_DEVICEID _IOR('V',  98, struct v412_usb_device_info)
#define VIDIOC_USB_CONTROL_MSG _IOWR('V',  99, struct v412_usb_control_msg)
#define UVCIOC_GET_BUSID_DEVICEID _IOR('V',  0x22, struct v412_usb_device_info)
#define UVCIOC_USB_CONTROL_MSG _IOWR('V',  0x23, struct v412_usb_control_msg)
// struct needed usb information
struct v412_usb_device_info {
    __u32 devnum;
    __u32 busnum;
};
static int GetBusidDevid()
{
    printf("===== %s(%d) =====\n", __FUNCTION__, __LINE__);
    char cam_path[32] = {0};
    int fd = -1;
    struct v412_usb_device_info usb_device_info;
    memset(&usb_device_info, 0, sizeof(struct v412_usb_device_info));

    memset(cam_path, 0, sizeof(cam_path));
    
    for(int32_t i = 0; i < CAMERAS_DEVICES_ID_MAX; i++) {
        snprintf(cam_path, sizeof(cam_path), "/dev/video%d", i);
        int fd = open(cam_path, O_RDONLY);
        if (fd < 0) {
            printf("open %s failed %s.\n", cam_path, strerror(errno));
            continue;
        }
        
        printf("open file %s success.\n", cam_path);
        memset(&usb_device_info, 0, sizeof(struct v412_usb_device_info));
        //if (ioctl(fd, VIDIOC_GET_BUSID_DEVICEID, &usb_device_info) == -1) {
        printf("UVCIOC_GET_BUSID_DEVICEID\n");
        if (ioctl(fd, UVCIOC_GET_BUSID_DEVICEID, &usb_device_info) == -1) { // 内核自定义宏
            printf("video device(%s): get camera busid and deviceid failed.\n", cam_path);
            close(fd);
            fd = -1;
            continue;
        } else {
            printf("open file %s bus:%d dev:%d.\n", cam_path, usb_device_info.busnum, usb_device_info.devnum);
            close(fd);
            fd = -1;
            //break;
        }
    }
    return 0;
}

/*
struct v4l2_capability
{
    u8 driver[16];      // 驱动名字
    u8 card[32];        // 设备名字
    u8 bus_info[32];    // 设备在系统中的位置
    u32 version;        // 驱动版本号
    u32 capabilities;   // 设备支持的操作
    u32 reserved[4];    // 保留字段
};

获取摄像头个数
*/
static int GetNumberOfCameras()
{
    printf("===== %s(%d) =====\n", __FUNCTION__, __LINE__);
    char cam_path[20];
    int mNumberOfCameras = 0;
    struct v4l2_capability capability;

    for (int i = 0; i < CAMERAS_DEVICES_ID_MAX; i++) {
        memset(cam_path, 0x00, 20);
        sprintf(cam_path, "/dev/video%d", i);
        printf("\n*************************\nopening %s:\n", cam_path);
        int fd = open(cam_path, O_RDONLY);
        if (fd < 0) {
            printf("open camera path [ /dev/video%d ] failed.\n", i);
            continue;
        }

        memset(&capability, 0, sizeof(struct v4l2_capability));
        if (ioctl(fd, VIDIOC_QUERYCAP, &capability) < 0) {
            printf("video device(%s): query capability not supported.\n", cam_path);
            goto loop_continue;
        }

        if ((capability.capabilities
                & (V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_STREAMING))
                != (V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_STREAMING)) {
        } else {
            printf("Driver Info:            \
                    driver      : %s\n      \
                    card        : %s\n      \
                    bus_info    : %s\n      \
                    version     : 0x%x\n    \
                    capabilities: 0x%x.\n", \
                capability.driver, capability.card, capability.bus_info, capability.version, capability.capabilities);
            mNumberOfCameras++;
        }

loop_continue:
        if (fd > 0) {
            close(fd);
            fd = -1;
        }
        continue;
    }

    printf("there are %d cameras.\n", mNumberOfCameras);
    return mNumberOfCameras;
}

/*
unsigned char转char函数，好像有问题
*/
static void ConvertUnCharToChar(char* str, unsigned char* UnChar, int ucLen)
{
    int i = 0;
    for (i = 0; i < ucLen; i++)
    {
        //格式化输str,每unsigned char 转换字符占两位置%x写输%X写输
        sprintf(str + i * 2, "%02x", UnChar[i]);
    }
}
/*
难点1：unsigned char如何转char类型
难点2：unsigned char如何求长度
*/
static int GetPVidOfCameras()
{
    printf("===== %s(%d) =====\n", __FUNCTION__, __LINE__);
    char cam_path[20];
    struct v4l2_capability capability;

    for (int i = 0; i < CAMERAS_DEVICES_ID_MAX; i++) {
        memset(cam_path, 0x00, 20);
        sprintf(cam_path, "/dev/video%d", i);
        printf("\nopening %s:\n", cam_path);
        int fd = open(cam_path, O_RDONLY);
        if (fd < 0) {
            printf("open camera path [ /dev/video%d ] failed.\n", i);
            continue;
        }

        memset(&capability, 0, sizeof(struct v4l2_capability));
        if (ioctl(fd, VIDIOC_QUERYCAP, &capability) < 0) {
            printf("video device(%s): query capability not supported.\n", cam_path);
            goto loop_continue;
        }

        if ((capability.capabilities
                & (V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_STREAMING))
                != (V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_STREAMING)) {
        } else {
            //printf("\ndriver: %s\ncard: %s\nbus_info: %s\nversion: %d\ncapabilities: %d.\n", \
            //    capability.driver, capability.card, capability.bus_info, capability.version, capability.capabilities);
            char char_card[256];
            memset(char_card, 0, sizeof(char_card));
            ConvertUnCharToChar(char_card, capability.card, 32);    // 这里有问题，并且并不是所有摄像头都会在card写好pvid
            string str = char_card;
            printf("char_card: %s, str: %s.\n", char_card, str.c_str());
			auto pos = str.find(":");
            if (pos != std::string::npos) {
                string vid_str = str.substr(pos-4, 4);
                string pid_str = str.substr(pos+1, 4);
                int vid_value, pid_value;
                istringstream(vid_str) >> hex >> vid_value;
                istringstream(pid_str) >> hex >> pid_value;
                printf("vid: str: %s, value: %d; pid: str: %s, value: %d.\n", vid_str.c_str(), vid_value, pid_str.c_str(), pid_value);
            }
        }

loop_continue:
        if (fd > 0) {
            close(fd);
            fd = -1;
        }
        continue;
    }
    return 0;
}

/*
枚举出摄像头支持的视频格式
*/
static int GetInfoOfCameras()
{
    printf("===== %s(%d) =====\n", __FUNCTION__, __LINE__);
    char cam_path[20];
    struct v4l2_capability capability;
    int fd = -1;

    for (int i = 0; i < CAMERAS_DEVICES_ID_MAX; i++) {
        memset(cam_path, 0x00, 20);
        sprintf(cam_path, "/dev/video%d", i);
        printf("\n*************************\nopening %s:\n", cam_path);
        fd = open(cam_path, O_RDONLY);
        if (fd < 0) {
            printf("open camera path [ /dev/video%d ] failed.\n", i);
            continue;
        }

        // 1.查询设备属性
        memset(&capability, 0, sizeof(struct v4l2_capability));
        if (ioctl(fd, VIDIOC_QUERYCAP, &capability) < 0) {
            printf("video device(%s): query capability not supported.\n", cam_path);
            goto loop_continue;
        }

        if ((capability.capabilities
                & (V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_STREAMING))
                != (V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_STREAMING)) {
        } else {
            printf("Driver Info:\n          \
                    driver      : %s\n      \
                    card        : %s\n      \
                    bus_info    : %s\n      \
                    version     : 0x%x\n    \
                    capabilities: 0x%x.\n", \
                capability.driver, capability.card, capability.bus_info, capability.version, capability.capabilities);
        }
        // 2.显示所有支持帧格式
        struct v4l2_fmtdesc fmtdesc;
        fmtdesc.index = 0;
        fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        printf("Support format:\n");
        while (ioctl(fd, VIDIOC_ENUM_FMT, &fmtdesc) != -1) {
            printf("\t%d.%s\n",fmtdesc.index+1,fmtdesc.description);
            fmtdesc.index++;
        }

loop_continue:
        if (fd > 0) {
            close(fd);
            fd = -1;
        }
    }
    return 0;
}

int main()
{
    GetBusidDevid();
    GetNumberOfCameras();
    GetPVidOfCameras();
    GetInfoOfCameras();
    return 0;
}
