/**
 * 文 件 名: exec_shell_cmd_return_result.c
 * 文件描述: 执行shell命令返回结果
 * 作    者: HanKin
 * 创建日期: 2021.09.01
 * 修改日期：2021.09.01
 *
 * Copyright (c) 2021 HanKin. All rights reserved.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>

/*
一般来说，在 Linux 系统中使用 C 程序调用 shell 命令有以下三种常见的方法：system()、popen()、exec 系列函数。

使用 system() 不需要用户再创建进程，因为它已经封装好了，直接加入 shell 命令即可；
使用 popen() 执行 shell 命令，其开销比 system() 小；
exec 需要用户 fork/vfork 进程，然后 exec 所需的 shell 命令。
*/

/*
1.system函数
执行需要的结果直接在窗口输出，无法获取到
*/
static int get_cmd_result_by_system(char *ret_buf, int ret_buf_size, const char *cmd)
{
    assert(ret_buf && cmd);
    
    memset(ret_buf, 0, ret_buf_size);
    int ret = system(cmd);
    printf("ret = %d\n", ret);
    return ret;
}

/*
2.popen函数
推荐使用
*/
static int get_cmd_result_by_popen(char *ret_buf, int ret_buf_size, const char *cmd)
{
    assert(ret_buf && cmd);

    // FILE *popen(const char *command, const char *type)
    FILE *fp = popen(cmd, "r");
    if (fp == NULL) {
        printf("popen %s failed, errno=%d[%s]",
                cmd, errno, strerror(errno));
        return -1;
    }
    
    size_t count = 0;
    size_t ret = -1;
    memset(ret_buf, 0, ret_buf_size);
    do {
        // size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
        ret = fread(ret_buf + count, 1, ret_buf_size - count, fp);
        if (ret <= 0) {
            if (feof(fp)) {
                printf("read over\n");
                break;
            }
            printf("fread %s failed, errno=%d[%s]",
                            cmd, errno, strerror(errno));
            break;
        }
        count += ret;
        if (count >= ret_buf_size - 1) {
            printf("buff is not enough!");
            break;
        }
    } while (!feof(fp));
    //ret_buf[count] = '\0';

    // int pclose(FILE *stream)
    ret = pclose(fp);
    if (WIFEXITED(ret) == 0) {
        printf("cmd %s excute failed!", cmd);
        return -1;
    }
    int status = WEXITSTATUS(ret);
    if (status) {
        printf("cmd return status=%d", status);
        return -1;
    }
    return 0;
}

static int get_meminfo_utilization()
{
    const int max_buf_size = 1024;
    char ret_buf[max_buf_size];
    int ret = 0;
    const char *cmd = "free | awk 'NR==2{print $2,$7}'";
    
    ret = get_cmd_result_by_system(ret_buf, max_buf_size, cmd);
    if (ret < 0) {
        printf("[get_cmd_result_by_system]cmd excute failed, return %d", ret);
        return -1;
    }
    
    ret = get_cmd_result_by_popen(ret_buf, max_buf_size, cmd);
    if (ret < 0) {
        printf("[get_cmd_result_by_popen]cmd excute failed, return %d", ret);
        return -1;
    }
    size_t total = 0, available = 0;
    if(sscanf(ret_buf, "%lu %lu\n", &total, &available) != 2) {
        printf("sscanf cmd_ret failed!");
        return -1;
    }
    printf("total = %lu, avaiable = %lu, utilization = %%%.3lf\n", total, available, (total - available) * 1.0 / total * 100);
    return 0;
}


/*
题目：计算系统内存使用率
*/
int main()
{
    get_meminfo_utilization();
    return 0;
}