// process_c.cpp
#include "message_utils.h"
#include <iostream>
#include <thread>

// 处理来自B的消息
void handle_request(int client_socket)
{
    try {
        std::cout << "进程C: 收到来自B的连接" << std::endl;
        
        // 接收B转发的消息
        json data_from_b;
        if (!recv_json(client_socket, data_from_b)) {
            close(client_socket);
            return;
        }
        
        std::cout << "进程C收到消息: " << data_from_b.dump(4) << std::endl;
        
        // 处理消息并生成响应
        json response;
        response["type"] = "response";
        response["sender"] = "process_c";
        response["original_content"] = data_from_b["content"];
        response["result"] = "Message processed successfully";
        response["timestamp"] = time(nullptr);
        
        // 发送响应给B
        if (!send_json(client_socket, response)) {
            close(client_socket);
            return;
        }
        
        std::cout << "进程C发送响应: " << response.dump(4) << std::endl;
        
        // 关闭连接
        close(client_socket);
    } catch (const std::exception& e) {
        std::cerr << "进程C处理错误: " << e.what() << std::endl;
        close(client_socket);
    }
}

int main()
{
    try {
        std::cout << "进程C启动" << std::endl;
        
        // 创建服务器，监听B的连接
        int server_fd = create_tcp_server(PORT_C);
        
        while (true) {
            sockaddr_in address;
            socklen_t addrlen = sizeof(address);
            
            // 接受B的连接
            int new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen);
            if (new_socket < 0) {
                std::cerr << "接受连接失败: " << strerror(errno) << std::endl;
                continue;
            }
            
            // 创建新线程处理请求
            std::thread(handle_request, new_socket).detach();
        }
        
        close(server_fd);
    } catch (const std::exception& e) {
        std::cerr << "进程C错误: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
