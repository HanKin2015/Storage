// process_a.cpp
#include "message_utils.h"
#include <iostream>

int main()
{
    try {
        std::cout << "进程A启动" << std::endl;
        
        // 连接到进程B
        int sock = connect_to_server(SERVER_IP, PORT_B);
        
        // 创建要发送的JSON消息
        json send_data;
        send_data["type"] = "request";
        send_data["sender"] = "process_a";
        send_data["content"] = "Hello from A, please forward to C";
        send_data["timestamp"] = time(nullptr);
        
        std::cout << "进程A发送消息: " << send_data.dump(4) << std::endl;
        
        // 发送消息给B
        if (!send_json(sock, send_data)) {
            close(sock);
            return 1;
        }
        
        // 等待B返回的结果（来自C的响应）
        json recv_data;
        if (!recv_json(sock, recv_data)) {
            close(sock);
            return 1;
        }
        
        std::cout << "进程A收到响应: " << recv_data.dump(4) << std::endl;
        
        // 关闭连接
        close(sock);
        std::cout << "进程A完成" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "进程A错误: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
