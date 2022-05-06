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


int recv_msg()
{
    int on = 1;
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
    // 设置允许地址复用
    if (setsockopt(socket_handle, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0) {
        printf("setsockopt failed error: %s(errno: %d)\n",strerror(errno),errno);
        goto EXIT;
    }
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
    while (1) {
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

int readn(int fd, void *vptr, size_t n)
{
    size_t          nleft = n;           //readn函数还需要读的字节数
    ssize_t         nread = 0;           //read函数读到的字节数
    unsigned char   *ptr = (char *)vptr; //指向缓冲区的指针

    while (nleft > 0)
    {
        nread = read(fd, ptr, nleft);
        if (-1 == nread)
        {
            if (EINTR == errno)
                nread = 0;
            else
                return -1;
        }
        else if (0 == nread)
        {
            break;
        }
        nleft -= nread;
        ptr += nread;
    }
    return n - nleft;
}

int writen(int fd, const void *vptr, size_t n)
{
    size_t          nleft = n;  //writen函数还需要写的字节数
    ssize_t         nwrite = 0; //write函数本次向fd写的字节数
    const char*     ptr = vptr; //指向缓冲区的指针

    while (nleft > 0)
    {
        if ((nwrite = write(fd, ptr, nleft)) <= 0)
        {
            if (nwrite < 0 && EINTR == errno)
                nwrite = 0;
            else
                return -1;
        }
        nleft -= nwrite;
        ptr += nwrite;
    }
    return n;
}

static ssize_t readch(int fd, char *ptr)
{
    static int          count = 0;
    static char*        read_ptr = 0;
    static char         read_buf[1024*4] = {0};

    if (count <= 0)
    {
    again:
        count = read(fd, read_buf, sizeof(read_buf));
        if (-1 == count)
            if (EINTR == errno)
                goto again;
            else
                return -1;
        else if (0 == count)
            return 0;
        read_ptr = read_buf;
    }
    count--;
    *ptr = *read_ptr++;
    return 1;
}

ssize_t readline(int fd, void *vptr, size_t maxlen)
{
    ssize_t         i = 0;
    ssize_t         ret = 0;
    char            ch = '\0';
    char*           ptr = NULL;

    ptr = (char *)vptr;

    for (i = 1; i < maxlen; ++i)
    {
        ret = readch(fd, &ch);
        if (1 == ret)
        {
            *ptr++ = ch;
            if ('\n' == ch)
                break;
        }
        else if (0 == ret)
        {
            *ptr = 0;
            return i-1;
        }
        else
            return -1;
    }
    *ptr = 0;
    return i;
}

void str_cli(FILE *fp, int sockfd)
{
    char sendline[1024], recvline[1024];
    while (fgets(sendline, 1024, fp) != NULL) {
        write(sockfd, sendline, 1024);
        if (readline(sockfd, recvline, 1024) == 0) {
            printf("str_cli:server terminated prematurely\n");
            return;
        }
        fputs(recvline, stdout);
    }
    return;
}

char ip_addr[BUFFERSIZE];
int send_msg()
{
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
    if (inet_pton(AF_INET, ip_addr, &server_addr.sin_addr) <= 0) {
        printf("inet_pton error for %s\n", ip_addr); 
        goto EXIT;
    }
    
    // 建立连接
    if (connect(socket_handle, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        printf("connect error: %s(errno: %d)\n", strerror(errno), errno); 
        goto EXIT;
    }
    while (1) { 
        // 输入发送的消息内容
        printf("\nplease input send msg to server : ");
        char msg[BUFFERSIZE];
        //getchar();
        //fgets(msg, BUFFERSIZE, stdin);
        scanf("%s", msg);
        printf("will send msg : %s", msg);
        
        // 向服务器发送消息
        if (send(socket_handle, msg, strlen(msg), 0) < 0) {
            printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
            goto EXIT;
        }

        str_cli(stdin, socket_handle);
    }
    
EXIT:
    printf("\nclose socket handle and exit\n");
    if (socket_handle != -1) {
        close(socket_handle);
    }
    return 0;
}

int main(int argc, char** argv)
{
    pid_t pid = 0;
    pid = fork();
    
    if (pid > 0) {
        sleep(2);
        // 指定服务器ip地址
        printf("please input <ip_address> : ");
        scanf("%s", ip_addr);
        printf("current ip addr = %s\n", ip_addr);
        while (1) {
            send_msg();
        }
    } else if (pid == 0) {
        recv_msg();
    } else {
        printf("fork error: %s(error: %d)\n", strerror(errno), errno);
    }
    return 0;
}
