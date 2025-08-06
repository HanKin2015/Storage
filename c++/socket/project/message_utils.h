/*******************************************************************************
* 文 件 名: message_utils.h
* 文件描述: 字符串那些事儿
* 备    注: 
* 作    者: HanKin
* 创建日期: 2021.08.24
* 修改日期：2025.08.06
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#ifndef MESSAGE_UTILS_H
#define MESSAGE_UTILS_H

#include "nlohmann/json.hpp"
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdexcept>

using json = nlohmann::json;

// 端口定义
const int PORT_B = 8080;   // 进程B监听端口
const int PORT_C = 8081;   // 进程C监听端口
const std::string SERVER_IP = "127.0.0.1";  // 本地回环地址

// 发送JSON消息
bool send_json(int socket_fd, const json& j)
{
    try {
        std::string json_str = j.dump();
        // 先发送消息长度（4字节）
        uint32_t len = htonl(json_str.size());
        if (send(socket_fd, &len, sizeof(len), 0) != sizeof(len)) {
            throw std::runtime_error("发送长度失败");
        }
        // 再发送消息内容
        if (send(socket_fd, json_str.c_str(), json_str.size(), 0) != (ssize_t)json_str.size()) {
            throw std::runtime_error("发送消息失败");
        }
        return true;
    } catch (const std::exception& e) {
        std::cerr << "发送JSON错误: " << e.what() << std::endl;
        return false;
    }
}

// 接收JSON消息
bool recv_json(int socket_fd, json& j)
{
    try {
        // 先接收消息长度
        uint32_t len;
        if (recv(socket_fd, &len, sizeof(len), 0) != sizeof(len)) {
            throw std::runtime_error("接收长度失败");
        }
        len = ntohl(len);
        
        // 再接收消息内容
        std::string json_str(len, '\0');
        ssize_t total_received = 0;
        while (total_received < len) {
            ssize_t received = recv(socket_fd, &json_str[total_received], len - total_received, 0);
            if (received <= 0) {
                throw std::runtime_error("接收消息失败");
            }
            total_received += received;
        }
        
        j = json::parse(json_str);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "接收JSON错误: " << e.what() << std::endl;
        return false;
    }
}

// 创建TCP服务器
int create_tcp_server(int port)
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        throw std::runtime_error("创建socket失败: " + std::string(strerror(errno)));
    }
    
    // 设置socket选项，允许端口重用
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        throw std::runtime_error("设置socket选项失败: " + std::string(strerror(errno)));
    }
    
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        throw std::runtime_error("绑定端口失败: " + std::string(strerror(errno)));
    }
    
    if (listen(server_fd, 3) < 0) {
        throw std::runtime_error("监听端口失败: " + std::string(strerror(errno)));
    }
    
    std::cout << "服务器启动，监听端口 " << port << std::endl;
    return server_fd;
}

// 连接到TCP服务器
int connect_to_server(const std::string& ip, int port)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        throw std::runtime_error("创建socket失败: " + std::string(strerror(errno)));
    }
    
    sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    
    // 转换IP地址
    if (inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr) <= 0) {
        throw std::runtime_error("无效的IP地址");
    }
    
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        throw std::runtime_error("连接服务器失败: " + std::string(strerror(errno)));
    }
    
    std::cout << "成功连接到 " << ip << ":" << port << std::endl;
    return sock;
}

#endif // MESSAGE_UTILS_H
