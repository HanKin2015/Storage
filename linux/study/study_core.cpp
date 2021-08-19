#include <stdio.h>
#include <unistd.h>

int main()
{
#if 0
    // change the urrent working directory to "/tmp/coredump/wd"
    const char *wdir = "/tmp/coredump/wd";
    int ret = -1;
    ret = chdir(wdir);
    if (ret != 0) {
        printf("chdir failed! ret; %d\n", ret);
        return -1;
    }
#endif

    // generate coredump file
    char *ptr = "hello world";
    *ptr = 0;

    return 0;
}
