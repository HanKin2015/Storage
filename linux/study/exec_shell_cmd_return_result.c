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
#include<sys/types.h>
#include<sys/wait.h>

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

该函数的作用是创建一个管道，fork 一个进程，然后执行 shell，而 shell 的输出可以采用读取文件的方式获得。采用这种方法，既避免了创建临时文件，又不受输出字符数的限制，推荐使用。
*/
static int get_cmd_result_by_popen(char *ret_buf, int ret_buf_size, const char *cmd)
{
    assert(ret_buf && cmd);
    memset(ret_buf, 0, ret_buf_size);

    // FILE *popen(const char *command, const char *type)
    FILE *fp = popen(cmd, "r");
    if (fp == NULL) {
        printf("popen %s failed, errno=%d[%s]",
                cmd, errno, strerror(errno));
        return -1;
    }
    
    size_t count = 0;
    size_t ret = -1;
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
3.exec函数
int execl(const char *path, const char *arg, ...);
int execlp(const char *file, const char *arg, ...);
int execle(const char *path, const char *arg, ..., char *const envp[]);
int execv(const char *path, char *const argv[]);
int execvp(const char *file, char *const argv[]);
int execve(const char *path, char *const argv[], char *const envp[];

完全由子进程执行了，无法得知执行结果
*/
static int get_cmd_result_by_exec(char *ret_buf, int ret_buf_size, const char *cmd)
{
    assert(ret_buf && cmd);
    
    char *args[] = {"ls", "-al", "/etc/passwd"};
    if (vfork() == 0) {
        execv("/bin/ls", args);
        _exit(0);
    } else {
        printf("This is the parent process\n");
    }
    return 0;
}

/*
4.使用临时文件

参数template 所指的文件名称字符串中最后六个字符必须是XXXXXX
参数 template 所指的文件名称字符串必须声明为数组, 如:
char template[] = "template-XXXXXX";
千万不可以使用下列的表达方式(一直出现段错误)
char *template = "template-XXXXXX";

[root@ubuntu0006:/media/hankin/vdb/study] #cat tmpfile-RsEVJs
8175056 7505756
*/
static int get_cmd_result_by_tmpfile(char *tmpfile, const char *cmd)
{
    assert(tmpfile && cmd);
    printf("%s[%d] tmpfile: %s, cmd: %s\n", __FUNCTION__, __LINE__, tmpfile, cmd);
    
    char cmd_string[1024] = {0};
    int ret = mkstemp(tmpfile);
    if (ret == -1) {
        printf("%s[%d] error[%d]: %s\n", __FUNCTION__, __LINE__, errno, strerror(errno));
        return -1;
    }
    
    sprintf(cmd_string, "%s > %s", cmd, tmpfile);
    printf("%s[%d] cmd_string: %s\n", __FUNCTION__, __LINE__, cmd_string);
    return system(cmd_string);
}

/**
 * 5.使用匿名管道
 * 在《UNIX 环境高级编程》（APUE）一书中给出了一种通过匿名管道方式将程序结果输出到分页程序的例子，因此想到，
 * 我们也可以通过管道来将外部命令的结果同应用程序连接起来。方法就是 fork 一个子进程，并创建一个匿名管道，在
 * 子进程中执行 shell 命令，并将其标准输出 dup 到匿名管道的输入端，父进程从管道中读取，即可获得 shell 命令的输出。
 *
 * 增强的 system 函数，能够返回 system 调用的输出
 *
 * @param[in ] cmdstring 调用外部程序或脚本的命令串
 * @param[out] buf 返回外部命令的结果的缓冲区
 * @param[in ] len 缓冲区 buf 的长度
 *
 * @return 0: 成功; -1: 失败 
 */
static int get_cmd_result_by_anonymous_pipe(char *ret_buf, int ret_buf_size, const char *cmd)
{
    assert(ret_buf && cmd);
    memset(ret_buf, 0, ret_buf_size);
    
    int   fd[2];
    pid_t pid;
    int   n, count;

    if (pipe(fd) < 0) {
        printf("%s[%d] error[%d]: %s\n", __FUNCTION__, __LINE__, errno, strerror(errno));
        return -1;
    }

    if ((pid = fork()) < 0) {
        printf("%s[%d] error[%d]: %s\n", __FUNCTION__, __LINE__, errno, strerror(errno));
        return -1;
    } else if (pid > 0) {   /* parent process */
        close(fd[1]);       /* close write end */
        count = 0;

        while ((n = read(fd[0], ret_buf + count, ret_buf_size)) > 0 && count < ret_buf_size) {
            count += n;
        }

        // 如果执行成功则返回子进程识别码(PID) ,如果有错误发生则返回返回值-1。失败原因存于 errno 中。
        if (waitpid(pid, NULL, 0) == -1) {
            printf("%s[%d] error[%d]: %s\n", __FUNCTION__, __LINE__, errno, strerror(errno));
            return -1;
        }
        
        printf("ret_buf: %s\n", ret_buf);
    } else {                /* child process */
        close(fd[0]);       /* close read end */
        if (fd[1] != STDOUT_FILENO) {
            if (dup2(fd[1], STDOUT_FILENO) != STDOUT_FILENO) {
                printf("%s[%d] error[%d]: %s\n", __FUNCTION__, __LINE__, errno, strerror(errno));
                return -1;
            }
        } 
        
        if (execl("/bin/sh", "sh", "-c", cmd, (char *)0) == -1) {
            printf("%s[%d] error[%d]: %s\n", __FUNCTION__, __LINE__, errno, strerror(errno));
            return -1;
        }
    } 
    close(fd[0]);
    close(fd[1]);
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
    printf("total = %lu, avaiable = %lu, utilization = %.3lf%%\n", total, available, (total - available) * 1.0 / total * 100);
    
    ret = get_cmd_result_by_exec(ret_buf, max_buf_size, cmd);
    if (ret < 0) {
        printf("[get_cmd_result_by_exec]cmd excute failed, return %d", ret);
        return -1;
    }
    
    char tmpfile[] = "./tmpfile-XXXXXX";
    ret = get_cmd_result_by_tmpfile(tmpfile, cmd);
    if (ret < 0) {
        printf("[get_cmd_result_by_tmpfile]cmd excute failed, return %d", ret);
        return -1;
    }
    
    ret = get_cmd_result_by_anonymous_pipe(ret_buf, max_buf_size, cmd);
    if (ret < 0) {
        printf("[get_cmd_result_by_anonymous_pipe]cmd excute failed, return %d\n", ret);
        return -1;
    }
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