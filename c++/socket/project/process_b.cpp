// process_b.cpp
#include "message_utils.h"
#include <iostream>
#include <thread>

// 处理来自A的连接
void handle_client(int client_socket)
{
    try {
        std::cout << "进程B: 收到来自A的连接" << std::endl;
        
        // 接收A发送的消息
        json data_from_a;
        if (!recv_json(client_socket, data_from_a)) {
            close(client_socket);
            return;
        }
        
        std::cout << "进程B收到A的消息: " << data_from_a.dump(4) << std::endl;
        
        // 连接到进程C
        int sock_to_c = connect_to_server(SERVER_IP, PORT_C);
        
        // 转发消息给C
        if (!send_json(sock_to_c, data_from_a)) {
            close(sock_to_c);
            close(client_socket);
            return;
        }
        
        // 接收C的响应
        json data_from_c;
        if (!recv_json(sock_to_c, data_from_c)) {
            close(sock_to_c);
            close(client_socket);
            return;
        }
        
        std::cout << "进程B收到C的响应: " << data_from_c.dump(4) << std::endl;
        
        // 关闭与C的连接
        close(sock_to_c);
        
        // 将C的响应转发给A
        if (!send_json(client_socket, data_from_c)) {
            close(client_socket);
            return;
        }
        
        // 关闭与A的连接
        close(client_socket);
        std::cout << "进程B: 完成一次消息转发" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "进程B处理错误: " << e.what() << std::endl;
        close(client_socket);
    }
}

int main()
{
    try {
        std::cout << "进程B启动" << std::endl;
        
        // 创建服务器，监听A的连接
        int server_fd = create_tcp_server(PORT_B);
        
        while (true) {
            sockaddr_in address;
            socklen_t addrlen = sizeof(address);
            
            // 接受A的连接
            int new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen);
            if (new_socket < 0) {
                std::cerr << "接受连接失败: " << strerror(errno) << std::endl;
                continue;
            }
            
            // 创建新线程处理连接
            std::thread(handle_client, new_socket).detach();
        }
        
        close(server_fd);
    } catch (const std::exception& e) {
        std::cerr << "进程B错误: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
