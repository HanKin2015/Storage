#include <stdio.h>

#define fmt "%s"

int main()
{
    char str[] = "helloworld";
    printf("welcome "fmt" good!\n", str);

    printf("123" "456" "789""0\n");
    return 0;
}
