/*
什么是Quickstart?

Quickstart，97年开发，首次被引入Pentium III处理器，它主要是通过监测CPU的工作负荷，当CPU处于空闲状态时，就把CPU置于休眠状态，到需要时再迅速恢复工作状态。处于休眠状态的CPU功耗，甚至能低到0.5W，以达到有效管理电源以获得更长的使用时间。
*/

/**
You need libevent2 to compile this piece of code
Please see: http://libevent.org/
Or you can simply run this command to install on Mac: brew install libevent
Cmd to compile this piece of code: gcc client.c -o client -levent
**/
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <errno.h>  
#include <unistd.h>  
#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  
#include <event.h>  
#include <event2/util.h>  

int tcp_connect_server(const char* server_ip, int port);  
void cmd_msg_cb(int fd, short events, void* arg);  
void socket_read_cb(int fd, short events, void *arg);  

int main(int argc, char** argv)  
{  
	if ( argc < 3 ) {  
		printf("please input 2 parameter(ip, port)\n");  
		return -1;  
	}  

	//两个参数依次是服务器端的IP地址、端口号  
	int sockfd = tcp_connect_server(argv[1], atoi(argv[2]));  
	if (sockfd == -1) {  
		perror("tcp_connect_server error");  
		return -1;  
	}  

	printf("connect to server successful!\n");  

	struct event_base* base = event_base_new();  
	
	// 接受消息
	struct event *ev_sockfd = event_new(base, sockfd,  
			EV_READ | EV_PERSIST,  
			socket_read_cb, NULL);  
	event_add(ev_sockfd, NULL);  

	// 发送消息  
	struct event* ev_cmd = event_new(base, STDIN_FILENO,  
			EV_READ | EV_PERSIST, cmd_msg_cb,  
			(void*)&sockfd);  
	event_add(ev_cmd, NULL);  
	
	event_base_dispatch(base);  
	printf("finished \n");  
	return 0;  
}  

// 终端输入并发送消息
void cmd_msg_cb(int fd, short events, void* arg)  
{  
	char msg[1024];  

	int ret = read(fd, msg, sizeof(msg));  
	if (ret <= 0) {  
		perror("read fail ");  
		exit(1);  
	}  

	int sockfd = *((int*)arg);  

	//把终端的消息发送给服务器端  
	//为了简单起见，不考虑写一半数据的情况  
	write(sockfd, msg, ret);  
	return;
}  

// 接受服务端的消息
void socket_read_cb(int fd, short events, void *arg)  
{  
	char msg[1024];  

	//为了简单起见，不考虑读一半数据的情况  
	int len = read(fd, msg, sizeof(msg)-1);  
	if (len <= 0) {  
		perror("read fail ");  
		exit(1);  
	}  

	msg[len] = '\0';  

	printf("recv %s from server\n", msg);  
	return;
}  

// tcp连接方式连接服务器ip,port 
int tcp_connect_server(const char* server_ip, int port)  
{  
	int sockfd, status, save_errno;  
	struct sockaddr_in server_addr;  

	memset(&server_addr, 0, sizeof(server_addr) );  

	server_addr.sin_family = AF_INET;  
	server_addr.sin_port = htons(port);  
	status = inet_aton(server_ip, &server_addr.sin_addr);  

	if( status == 0 ) { //the server_ip is not valid value    
		errno = EINVAL;  
		return -1;  
	}  

	sockfd = ::socket(PF_INET, SOCK_STREAM, 0);  
	if (sockfd == -1) {  
		printf("create socket failed!\n");
		return sockfd;  
	}

	// int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
	// sockaddr_in把ip和port分开在两个变量中,sockaddr没有,常常需要做一个强制转换操作方便
	status = ::connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));  

	if (status == -1) {  
		save_errno = errno;  
		::close(sockfd);  
		errno = save_errno; //the close may be error  
		printf("connect failed!\n");
		return -1;  
	}  

	evutil_make_socket_nonblocking(sockfd);
	return sockfd;  
}  

