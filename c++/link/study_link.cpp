#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main()
{
	int ret;

	ret = symlink("/etc/passwd", "./pass1");
	if (ret != 0) {
		printf("ret:%d (%s)\n", ret, strerror(errno));
	}
	
	symlink("/etc/passwd", "pass2");
	if (ret != 0) {
		printf("ret:%d (%s)\n", ret, strerror(errno));
	}
	
	const int buf_size = 100;
	char buf[buf_size] = {0};
	ret = readlink("./pass1", buf, buf_size);
	if (ret == -1) {
		printf("ret:%d (%s)\n", ret, strerror(errno));
	} else {
		printf("pass1 -> %s\n", buf);
	}
	return 0;
}

