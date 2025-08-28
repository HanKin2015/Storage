#include <sys/select.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>

#define PORT 8888
#define MAX_CLIENTS 100

int main() {
    int server_fd, new_socket, client_fds[MAX_CLIENTS];
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    fd_set read_fds, temp_fds;
    int max_sd;

    // 创建套接字
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // 绑定套接字
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    // 监听连接
    listen(server_fd, 3);

    // 初始化客户端文件描述符数组
    for (int i = 0; i < MAX_CLIENTS; i++) {
        client_fds[i] = -1;
    }

    // 初始化文件描述符集合
    FD_ZERO(&read_fds);
    FD_SET(server_fd, &read_fds);
    max_sd = server_fd;

    while (1) {
        temp_fds = read_fds;

        // 调用select函数，等待事件发生
        int activity = select(max_sd + 1, &temp_fds, NULL, NULL, NULL);

        if (activity < 0) {
            perror("select error");
            break;
        } else if (activity > 0) {
            // 检查是否有新的连接请求
            if (FD_ISSET(server_fd, &temp_fds)) {
                new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
                for (int i = 0; i < MAX_CLIENTS; i++) {
                    if (client_fds[i] == -1) {
                        client_fds[i] = new_socket;
                        break;
                    }
                }
                FD_SET(new_socket, &read_fds);
                if (new_socket > max_sd) {
                    max_sd = new_socket;
                }
            }

            // 检查已连接客户端是否有数据可读
            for (int i = 0; i < MAX_CLIENTS; i++) {
                int sd = client_fds[i];
                if (sd != -1 && FD_ISSET(sd, &temp_fds)) {
                    char buffer[1024] = {0};
                    int valread = read(sd, buffer, 1024);
                    if (valread == 0) {
                        // 客户端关闭连接
                        close(sd);
                        FD_CLR(sd, &read_fds);
                        client_fds[i] = -1;
                    } else {
                        // 处理客户端数据
                        printf("Received from client: %s\n", buffer);
                    }
                }
            }
        }
    }

    close(server_fd);
    return 0;
}