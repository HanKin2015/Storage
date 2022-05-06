#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#define DESCRIPTOR_MAX_LENGTH 256 

int main()
{
	char *str = (char *)malloc(DESCRIPTOR_MAX_LENGTH);
	uint16_t vid = 0xc007;
	//int vid = 1234;
	printf("start\n");
	sprintf(str, "%04x", vid);
	printf("%s\n", str);
	sprintf(str, "%d", 1);
	printf("%s\n", str);
	
	char *tmp = (char *)malloc(2);
	int n = 12;
	sprintf(tmp, "%02x", n);
	char *p = (char *)malloc(DESCRIPTOR_MAX_LENGTH);
	memset(p, 0, sizeof(char *)*DESCRIPTOR_MAX_LENGTH);
	strncat(p, tmp, 2);
	strncat(p, tmp, 2);
	strncat(p, tmp, 2);
	printf("%s\n", p);
	return 0;
}
