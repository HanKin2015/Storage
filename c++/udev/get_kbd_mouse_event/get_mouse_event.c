/*******************************************************************************
* 文 件 名: get_mouse_event.c
* 文件描述: 获取鼠标数据(不能用来获取键盘数据)
* 备    注: https://blog.csdn.net/wabil/article/details/132382577
* 作    者: HanKin
* 创建日期: 2023.12.18
* 修改日期：2023.12.18
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/
#include <X11/Xlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>
#include <string.h>
//LDFLAGS := -lX11

int GetDisplayInfo(int *screen_width, int *screen_height)
{
    Display *display = XOpenDisplay(NULL);
    if (display == NULL) {
        printf("Error: cannot open display\n");
        return 1;
    }
    int screen_num = DefaultScreen(display);
    Screen *screen = ScreenOfDisplay(display, screen_num);
    *screen_width = WidthOfScreen(screen);
    *screen_height = HeightOfScreen(screen);
    printf("Screen size: %dx%d pixels\n", WidthOfScreen(screen), HeightOfScreen(screen));
    printf("Screen resolution: %dx%d dpi\n", (int) (WidthOfScreen(screen) * 25.4 / DisplayWidthMM(display, screen_num)), 
                                             (int) (HeightOfScreen(screen) * 25.4 / DisplayHeightMM(display, screen_num)));
    XCloseDisplay(display);
    
    return 0;
}
 
int get_xy(int fd,struct input_event ts,int *x,int *y)
{
    static int nCnt = 0;
    read(fd,&ts,sizeof(ts));
    if(ts.type == EV_ABS && ts.code == ABS_X) {
        *x = ts.value;
        nCnt = (nCnt+1)%3;
        return nCnt;
    }
    if(ts.type == EV_ABS && ts.code == ABS_Y)
    {
        *y = ts.value;
        nCnt = (nCnt+1)%3;
        return nCnt;
    }

    return 0;
}
 
 
int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("param is invalid, use event number please\n");
        return -1;
    }
    char mouse_event_path[BUFSIZ] = "/dev/input/event";
    strncat(mouse_event_path, argv[1], strlen(argv[1]));
    printf("mouse event path: %s\n", mouse_event_path);
    
    int fd = -1, ret = -1;
    struct input_event ev;
    int data_size = sizeof(struct input_event);

    // 第1步：打开设备文件[需要权限运行]
    fd = open(mouse_event_path, O_RDONLY);
    if (fd < 0) {
        perror("open,error");
        return -1;
    }
    printf("mouse test [%s], data size=%lu.\n", mouse_event_path, sizeof(struct input_event));

    int screen_width = 0;
    int screen_height = 0;
    if( GetDisplayInfo(&screen_width,&screen_height) > 0) {
        perror("get display info，error");
        return -2;
    }

    while (1) {
        static int raw_x=0;
        static int raw_y=0;
        int tmp =0;

        tmp = get_xy(fd,ev, &raw_x, &raw_y);
        if(tmp==2)
        {
            int curr_x = 0;
            int curr_y = 0;
            curr_x = raw_x * screen_width / 0xFFFF;
            curr_y = raw_y * screen_height / 0xFFFF;    // 使用export DISPLAY=:0读取数据失败
            printf("mousePos: x=%d, y=%d.\n", curr_x, curr_y);
        }
    }
    close(fd);	
    return 0;
}