#include <stdio.h>
#include <string.h>
#include <unistd.h>

void vul(char *msg)
{
    char buffer[128];
    printf("%p", buffer);
    strcpy(buffer, msg);
    return;
}

int main()
{
    puts("give me your sheelcode please:");
    char buffer[256] = { 0 };
    read(0, buffer, 256);
    vul(buffer);
    return 0;
}