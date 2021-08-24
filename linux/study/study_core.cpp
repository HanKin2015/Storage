#include <stdio.h>
#include <unistd.h>

int main()
{
    // change the urrent working directory to "/data/coredump/wd"
    const char *wdir = "/data/coredump/wd";
    int ret = -1;
    ret = chdir(wdir);
    if (ret != 0) {
        printf("chdir failed! ret; %d\n", ret);
        return -1;
    }

    // generate coredump file
    char *ptr = "hello world";
    *ptr = 0;
    
    return 0;
}