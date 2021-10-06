#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

int main()
{
	char *str = new char[20];
	const char *s = "123";
	strncat(str, s, strlen(s) - 1);
	printf("%lu %lu %lu %lu %s\n", strlen(s), strlen(str), sizeof(s), sizeof(str), str);
	printf("%lu %lu %lu %lu\n", sizeof(char), sizeof(char *), sizeof(int), sizeof(int *));
	
	const char *log_file_prefix = "/log/today/log_";
	char tmp[256];
	strncpy(tmp, log_file_prefix, strlen(log_file_prefix));
	printf("tmp: %s, %lu, %lu.\n", tmp, sizeof(log_file_prefix), strlen(log_file_prefix));
	return 0;
}
