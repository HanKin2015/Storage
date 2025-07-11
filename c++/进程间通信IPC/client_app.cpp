// client_app.cpp - 使用封装类的客户端应用

#include "event_client.h"
#include <iostream>
#include <thread>

int main() {
    EventClient client("/tmp/my_socket");
    
    // 设置消息接收回调
    client.setMessageCallback([](const std::string& message) {
        std::cout << "Server response: " << message << std::endl;
    });
    
    // 设置连接状态回调
    client.setConnectionCallback([](bool connected) {
        std::cout << "Connection status: " << (connected ? "connected" : "disconnected") << std::endl;
    });
    
    // 启动客户端
    if (client.start()) {
        std::cout << "Client started. Type messages and press Enter to send." << std::endl;
        std::cout << "Type 'exit' to quit." << std::endl;
        
        std::string input;
        while (std::getline(std::cin, input)) {
            if (input == "exit") {
                break;
            }
            
            client.sendMessage(input);
        }
        
        client.stop();
    }
    
    return 0;
}