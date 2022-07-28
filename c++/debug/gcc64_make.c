#include <stdio.h>
#include <assert.h>

// 获取程序位数(被编译为多少位的代码)
int GetProgramBits()
{
    return sizeof(int*) * 8;
}

int main(int argc, char* argv[])
{
    printf("bits:\t%d\n", GetProgramBits());
    assert(argc > 1);
    return 0;
}
