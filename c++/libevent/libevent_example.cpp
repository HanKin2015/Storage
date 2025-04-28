/*******************************************************************************
* 文 件 名: libevent_example.cpp
* 文件描述: 一个开源的事件通知库，旨在提供高效的事件驱动编程模型
* 备    注: 通过使用高效的 I/O 多路复用机制（如 epoll、kqueue、select 等），libevent 能够处理大量并发连接
* 作    者: HanKin
* 创建日期: 2025.04.25
* 修改日期：2025.04.25
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <event2/event.h>

void read_callback(evutil_socket_t fd, short events, void *arg) {
    char buffer[1024];
    int n = read(fd, buffer, sizeof(buffer) - 1);
    if (n > 0) {
        buffer[n] = '\0'; // 确保字符串以 null 结尾
        printf("读取到数据: %s\n", buffer);
    } else {
        printf("读取失败或连接关闭\n");
        event_base_loopbreak((struct event_base *)arg); // 退出事件循环
    }
}

int main() {
    struct event_base *base = event_base_new();
    if (!base) {
        fprintf(stderr, "创建事件基础失败\n");
        return 1;
    }

    // 创建一个事件，监听标准输入（fd = 0）的读事件
    struct event *ev = event_new(base, 0, EV_READ | EV_PERSIST, read_callback, base);
    event_add(ev, NULL); // 添加事件

    printf("请在标准输入中输入数据:\n");
    event_base_dispatch(base); // 进入事件循环

    event_free(ev);
    event_base_free(base);
    return 0;
}
