/*****************************************************
 * 文件名：GetCameraInfo.cpp
 * 文件描述：linux下使用v4l2编程查询摄像头设备信息，主要是枚举所有分辨率
 * 编写人  ：HanKin
 * 编写日期：2021.08.03
 * 修改日期：2021.08.03
*****************************************************/
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>                      // 下面四个头文件是linux系统编程特有的
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include <linux/videodev2.h>                // 操作摄像头设备

#define CAMERAS_DEVICES_ID_MAX 4

int main(int argc, char **argv)
{	
	int ret, i, j;
	int fd;
    char cam_path[20];

    for (int index = 0; index < CAMERAS_DEVICES_ID_MAX; index++) {
        memset(cam_path, 0x00, 20);
        sprintf(cam_path, "/dev/video%d", index);
        printf("=================\nopening %s:\n", cam_path);
        
        /* 打开摄像头设备 */ 
        fd = open(cam_path, O_RDWR);       // 注意查看摄像头设备名
        if (fd == -1) {
            perror("open %s", cam_path);
            return -1;
        }

        /* 查询打开的设备是否属于摄像头：设备video不一定是摄像头*/
        struct v4l2_capability cap;
        ret = ioctl(fd, VIDIOC_QUERYCAP, &cap);
        if (fd == -1) {
            perror("ioctl VIDIOC_QUERYCAP");
            close(fd);
        }
        if (cap.capabilities & V4L2_CAP_VIDEO_CAPTURE) {
            /* 如果为摄像头设备则打印摄像头驱动名字 */
            printf("Driver    Name: %s\n", cap.driver);         
        } else {
            printf("open file is not video\n");
            close(fd);
            return -2;
        }

        /* 查询摄像头可捕捉的图片类型，VIDIOC_ENUM_FMT: 枚举摄像头帧格式 */
        struct v4l2_fmtdesc fmt;
        fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE; // 指定需要枚举的类型
        for (i = 0; ; i++) {                    // 有可能摄像头支持的图片格式不止一种 
            fmt.index = i;
            ret = ioctl(fd, VIDIOC_ENUM_FMT, &fmt);
            if (ret == -1) {                      // 获取所有格式完成
                perror("VIDIOC_ENUM_FMT failed");
                break;
            }
            
            /* 打印摄像头图片格式 */
            printf("Picture Format: %s\n", fmt.description);    

            /* 查询该图像格式所支持的分辨率 */	
            struct v4l2_frmsizeenum frmsize;
            frmsize.pixel_format = fmt.pixelformat;
            for (j = 0; ; j++) {                 //　该格式支持分辨率不止一种
                frmsize.index = j;
                ret = ioctl(fd, VIDIOC_ENUM_FRAMESIZES, &frmsize);
                if (ret == -1) {                  // 获取所有图片分辨率完成
                    perror("VIDIOC_ENUM_FRAMESIZES failed");
                    break;
                }
                
                /* 打印图片分辨率 */
                printf("solution[%d]: %dx%d\n",
                        j+1, frmsize.discrete.width,frmsize.discrete.height);
            }
        }
        
loop_continue:
        if (fd > 0) {
            close(fd);
            fd = -1;
        }
    }
    return 0;
}
