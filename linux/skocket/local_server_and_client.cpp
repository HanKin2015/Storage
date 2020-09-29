#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <sys/poll.h>
#include <signal.h>
#include <time.h>
#include <pthread.h>
#include <sys/un.h>

#define SERVER_DOMAIN_SOCKET_FILE "./server.sock"

int send_msg()
{
    // 创建一个socket
	int socket_handle = socket(AF_UNIX, SOCK_STREAM, 0);
	if(socket_handle < 0) {
		perror("socket error");
		return -1;
	}

    // 设置服务器本地相对路径地址
    struct sockaddr_un server_addr;
	bzero(&server_addr, sizeof(server_addr));   // 初始化为0
	server_addr.sun_family = AF_UNIX;
	strcpy(server_addr.sun_path, SERVER_DOMAIN_SOCKET_FILE);

    // 连接服务器
	int ret = connect(socket_handle, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if (ret < 0) {
		close(socket_handle);
		perror("connect error");
		return -3;
	}

    // 发送消息
    char msg[256];
    printf("please input send msg content : ");
    scanf("%s", msg);
	ret = send(socket_handle, msg, sizeof(msg), 0);
	if (ret != 4) {
		printf("\n[%s:%d]\033[36m ret=%d\n", __FUNCTION__, __LINE__, ret);
	}

	close(socket_handle);
	return 0;
}

int recv_msg()
{
	struct sockaddr_un server_addr;
	struct sockaddr_in client_addr;
	socklen_t client_length = sizeof(client_addr);
    
    // 创建一个socket
    int socket_handle = socket(AF_UNIX, SOCK_STREAM, 0);
    if (socket_handle < 0) {
        perror("socket error");
		return 0;
	}
    
    // 设置服务器本地相对路径地址
    unlink(SERVER_DOMAIN_SOCKET_FILE);
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sun_family = AF_LOCAL;
	strncpy(server_addr.sun_path, SERVER_DOMAIN_SOCKET_FILE, strlen(SERVER_DOMAIN_SOCKET_FILE));

    // 绑定本地服务器地址
	int ret = bind(socket_handle, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if (ret < 0) {
		close(socket_handle);
		perror("bind error");
		return 0;
	}

	ret = listen(socket_handle, 1);
	if (ret < 0) {
		close(socket_handle);
		perror("listen error");
		return 0;
	}
    
    while (1) {
		int conn_handle = accept(socket_handle, (struct sockaddr*)&client_addr, &client_length);
		if (conn_handle > 0) {
			char buffer[256];
			memset(&buffer, 0, sizeof(buffer));
			ret = recv(conn_handle, &buffer, sizeof(buffer), 0);
			if (ret != sizeof(buffer)) {
				printf("\n[%s:%d] get msg size error, ret = %d\n", __FUNCTION__, __LINE__, ret);
			}
            
			printf("\n[%s:%d] receive msg = [%s]\n", __FUNCTION__, __LINE__, buffer);
			close(conn_handle);
		}
	}

	close(socket_handle);
	return 0;
}

int main(int argc, char *argv[])
{
    pid_t pid = 0;
    pid = fork();
    
    if (pid > 0) {
        sleep(2);
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


