#include <iostream>
#include <stdio.h>
using namespace std;

inline const char * INNER_UNSAFE_CMD_SHELL(const char * cmdline)
{
    return cmdline;
}

int qemu_shell_call(const char* shell_cmd, char* result)
{
    //result数组长度至少1024.
    FILE* pipe;
    char buffer[1024];

    pipe = popen(INNER_UNSAFE_CMD_SHELL(shell_cmd), "r");
    if (!pipe) {
        return -1;
    }
    return 0;
}

inline void func()
{
    printf("hello world!\n");
}

int main()
{
    func();
    qemu_shell_call("ls -l", NULL);
    return 0;
}
