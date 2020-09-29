#include <iostream>
#include <errno.h>
#include <sys/socket.h>
#include <cstdio>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#define BUFFERSIZE 4096
using namespace std;

int main()
{
    // 创建一个socket
    int socket_handle = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_handle == -1) {
        printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);
        goto EXIT;
    }
    
    // 绑定本地地址
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);    // 0.0.0.0泛指本机的所有ip地址，便于程序移植
    server_addr.sin_port = htons(6666);
    if (bind(socket_handle, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        printf("bind socket error: %s(errno: %d)\n", strerror(errno), errno);
        goto EXIT;
    }
    
    // 开始监听
    if (listen(socket_handle, 10) == -1) {
        printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);
        goto EXIT;
    }
    
    // 无限循环接收请求
    printf("======waiting for client's request======\n"); 
    while(1) {
        int conn_handle = accept(socket_handle, (struct sockaddr*)NULL, NULL);
        if (conn_handle == -1) { 
            printf("accept socket error: %s(errno: %d)", strerror(errno), errno); 
            continue; 
        }
        
        char buffer[BUFFERSIZE];
        memset(buffer, 0, sizeof(buffer));
        int msg_size = recv(conn_handle, buffer, BUFFERSIZE, 0); 
        buffer[msg_size] = '\0'; 
        printf("recv msg from client: %s\n", buffer); 
        close(conn_handle); 
    }

EXIT:
    if (socket_handle != -1) {
        close(socket_handle);
    }
    return 0;
}
