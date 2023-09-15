/**
* 文 件 名: getopt_long_example.c
* 文件描述: getopt_long()函数学习
* 作    者: HanKin
* 创建日期: 2023.09.07
* 修改日期：2023.09.07
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

/** 帮助文档 **/
int print_help()
{
    printf("\nUsage:devicehelper [option]...\n\n"\
            "option:\n"\
            "\t-h, --help:										\tShow help\n"\
            "\t-l, --online_list:									\tGet all online users\n"\
            "\t-p, --policy [usernmae]:								\tGet effective policy type and policy details by username\n"\
            "\t-c, --client_log [username] [client_sn]:					\tGet client log by username and client sn\n"\
            "\t-v, --version:										\tShow the supported versions"
            "\n\n");
    return 0;
}

struct option long_options[] = {
    {"help", no_argument, 0, 'h'}, 				/** 显示帮助 */
    {"version", no_argument, 0, 'v'},		    /** 显示支持的版本 */
    {"online_list", no_argument, 0, 'l'},		/** 获取在线用户列表*/
    {"policy", required_argument, 0, 'p'},		/** 获取在线用户生效的策略 */
    {"client_log", required_argument, 0, 'c'},	/** 获取客户端日志 */
    {0, 0, 0, 0},
};

const char *short_options = "hvlp:c:";

int main(int argc, char* argv[])
{
    printf("filename: %s %s\n", __FILE__, argv[0]);

    int optstring;
    printf("default optind: %d\n", optind);
    while((optstring = getopt_long(argc, (char * const*)argv, short_options, long_options, NULL)) != -1) {
        printf("optind: %d\n", optind);
        switch(optstring) {
        case 'h':
            print_help();
            break;
        case 'l':
            print_help();
            break;
        case 'p':
            printf("p argument: %s\n", optarg);
            break;
        case 'c':
            printf("c argument: %s\n", optarg);
            break;
        case 'v':
            print_help();
            break;
        case '?':
            printf("invalid params\n");
            break;
        default:
            printf("will not enter here\n");
            break;
        }
    }
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
filename: k.cpp ./a.out
default optind: 1
[root@ubuntu0006:~/cmake] #./a.out -t -l -p 123
filename: k.cpp ./a.out
default optind: 1
./a.out: invalid option -- 't'
optind: 2
invalid params
optind: 3

Usage:devicehelper [option]...

option:
        -h, --help:                                             Show help
        -l, --online_list:                                      Get all online users
        -p, --policy [usernmae]:                                Get effective policy type and policy details by username
        -c, --client_log [username] [client_sn]:                        Get client log by username and client sn
        -v, --version:                                          Show the supported versions

optind: 5
p argument: 123

[root@ubuntu0006:~/cmake] #./a.out --help
filename: k.cpp ./a.out
default optind: 1
optind: 2

Usage:devicehelper [option]...

option:
        -h, --help:                                             Show help
        -l, --online_list:                                      Get all online users
        -p, --policy [usernmae]:                                Get effective policy type and policy details by username
        -c, --client_log [username] [client_sn]:                        Get client log by username and client sn
        -v, --version:                                          Show the supported versions

[root@ubuntu0006:~/cmake] #./a.out -help
filename: k.cpp ./a.out
default optind: 1
optind: 1

Usage:devicehelper [option]...

option:
        -h, --help:                                             Show help
        -l, --online_list:                                      Get all online users
        -p, --policy [usernmae]:                                Get effective policy type and policy details by username
        -c, --client_log [username] [client_sn]:                        Get client log by username and client sn
        -v, --version:                                          Show the supported versions

./a.out: invalid option -- 'e'
optind: 1
invalid params
optind: 1

Usage:devicehelper [option]...

option:
        -h, --help:                                             Show help
        -l, --online_list:                                      Get all online users
        -p, --policy [usernmae]:                                Get effective policy type and policy details by username
        -c, --client_log [username] [client_sn]:                        Get client log by username and client sn
        -v, --version:                                          Show the supported versions

./a.out: option requires an argument -- 'p'
optind: 2
invalid params
*/
