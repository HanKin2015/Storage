#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	char s1[20];
	memset(s1, 0, sizeof(s1));
	printf("%d %d\n", strlen(s1), sizeof(s1)); 
	const char *s3 = "12345678910";
	printf("%d %d\n", strlen(s3), sizeof(s3)); 
	snprintf(s1, strlen(s3) - 1, "%s", s3);
	char *s2 = s1;
	printf("%s\n", s2);
	printf("%d %d\n", strlen(s2), sizeof(s2));
	
	char *s4 = (char *)malloc(100);
	if (s4 == NULL) {
		printf("malloc failed\n");
	}
	printf("%d %d\n", strlen(s4), sizeof(s4));
	return 0;
}
