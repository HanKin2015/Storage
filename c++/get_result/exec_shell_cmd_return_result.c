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
#include <sys/wait.h>

int get_cmd_result_by_tmpfile(const char *cmd);

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
    printf("===== %s(%d) =====\n", __FUNCTION__, __LINE__);
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
    printf("===== %s(%d) =====\n", __FUNCTION__, __LINE__);
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

/*
===== get_cmd_result_by_popen2(100) =====
sizeof(): 8, strlen(): 0
buf: 8174988 6951888
*/
static int get_cmd_result_by_popen2(char *buf, int ret_buf_size, const char *cmd)
{
    printf("===== %s(%d) =====\n", __FUNCTION__, __LINE__);
    assert(buf && cmd);

    memset(buf, 0, ret_buf_size);       // 初始化buf,以免后面写如乱码到文件中
    printf("sizeof(): %ld, strlen(): %ld\n", sizeof(buf), strlen(buf));
    FILE *stream = popen(cmd, "r" );    // 将命令的输出(通过管道读取（“r”参数）)到FILE* stream
    FILE *wstream = fopen("test_popen.txt", "w+");  // 新建一个可写的文件
    fread(buf, sizeof(char), ret_buf_size, stream); // 将刚刚FILE* stream的数据流读取到buf中
    fwrite(buf, 1, ret_buf_size, wstream);          // 将buf中的数据写到FILE *wstream对应的流中，也是写到文件中
    pclose(stream);
    fclose(wstream);
    printf("buf: %s", buf);
    return 0;
}

/*
3.exec系列函数
使用匿名管道
*/
static int get_cmd_result_by_exec(char *buf, int len, const char *cmd)
{
    printf("===== %s(%d) =====\n", __FUNCTION__, __LINE__);
    int   fd[2];
    pid_t pid;
    int   n, count; 
    memset(buf, 0, len);    // 初始化输出结果数组
    int status = 0;
    
    if (pipe(fd) < 0) {   // 创建匿名管道
        printf("pipe failed\n");
        return -1;
    }
    
    if ((pid = fork()) < 0) {
        printf("fork failed\n");
        return -1;
    } else if (pid > 0) {   // 父进程
        close(fd[1]);     
        count = 0;
        while ((n = read(fd[0], buf + count, len - count - 1)) > 0) {
            count += n;
        }
        close(fd[0]);
        if ((status = waitpid(pid, NULL, 0)) < 0) { // waitpid 返回子进程的 PID，如果返回值小于 0 则表示出错
            printf("waitpid failed, status %d\n", status);
            return -1;
        }
    } else {    // 子进程
        close(fd[0]);     
        if (fd[1] != STDOUT_FILENO) {
            if (dup2(fd[1], STDOUT_FILENO) != STDOUT_FILENO) {
                printf("dup2 failed\n");
                _exit(1);
            }
            close(fd[1]);
        }
        if (execl("/bin/sh", "sh", "-c", cmd, (char*)0) == -1) {
            printf("execl failed\n");
            _exit(1);
        }
        _exit(0);
    }
    printf("buf: %s", buf);
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
===== get_meminfo_utilization(151) =====
===== get_cmd_result_by_system(34) =====
8174988 6961612
ret = 0
===== get_cmd_result_by_popen(49) =====
total = 8174988, avaiable = 6961756, utilization = %14.841
===== get_cmd_result_by_tmpfile(185) =====
cmd_string: free | awk 'NR==2{print $2,$7}' > /tmp/filedPL4PZ
get_cmd_result_by_tmpfile system exit status: 0
===== get_cmd_result_by_exec(103) =====
buf: 8174988 6961860
*/

// 获取内存使用率
static int get_meminfo_utilization()
{
    printf("===== %s(%d) =====\n", __FUNCTION__, __LINE__);
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
    
    get_cmd_result_by_popen2(ret_buf, max_buf_size, cmd);
    
    pid_t status = get_cmd_result_by_tmpfile(cmd);
    printf("get_cmd_result_by_tmpfile system exit status: %d\n", status);
    
    get_cmd_result_by_exec(ret_buf, max_buf_size, cmd);
    return 0;
}

// 4、使用临时文件
int get_cmd_result_by_tmpfile(const char *cmd)
{
    printf("===== %s(%d) =====\n", __FUNCTION__, __LINE__);
    
    char cmd_string[BUFSIZ] = { 0 };
    char tmpname[L_tmpnam];  // L_tmpnam 是一个宏，定义了临时文件名缓冲区的大小

    // 生成一个临时文件名
    if (tmpnam(tmpname) == NULL) {
        perror("tmpnam");
        return 1;
    }
    sprintf(cmd_string, "%s > %s", cmd, tmpname);
    printf("cmd_string: %s\n", cmd_string);
    return system(cmd_string);
}
/*
[root@ubuntu0006:~/cmake] #./a.out
===== get_meminfo_utilization(109) =====
===== get_cmd_result_by_system(33) =====
8174988 6945088（这个非程序获取的，而是system函数执行后打印的）
ret = 0
===== get_cmd_result_by_popen(48) =====
total = 8174988, avaiable = 6944972, utilization = %15.046
===== get_cmd_result_by_tmpfile(141) =====
cmd_string: free | awk 'NR==2{print $2,$7}' > /tmp/file8WlQc9
get_cmd_result_by_tmpfile system exit status: 0
[root@ubuntu0006:~/cmake] #cat /tmp/file8WlQc9
8174988 6944752
*/

/*
题目：计算系统内存使用率
*/
int main()
{
    get_meminfo_utilization();
    return 0;
}