#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8888
#define MAX_CLIENTS 100

int main() {
    int server_fd, new_socket, client_fds[MAX_CLIENTS];
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    struct pollfd fds[MAX_CLIENTS + 1];
    int num_fds = 1;

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

    // 初始化pollfd数组
    fds[0].fd = server_fd;
    fds[0].events = POLLIN;

    while (1) {
        // 调用poll函数，等待事件发生
        int activity = poll(fds, num_fds, -1);

        if (activity < 0) {
            perror("poll error");
            break;
        } else if (activity > 0) {
            // 检查是否有新的连接请求
            if (fds[0].revents & POLLIN) {
                new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
                for (int i = 0; i < MAX_CLIENTS; i++) {
                    if (client_fds[i] == -1) {
                        client_fds[i] = new_socket;
                        fds[num_fds].fd = new_socket;
                        fds[num_fds].events = POLLIN;
                        num_fds++;
                        break;
                    }
                }
            }

            // 检查已连接客户端是否有数据可读
            for (int i = 1; i < num_fds; i++) {
                int sd = fds[i].fd;
                if (fds[i].revents & POLLIN) {
                    char buffer[1024] = {0};
                    int valread = read(sd, buffer, 1024);
                    if (valread == 0) {
                        // 客户端关闭连接
                        close(sd);
                        for (int j = i; j < num_fds - 1; j++) {
                            fds[j] = fds[j + 1];
                            client_fds[j - 1] = client_fds[j];
                        }
                        num_fds--;
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