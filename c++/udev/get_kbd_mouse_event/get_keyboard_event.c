/*******************************************************************************
* 文 件 名: get_keyboard_event.c
* 文件描述: 获取键盘数据（也可以获取鼠标数据）
* 备    注: https://blog.csdn.net/wabil/article/details/132382577
* 作    者: HanKin
* 创建日期: 2023.12.18
* 修改日期：2023.12.18
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("param is invalid, use event number please\n");
        return -1;
    }
    char keyboard_event_path[BUFSIZ] = "/dev/input/event";
    strncat(keyboard_event_path, argv[1], strlen(argv[1]));
    printf("keyboard event path: %s\n", keyboard_event_path);
    
    int fd = -1, ret = -1;
    struct input_event ev;
    // 第1步：打开设备文件
    fd = open(keyboard_event_path, O_RDONLY);
    if (fd < 0) {
        perror("open,error");
        return -1;
    }
    printf("struct input_event size=%lu.\n", sizeof(struct input_event));

    while (1) {
        // 第2步：读取event事件包
        memset(&ev, 0, sizeof(struct input_event));
        ret = read(fd, &ev, sizeof(struct input_event));
        if (ret != sizeof(struct input_event)) {
            perror("read,error");
            close(fd);
            return -1;
        }
        
        // 第3步：解析event包.
        printf("========================================================\n");
        printf("[%11ld] type: %3d, code: %3d, value: %3d \n", ev.time.tv_sec, ev.type, ev.code, ev.value);
        //type: 1:按键同步
        //code: 键码['a'=30]
        //value:0：按键释放，1：按键按下,2:长按下
    }

    // 第4步：关闭设备
    close(fd);	
    return 0;
}