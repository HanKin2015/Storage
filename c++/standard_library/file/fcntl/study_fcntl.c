#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main()
{
	// 参数害人,O_RDWR,O_RDONLY,O_WRONLY
	int fd = open("./fcntl.txt", O_CREAT | O_APPEND | O_WRONLY);
	const char *buf = "hello world\n";
	write(fd, buf, strlen(buf));

	printf("O_RDONLY: %d O_WRONLY: %d O_RDWR: %d\n", O_RDONLY, O_WRONLY, O_RDWR);
    printf("O_CREAT: 0x%0x O_APPEND: 0x%0x O_WRONLY: 0x%0x\n", O_CREAT, O_APPEND, O_WRONLY);

	int flag = fcntl(fd, F_GETFL);
	printf("flag: 0x%0x\n", flag);

	flag = fcntl(fd, F_GETFD);
	printf("flag: 0x%0x\n", flag);

	// 第三个参数转换成二进制格式的最后一位，因此是0或1
	flag = fcntl(fd, F_SETFD, 7);
	printf("flag: 0x%0x\n", flag);
	flag = fcntl(fd, F_GETFD);
	printf("flag: 0x%0x\n", flag);

	// fcntl(fd, F_DUPFD) 返回的fd要求大于等于参数fd的最小的可用的fd, dup(fd)返回的是当前进程中
	// 最小的可用的fd，没有大于等于的要求。所以一般用dup或者dup2来实现标准输入输出的重定向而不是fcntl。
	int new_fd = fcntl(fd, F_DUPFD, 10);
	if (new_fd < 0) {
		printf("error[%d]: %s\n", errno, strerror(errno));
		return -1;
	}
	printf("fd: %d, new_fd: %d\n", fd, new_fd);
	const char *new_buf = "let is go\n";
	write(new_fd, new_buf, strlen(new_buf)); 

	close(fd);
	close(new_fd);
	return 0;
}
/*
O_RDONLY: 0 O_WRONLY: 1 O_RDWR: 2
O_CREAT: 0x40 O_APPEND: 0x400 O_WRONLY: 0x1
flag: 0x8401
flag: 0x0
flag: 0x0
flag: 0x1
fd: 3, new_fd: 10
*/
