/*******************************************************************************
* 文 件 名: serverd_select.cpp
* 文件描述: 使用select实现的IPC服务器
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.11
* 修改日期：2025.07.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <fcntl.h>

#define SOCKET_PATH "/tmp/ipc_socket"
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 10

int main()
{
    // 创建Unix域套接字
    int server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    // 设置套接字地址
    sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);

    // 移除已存在的套接字文件
    unlink(SOCKET_PATH);

    // 绑定套接字
    if (bind(server_fd, (sockaddr*)&addr, sizeof(addr)) == -1) {
        std::cerr << "Failed to bind socket" << std::endl;
        close(server_fd);
        return 1;
    }

    // 监听连接
    if (listen(server_fd, 5) == -1) {
        std::cerr << "Failed to listen" << std::endl;
        close(server_fd);
        unlink(SOCKET_PATH);
        return 1;
    }

    std::cout << "Server started. Listening on " << SOCKET_PATH << std::endl;

    // 设置为非阻塞模式
    fcntl(server_fd, F_SETFL, O_NONBLOCK);

    // 创建文件描述符集合
    fd_set readfds;
    int max_fd = server_fd;
    int client_fds[MAX_CLIENTS] = {0};

    while (true) {
        // 清空文件描述符集合
        FD_ZERO(&readfds);

        // 添加服务器套接字
        FD_SET(server_fd, &readfds);

        // 添加所有客户端套接字
        for (int i = 0; i < MAX_CLIENTS; ++i) {
            if (client_fds[i] > 0) {
                FD_SET(client_fds[i], &readfds);
                if (client_fds[i] > max_fd) {
                    max_fd = client_fds[i];
                }
            }
        }

        // 使用select等待IO事件
        int activity = select(max_fd + 1, &readfds, nullptr, nullptr, nullptr);
        if (activity == -1) {
            std::cerr << "Select error" << std::endl;
            break;
        }

        // 检查服务器套接字是否有新连接
        if (FD_ISSET(server_fd, &readfds)) {
            sockaddr_un client_addr;
            socklen_t client_addr_len = sizeof(client_addr);
            int new_client = accept(server_fd, (sockaddr*)&client_addr, &client_addr_len);
            if (new_client == -1) {
                std::cerr << "Failed to accept new connection" << std::endl;
                continue;
            }

            // 设置为非阻塞模式
            fcntl(new_client, F_SETFL, O_NONBLOCK);

            // 添加到客户端数组
            for (int i = 0; i < MAX_CLIENTS; ++i) {
                if (client_fds[i] == 0) {
                    client_fds[i] = new_client;
                    std::cout << "New connection established. Client fd: " << new_client << std::endl;
                    break;
                }
            }
        }

        // 检查客户端套接字是否有数据可读
        for (int i = 0; i < MAX_CLIENTS; ++i) {
            if (client_fds[i] > 0 && FD_ISSET(client_fds[i], &readfds)) {
                char buffer[BUFFER_SIZE] = {0};
                int bytes_read = recv(client_fds[i], buffer, BUFFER_SIZE, 0);
                
                if (bytes_read <= 0) {
                    // 客户端关闭连接
                    std::cout << "Client disconnected. Client fd: " << client_fds[i] << std::endl;
                    close(client_fds[i]);
                    client_fds[i] = 0;
                } else {
                    // 处理接收到的数据
                    std::cout << "Received from client " << client_fds[i] << ": " << buffer << std::endl;
                    
                    // 回显数据给客户端
                    std::string response = "Server received: ";
                    response += buffer;
                    send(client_fds[i], response.c_str(), response.length(), 0);
                }
            }
        }
    }

    // 清理资源
    close(server_fd);
    unlink(SOCKET_PATH);
    return 0;
}