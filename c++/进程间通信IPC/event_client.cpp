// event_client.cpp - 客户端实现

#include "event_client.h"
#include <sys/un.h>
#include <iostream>

EventClient::EventClient(const std::string& socketPath)
    : m_socketPath(socketPath) {}

bool EventClient::setupSocket() {
    // 设置Unix域套接字地址
    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, m_socketPath.c_str(), sizeof(addr.sun_path) - 1);
    
    // 连接到服务器
    if (bufferevent_socket_connect(m_bufferEvent, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        std::cerr << "Failed to connect to server: " << m_socketPath << std::endl;
        return false;
    }
    
    return true;
}