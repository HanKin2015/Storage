#include <stdio.h>
#include <stdlib.h>

int main()
{
    char ch[0x20] = "";
    //printf("%d %d\n", sizeof(ch), strlen(ch));

    char *p = (char *)malloc(-1);
    printf("%p %lu\n", p, sizeof(p));

    int a = -5;
    unsigned int b = 5;
    printf("int a = -5, uint b = 5\n");
    if (a > b) {
        printf("a大于b\r\n");
    } else {
        printf("a不大于b\r\n");
    }

    // 这个判断不应该有问题吧
    if (a > 0 && a > b) {
        printf("a大于b\r\n");
    } else {
        printf("a不大于b\r\n");
    }

    if (a <= 0) {
        printf("a不大于b\r\n");
    } else if (a > b) {
        printf("a大于b\r\n");
    } else {
        printf("a小于b\r\n");
    }

    char c = 'G';
    char str[] = "hankin";
    printf("%c\n", str[-1]);
    return 0;
}
