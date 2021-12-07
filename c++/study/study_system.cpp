#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <iostream>
using namespace std;

int do_system(const char *fmt, ...)
{
	char cmd[BUFSIZ] = "";

	va_list ap;
	va_start(ap, fmt);
	int num = vsnprintf(cmd, sizeof(cmd), fmt, ap);
	va_end(ap);

	if (num < 0 || num >= (int)sizeof(cmd))
		return -1;

	int ret = system(cmd);

	if (ret < 0)
		return -1;

	return (WIFEXITED(ret) && WEXITSTATUS(ret) == 0) ? 0 : -1;
}

int main()
{
	system("touch 123.txt");
	return 0;
}
