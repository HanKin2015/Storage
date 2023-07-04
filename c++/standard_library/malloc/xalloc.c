#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char s1[100];
    memset(s1, 0, sizeof(s1));

    char *s2 = (char *)malloc(sizeof(char) * 100);
    printf("uninit malloc s2[55]: %d\n", s2[55]);
    memset(s2, 0, sizeof(char) * 100);
    printf("init: %lu %lu %lu %lu %lu\n", sizeof(s1), sizeof(s2),  sizeof(char *), strlen(s1), strlen(s2));

    const char *str = "12345";
    memcpy(s1, str, sizeof(s1));
    strncpy(s2, str, sizeof(char)*100-1);
    printf("assign: %lu %lu %lu %lu %lu\n", sizeof(s1), sizeof(s2),  sizeof(char *), strlen(s1), strlen(s2));

    char *s3 = (char *)calloc(100, sizeof(char));
    printf("uninit calloc s3[55]: %d\n", s3[55]);

    s3 = (char *)realloc(s3, sizeof(char) * 200);
    printf("uninit realloc s3[155]: %d\n", s3[155]);
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
uninit malloc s2[55]: 0
init: 100 8 8 0 0
assign: 100 8 8 5 5
uninit calloc s3[55]: 0
uninit realloc s3[155]: 0
*/