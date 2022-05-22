#include <stdio.h>
#include <string.h>

int main()
{
    char buffer[50];
    char* s = "runoobcom";

    // 读取字符串并存储在 buffer 中
    int j = snprintf(buffer, 6, "%s", s);

    // 输出 buffer及字符数
    printf("string: %s\ncharacter count = %d\n", buffer, j);

    printf("%lu %lu\n", sizeof(buffer), strlen(buffer));
    memset(buffer, 0, sizeof(buffer));
    int i = snprintf(buffer, 50, "%s", s);
    printf("string: %s\ncharacter count = %d\n", buffer, i);

    char str[5] = {0};
    snprintf(str, 5, "%s", s);
    printf("%s\n", str);

    printf("%lu\n", strlen(s));
    char c[9] = {0};
    snprintf(c, strlen(s), "%s", s);
    printf("%s\n", c);
    return 0;
}
