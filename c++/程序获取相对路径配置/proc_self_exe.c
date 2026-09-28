// 第一种方案是第三方修改成读取自身程序所在目录，或者添加参数根据参数去读取
#include <stdio.h>
#include <libgen.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>

int main ()
{
    printf ("hello world\n");
    // 获取当前可执行文件路径
    char path [PATH_MAX];
    readlink ("/proc/self/exe", path, sizeof (path));
    // 提取目录部分
    char *dir = dirname (path);
    // 切换到该目录
    chdir (dir);
    // 然后读取 config.ini
    FILE *fp = fopen ("./etc/config.ini", "rw");
    if (!fp) {
    printf ("open ./etc/config.ini failed\n");
    return 1;
    }
    fclose (fp);
    printf ("open ./etc/config.ini success\n");
    sleep (1000);
    return 0;
}



