// 确定sleep函数的睡眠单位
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    while (1) {
        printf ( "hello world\n" );
        sleep (2); //2s
    }
    return 0;
}