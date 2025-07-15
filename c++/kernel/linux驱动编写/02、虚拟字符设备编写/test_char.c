#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
 
#define CHAR_DEV_NAME "/dev/chr_dev"
 
int main()
{
	int ret;
	int fd;
	char buf[32];
	int read_len;

	// 在 Linux/Unix 系统编程中，O_NDELAY（或等价的 O_NONBLOCK）是文件打开标志，用于设置文件描述符为非阻塞模式。
	fd = open(CHAR_DEV_NAME, O_RDONLY | O_NDELAY);
	if(fd < 0)
	{
		printf("open failed!\n");
		return -1;
	}
	
	read_len = read(fd, buf, 32);
	printf("read length %d\n", read_len);   // 123
	close(fd);
	
	return 0;
}