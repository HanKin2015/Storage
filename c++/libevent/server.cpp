/**
  You need libevent2 to compile this piece of code
  Please see: http://libevent.org/
  Or you can simply run this command to install on Mac: brew install libevent
  Cmd to compile this piece of code: g++ LibeventQuickStartServer.c  -o  LibeventQuickStartServer /usr/local/lib/libevent.a
 **/
#include <stdio.h>  
#include <string.h>  
#include <errno.h>  
#include <unistd.h>  
#include <event.h>

void accept_cb(int fd, short events, void* arg);
void socket_read_cb(int fd, short events, void* arg);
int tcp_server_init(int port, int listen_num);

int main(int argc, char const *argv[])
{
	/* code */
	int listener = tcp_server_init(9999, 10);
	if (listener == -1) {
		perror("tcp_server_init error");
		return -1;
	}

	struct event_base* base = event_base_new();

	// 监听客户端请求链接事件
	struct event* ev_listen = event_new(base, listener, EV_READ | EV_PERSIST, accept_cb, base);

	event_add(ev_listen, NULL);

	event_base_dispatch(base);

	return 0;
}

void accept_cb(int fd, short events, void* arg)
{
	evutil_socket_t sockfd;

	struct sockaddr_in client;
	socklen_t len = sizeof(client);

	sockfd = ::accept(fd, (struct sockaddr *)&client, &len);
	evutil_make_socket_nonblocking(sockfd);

	printf("accept a client %d\n", sockfd);

	struct event_base* base = (event_base*)arg;

	//动态创建一个event结构体，并将其作为回调参数传递给
	struct event* ev = event_new(NULL, -1, 0, NULL, NULL);
	event_assign(ev, base, sockfd, EV_READ | EV_PERSIST, socket_read_cb, (void*)ev);
	event_add(ev, NULL);
	return;
}


void socket_read_cb(int fd, short events, void* arg)
{
	char msg[4096];
	struct event* ev = (struct event *)arg;
	int len = read(fd, msg, sizeof(msg) - 1);

	if (len <= 0) {
		printf("some error happen when read\n");
		event_free(ev);
		close(fd);
		return;
	}

	msg[len] = '\0';
	printf("recv the client msg : %s\n", msg);

	char reply_msg[4096] = "I have received the msg: ";
	strcat(reply_msg + strlen(reply_msg), msg);
	write(fd, reply_msg, strlen(reply_msg));	// 又把消息发送回去
	return;
}

// 初始化服务端监听端口
int tcp_server_init(int port, int listen_num)  
{  
	// int evutil_make_socket_nonblocking(evutil_socket_t sock); 这里需要用到
	evutil_socket_t listener;  

	listener = ::socket(AF_INET, SOCK_STREAM, 0);  
	//listener = ::socker(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
	if (listener == -1) {
		printf("create socket failed, %s\n", strerror(errno));
		return -1;  
	}

	//允许多次绑定同一个地址。要用在socket和bind之间  
	evutil_make_listen_socket_reuseable(listener);  

	struct sockaddr_in sin;  
	sin.sin_family = AF_INET;  
	sin.sin_addr.s_addr = 0;  // 表示本地的所有的可用地址
	sin.sin_port = htons(port);  

	// int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
	if (::bind(listener, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
		printf("bind failed! %s\n", strerror(errno));
		goto error;  
	}

	if (::listen(listener, listen_num) < 0) {
		printf("listen failed! %s\n", strerror(errno));
		goto error;  
	}

	// 跨平台统一接口，将套接字设置为非阻塞状态  
	evutil_make_socket_nonblocking(listener);  

	return listener;  

error:  
	evutil_closesocket(listener);  
	return -1;  
}  

