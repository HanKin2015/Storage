#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    fd_set rfds;//定义一个能保存文件描述符集合的变量
    struct timeval tv;//定义超时时间
    int retval;//保存返回值

    /* Watch stdin (fd 0) to see when it has input. */
    /* 监测标准输入流（fd=0）看什么时候又输入*/
    FD_ZERO(&rfds);//初始化集合
    FD_SET(STDIN_FILENO, &rfds);//把文件描述符0加入到监测集合中。

    /* Wait up to five seconds. */
    /* 设置超时时间为5s */
    tv.tv_sec = 5;
    tv.tv_usec = 0;

    /*调用select函数，将文件描述符集合设置成读取监测 */
    retval = select(1, &rfds, NULL, NULL, &tv);
    /* Don't rely on the value of tv now! */
    /* 这时候的tv值是不可依赖的 */

    /*根据返回值类型判断select函数 */
    if (retval == -1)
        perror("select()");
    else if (retval)
        printf("Data is available now.\n");
    /* FD_ISSET(0, &rfds) will be true. */
    /* 因为值增加了一个fd，如果返回值>0,则说明fd=0在集合中。*/
    else
        printf("No data within five seconds.\n");

    exit(EXIT_SUCCESS);
}

