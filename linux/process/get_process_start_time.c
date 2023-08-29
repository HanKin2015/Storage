/**
* 文 件 名: get_process_start_time.cpp
* 文件描述: 获取进程启动时间
* 备    注: 太人工智障了，一步一步领导它完成
* 作    者: HanKin
* 创建日期: 2023.08.29
* 修改日期：2023.08.29
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define MAX_BUF_SIZE 1024

long get_process_start_time(int pid)
{
    char stat_file_path[MAX_BUF_SIZE];
    char stat_buf[MAX_BUF_SIZE];
    FILE *fp;
    long start_time = -1;

    // 构造进程的 stat 文件路径
    snprintf(stat_file_path, sizeof(stat_file_path), "/proc/%d/stat", pid);

    // 打开进程的 stat 文件
    fp = fopen(stat_file_path, "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to open stat file for process %d\n", pid);
        return -1;
    }

    // 读取 stat 文件内容
    if (fgets(stat_buf, sizeof(stat_buf), fp) == NULL) {
        fprintf(stderr, "Failed to read stat file for process %d\n", pid);
        fclose(fp);
        return -1;
    }

    // 关闭 stat 文件
    fclose(fp);

    // 使用空格分割 stat 文件内容
    char *token = strtok(stat_buf, " ");
    int count = 1;
    while (token != NULL) {
        if (count == 22) {
            // 第 22 个字段为进程的启动时间（以系统启动时间为基准的时钟滴答数）
            start_time = atol(token);
            break;
        }
        token = strtok(NULL, " ");
        count++;
    }

    if (start_time == -1) {
        fprintf(stderr, "Failed to get start time for process %d\n", pid);
        return -1;
    }

    // 读取系统运行时间
    long uptime_sec, uptime_usec;
    fp = fopen("/proc/uptime", "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to open uptime file\n");
        return -1;
    }
    if (fscanf(fp, "%ld.%ld", &uptime_sec, &uptime_usec) != 2) {
        fprintf(stderr, "Failed to read uptime file\n");
        fclose(fp);
        return -1;
    }
    fclose(fp);

    // 读取系统开机时间
    struct timespec boot_time;
    if (clock_gettime(CLOCK_BOOTTIME, &boot_time) == -1) {
        fprintf(stderr, "Failed to get system boot time\n");
        return -1;
    }
    
    // 计算进程的实际启动时间
    long clk_tck = sysconf(_SC_CLK_TCK);
    time_t start_time_sec = time(NULL) - (start_time / clk_tck);
    printf("%ld start_time %ld start_time_sec %ld\n", (start_time / clk_tck), start_time, start_time_sec);

    // 计算进程的实际启动时间
    start_time_sec = boot_time.tv_sec + (start_time / sysconf(_SC_CLK_TCK));
    printf("boot_time %ld start_time_sec %ld\n", boot_time.tv_sec, start_time_sec);
    return start_time_sec;
}

long get_process_start_time1(int pid)
{
    char stat_file_path[MAX_BUF_SIZE];
    char stat_buf[MAX_BUF_SIZE];
    FILE *fp;
    long start_time = -1;

    // 构造进程的 stat 文件路径
    snprintf(stat_file_path, sizeof(stat_file_path), "/proc/%d/stat", pid);

    // 打开进程的 stat 文件
    fp = fopen(stat_file_path, "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to open stat file for process %d\n", pid);
        return -1;
    }

    // 读取 stat 文件内容
    if (fgets(stat_buf, sizeof(stat_buf), fp) == NULL) {
        fprintf(stderr, "Failed to read stat file for process %d\n", pid);
        fclose(fp);
        return -1;
    }

    // 关闭 stat 文件
    fclose(fp);

    // 使用空格分割 stat 文件内容
    char *token = strtok(stat_buf, " ");
    int count = 1;
    while (token != NULL) {
        if (count == 22) {
            // 第 22 个字段为进程在用户态下消耗的CPU时间（utime）
            long utime = atol(token);
            token = strtok(NULL, " ");
            count++;
            if (token == NULL) {
                fprintf(stderr, "Failed to get start time for process %d\n", pid);
                return -1;
            }
            // 第 23 个字段为进程在内核态下消耗的CPU时间（stime）
            long stime = atol(token);
            // 计算进程的运行时间（以时钟滴答数为单位）
            long total_time = utime + stime;
            // 获取系统的时钟频率
            long clk_tck = sysconf(_SC_CLK_TCK);
            // 获取系统的当前时间
            time_t current_time = time(NULL);
            // 计算进程的启动时间
            time_t start_time_sec = current_time - (total_time / clk_tck);
            return start_time_sec;
        }
        token = strtok(NULL, " ");
        count++;
    }

    fprintf(stderr, "Failed to get start time for process %d\n", pid);
    return -1;
}

int debug(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pid>\n", argv[0]);
        return 1;
    }

    int pid = atoi(argv[1]);
    return 0;
}

// 在Linux系统中，可以使用getpid()函数来获取当前进程的ID
int get_process_id(const char *process_name)
{
    FILE *fp;
    char command[256];
    char line[256];
    int pid = -1;

    // 构造命令，使用ps命令获取进程信息
    snprintf(command, sizeof(command), "ps -C %s -o pid=", process_name);

    // 执行命令并读取输出
    fp = popen(command, "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to execute command: %s\n", command);
        return -1;
    }

    // 读取输出的进程ID
    if (fgets(line, sizeof(line), fp) != NULL) {
        pid = atoi(line);
    }

    // 关闭命令输出流
    pclose(fp);

    return pid;
}

long get_process_start_time2(int pid)
{
    char cmd[MAX_BUF_SIZE];
    char buf[MAX_BUF_SIZE];
    FILE *fp;
    long start_time = -1;

    // 构造 ps 命令
    snprintf(cmd, sizeof(cmd), "ps -o lstart= -p %d", pid);

    // 执行 ps 命令
    fp = popen(cmd, "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to execute ps command for process %d\n", pid);
        return -1;
    }

    // 读取命令输出
    if (fgets(buf, sizeof(buf), fp) != NULL) {
        // 解析启动时间
        struct tm tm;
        if (strptime(buf, "%a %b %d %H:%M:%S %Y", &tm) != NULL) {
            // 转换为时间戳
            time_t start_time_sec = mktime(&tm);
            if (start_time_sec != -1) {
                start_time = start_time_sec;
            }
        }
    }

    // 关闭命令输出
    pclose(fp);

    if (start_time == -1) {
        fprintf(stderr, "Failed to get start time for process %d\n", pid);
        return -1;
    }

    return start_time;
}

int main(int argc, char **argv)
{
    const char *process_name = "adesk-spicec";
    int pid = get_process_id(process_name);
    if (pid == -1) {
        fprintf(stderr, "Failed to get process ID for %s\n", process_name);
        return 1;
    }
    printf("Process ID of %s: %d\n", process_name, pid);
    
    long start_time = get_process_start_time2(pid);
    if (start_time == -1) {
        fprintf(stderr, "Failed to get start time for process %d\n", pid);
        return 1;
    }

    printf("Process %d start time: %ld\n", pid, start_time);

    return 0;
}
/*
root@hankin:~# ps -o lstart= -p 14630
Tue Aug 29 14:59:59 2023
root@hankin:~# ./a.out
Process ID of hankin-spicec: 14630
Process 14630 start time: 1693292399
root@hankin:~# date --date='@1693292399'
Tue Aug 29 14:59:59 CST 2023
*/