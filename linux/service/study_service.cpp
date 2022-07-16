/**
* 文 件 名: study_service.cpp
* 文件描述: 学习Linux系统的服务及其使用
* 作    者: HanKin
* 创建日期: 2022.07.04
* 修改日期：2022.07.04
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#define MAX_BUF_LEN 64
//定义程序名字为usbipd
#undef  PROGNAME
#define PROGNAME "usbipd"
#define PACKAGE_STRING "usbip-utils 1.1.1"
//版本字符串
static const char usbip_version_string[] = PACKAGE_STRING;

static int action(int daemonize)
{
    if (daemonize) {
        if (daemon(0, 0) < 0) {
            printf("daemonizing failed: %s", strerror(errno));
            return -1;
        }
        umask(0);
    }

    do {
        sleep(5);
        FILE *fp = fopen("/home/study_service", "a");
        
        // 记录当前时间(外设插拔) 获取日期(文件夹)
        char cur_time[MAX_BUF_LEN] = {0}, cur_date[MAX_BUF_LEN] = {0};
        time_t tm = time(NULL);
        strftime(cur_time, sizeof(cur_time), "%Y/%m/%d %H:%M:%S", localtime(&tm));
        strftime(cur_date, sizeof(cur_date), "%Y%m%d/", localtime(&tm));
        
        fprintf(fp, "%s: %d\n", cur_time, daemonize);
        fclose(fp);
        fp = NULL;
    } while (true);
    return 0;
}

//帮助字符串
static const char usbipd_help_string[] =
    "usage: usbipd [options]			\n"
    "	-D, --daemon				\n"
    "		Run as a daemon process.	\n"
    "						\n"
    "	-d, --debug				\n"
    "		Print debugging information.	\n"
    "						\n"
    "	-h, --help 				\n"
    "		Print this help.		\n"
    "						\n"
    "	-v, --version				\n"
    "		Show version.			\n";

/**
* 帮助函数
* @para void
* @return 0 void
*/
static void usbipd_help(void)
{
    printf("%s\n", usbipd_help_string);
	return;
}

int main(int argc, char *argv[])
{
    static const struct option longopts[] =
    {
        { "daemon",  no_argument, NULL, 'D' },
        { "debug",   no_argument, NULL, 'd' },
        { "help",    no_argument, NULL, 'h' },
        { "version", no_argument, NULL, 'v' },
        { NULL,	     0,           NULL,  0  }
    };

    enum
    {
        cmd_standalone_mode = 1,
        cmd_help,
        cmd_version
    } cmd;

    int daemonize = 0;
    int opt = 0;
    int rc = -1;

    if (geteuid() != 0) {
        printf("not running as root?\n");
	}

    cmd = cmd_standalone_mode;
    for (;;) {
        opt = getopt_long(argc, argv, "Ddhv", longopts, NULL);

        if (opt == -1)
            break;

        switch (opt) {
        case 'D':
            daemonize = 1;
            break;
        case 'd':
            break;
        case 'h':
            cmd = cmd_help;
            break;
        case 'v':
            cmd = cmd_version;
            break;
        case '?':
            usbipd_help();
        default:
            goto err_out;
        }
	}
		
	switch (cmd)
	{
	case cmd_standalone_mode:
		rc = action(daemonize);
		break;
	case cmd_version:
		printf(PROGNAME " (%s)\n", usbip_version_string);
		rc = 0;
		break;
	case cmd_help:
		usbipd_help();
		rc = 0;
		break;
	default:
		usbipd_help();
		goto err_out;
	}

err_out:
    return (rc > -1 ? EXIT_SUCCESS : EXIT_FAILURE);
}