/**
 * 文 件 名: check_udev_plug_event.cpp
 * 文件描述: 检测USB设备拔出事件
 * 作    者: HanKin
 * 创建日期: 2021.09.01
 * 修改日期：2021.09.01
 *
 * Copyright (c) 2021 HanKin. All rights reserved.
 */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <errno.h> 
#include <unistd.h> 
#include <arpa/inet.h> 
#include <netinet/in.h>
#include <sys/types.h>  
#include <sys/socket.h>  
#include <sys/un.h>  
#include <sys/ioctl.h>
#include <linux/types.h> 
#include <linux/netlink.h>
#include <assert.h>

#define USB_ONLINE              0
#define USB_NOT_ONLINE          1

//状态检查尝试次数
#define MAX_RETRY_CNT           3
//状态检查尝试间隔(单位us)
#define RETRY_INTERVAL          100000

#define WAIT_TIME               3

// remove事件的特征字符串及其长度
#define REMOVE_EVENT_STR        "remove"
#define REMOVE_EVENT_STR_LEN    6

#define BUF_SIZE                1024

/* 监听内核usb设备插拔事件套接字 */
static int init_udev_event_sock()
{
    int ret;
    struct sockaddr_nl snl;
    const int rcv_buf_size = BUF_SIZE;

    bzero(&snl, sizeof(struct sockaddr_nl));
    snl.nl_family = AF_NETLINK;
    snl.nl_pid = getpid();
    snl.nl_groups = 1;

    int sock = socket(PF_NETLINK, SOCK_DGRAM, NETLINK_KOBJECT_UEVENT);
    if (sock == -1) {
        printf("create hotplug socket failed, err[%d]: %s\n", errno, strerror(errno));
        return -1;
    }

    setsockopt(sock, SOL_SOCKET, SO_RCVBUF, &rcv_buf_size, sizeof(rcv_buf_size));
    ret = bind(sock, (struct sockaddr *)&snl, sizeof(struct sockaddr_nl));
    if (ret < 0) {
        printf("bind hotplug socket failed, err[%d]: %s\n", errno, strerror(errno));
        close(sock);
        return -1;
    }
    return sock;
}

/* 用shell命令检查usb的状态返回值 */
static int get_udev_state(const char *pid, const char *vid)
{
    assert(pid != nullptr && vid != nullptr);
    
    std::string cmd = "cat /sys/kernel/debug/usb/devices | grep Vendor | grep ";
    cmd = cmd + pid + " | grep " + vid + " 2>&1 > /dev/null; echo $?";

    FILE *fp = popen(cmd.c_str(), "r");
    if (fp == nullptr) {
        printf("usb device query command execution failed, cmd = %s\n", cmd.c_str());
        return -1;
    }

    char buffer[BUF_SIZE] = {0};
    fgets(buffer, BUF_SIZE, fp);
    pclose(fp);
    fp = nullptr;

    if (!strncmp(buffer, "0", 1)) {
        return USB_ONLINE;
    }
    return USB_NOT_ONLINE;
}

/*
* 每次检查状态可能失败，最多重复检查三次，如果
* 三次都失败了，强制注销，
*/
static bool is_online(const char *pid, const char *vid)
{
    int try_cnt, udev_state;
    
    for (try_cnt = 0; try_cnt < MAX_RETRY_CNT; try_cnt++) {
        udev_state = get_udev_state(pid, vid);
        if (udev_state < 0) {
            printf("get usb device[%s:%s] state failed, try_cnt: %d\n", pid, vid, try_cnt);
            usleep(RETRY_INTERVAL);
            continue;
        }
        break;
    }
    
    if (udev_state == USB_NOT_ONLINE) {
        printf("usb device[%s:%s] is not online\n", pid, vid);
        return false;
    }

    if (try_cnt == MAX_RETRY_CNT) {
        // 多次尝试检查状态失败, 强制注销
        printf("get usb device[%s:%s] state reach the max retry times, need to quit\n", pid, vid);
        return false;
    }
    return true;
}


/**
* 发生USB设备插拔事件时检测USB状态
* @param 监听内核USB插拔事件的socket
* @return null
*/
static void check_udev_plug_event(const int udev_event_sock, const char *pid, const char *vid)
{
    while (1) {
        char buf[BUF_SIZE] = {0};
        int ret;
        ret = recv(udev_event_sock, &buf, sizeof(buf), 0);
        if (ret < 0) {
            printf("recv error, err[%d]: %s", errno, strerror(errno));
            continue;
        }
        printf("buf: %s\n", buf);
        if (strncmp(buf, REMOVE_EVENT_STR, REMOVE_EVENT_STR_LEN)) {
            continue;
        }

        if (!is_online(pid, vid)) {
            printf("usb device[%s:%s] is pull out\n", pid, vid);
            return;
        }
    }
    return;
}


/**
* 启动检测程序后，usb已被拔出做退出处理
* USB存在则实时监听插拔事件
* 当USB被拔出后做注销处理
*/
int main()
{
    const char *pid = "1d6b";
    const char *vid = "0002";
    
    if (!is_online(pid, vid)) {
        sleep(WAIT_TIME);
        printf("usb device[%s:%s] is not exist\n", pid, vid);
        return 0;
    }

    int udev_event_sock = init_udev_event_sock();
    check_udev_plug_event(udev_event_sock, pid, vid);
    close(udev_event_sock);
    return 0;
}

