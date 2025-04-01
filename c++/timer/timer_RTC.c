/*******************************************************************************
* 文 件 名: timer_RTC.c
* 文件描述: https://blog.csdn.net/hpu11/article/details/79588563
* 备    注: RTC机制利用系统硬件提供的Real Time Clock机制，通过读取RTC硬件/dev/rtc，通过ioctl()设置RTC频率
* 作    者: HanKin
* 创建日期: 2025.03.31
* 修改日期：2025.03.31
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <linux/rtc.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
 
int main(int argc, char* argv[])
{
    unsigned long i = 0;
    unsigned long data = 0;
    int retval = 0;
    int fd = open ("/dev/rtc", O_RDONLY);
    
    if (fd < 0) {
        perror("open");
        exit(errno);
    }
    
    /*Set the freq as 4Hz*/
    if (ioctl(fd, RTC_IRQP_SET, 2) < 0) {
        perror("ioctl(RTC_IRQP_SET)");
        close(fd);
        exit(errno);
    }
    /* Enable periodic interrupts */
    if (ioctl(fd, RTC_PIE_ON, 0) < 0) {
        perror("ioctl(RTC_PIE_ON)");
        close(fd);
        exit(errno);
    }
    
    for(i = 0; i < 100; i++) {
        if(read(fd, &data, sizeof(unsigned long)) < 0) {
            perror("read");
            close(fd);
            exit(errno);
            
        }
        time_t timestamp;
        time(&timestamp);
        printf("%ld: timer\n", timestamp);
    }
    /* Disable periodic interrupts */
    ioctl(fd, RTC_PIE_OFF, 0);
    close(fd);
    
    return 0;
}
/*
[root@ubuntu0006:~] #./a.out
1743420718: timer
1743420718: timer
1743420719: timer
1743420719: timer
1743420720: timer
1743420720: timer
1743420721: timer
1743420721: timer
*/