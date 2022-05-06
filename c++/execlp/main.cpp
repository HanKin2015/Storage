#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "log.h"

int main()
{
    int ret = execlp("./hankin",
        "./hankin",
        "-h", "help", 
        "-p", "port",
        "-t", "time",
        NULL);

    printf("execlp ret %d, errno=%d, strerror=%s", ret, errno, strerror(errno));
    LOG_INFO();
    return 0;
}
