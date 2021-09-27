#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#define BUFFERSIZE 4096

int main(int argc, char** argv)
{
    // 指定服务器ip地址
    if (argc != 2) {
        printf("usage: ./client <ip_address>\n"); 
        return 0;
    }
    
    // 创建一个socket
    int socket_handle = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_handle == -1) {
        printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);
        goto EXIT;
    } 
    
    // 绑定服务器ip地址
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9999);
    if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0) {
        printf("inet_pton error for %s\n", argv[1]); 
        goto EXIT;
    }
    
    // 建立连接
    if (connect(socket_handle, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        printf("connect error: %s(errno: %d)\n", strerror(errno), errno); 
        goto EXIT;
    } 
    while (1) {
        // 输入发送的消息内容
        printf("send msg to server: \n");
        char msg[BUFFERSIZE];
        fgets(msg, BUFFERSIZE, stdin);
        
        // 向服务器发送消息
        if (send(socket_handle, msg, strlen(msg), 0) < 0) {
            printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
            goto EXIT;
        }
    }
    
EXIT:
    if (socket_handle != -1) {
        close(socket_handle);
    }
    return 0;
}
