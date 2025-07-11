// server_app.cpp - 使用封装类的服务器应用

#include "event_server.h"
#include <iostream>

int main() {
    EventServer server("/tmp/my_socket");
    
    // 设置消息接收回调
    server.setMessageCallback([](const std::string& message) {
        std::cout << "Received: " << message << std::endl;
        
        // 回复客户端
        // 实际应用中可能需要根据消息内容决定回复什么
    });
    
    // 设置连接状态回调
    server.setConnectionCallback([](bool connected) {
        std::cout << "Connection status: " << (connected ? "connected" : "disconnected") << std::endl;
    });
    
    // 启动服务器
    if (server.start()) {
        std::cout << "Server started. Press Enter to exit..." << std::endl;
        std::cin.get();
        server.stop();
    }
    
    return 0;
}