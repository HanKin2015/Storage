/**
* 文 件 名: fscanf_fprintf.c
* 文件描述: fscanf和fprintf函数读写文件
* 作    者: HanKin
* 创建日期: 2021.06.10
* 修改日期：2022.08.09
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#ifdef _WIN32
    #include <io.h>
    #define R_OK 4 /* Test for read permission. */
    #define W_OK 2 /* Test for write permission. */
    #define X_OK 1 /* Test for execute permission. */
    #define F_OK 0 /* Test for existence. */
#else
    #include <unistd.h>
    #include <sys/stat.h>
    #include <sys/types.h>
#endif

static bool file_write(const char *file_path, const char *data)
{
    printf("--------- %s ---------\n", __FUNCTION__);
    assert(file_path);
    assert(data);
    
    FILE *fp = NULL;
    fp = fopen(file_path, "a");
    if (fp == NULL) {
        printf("open [%s] file failed!\n", file_path);
        return false;
    }

    //保存数据: 时间/地点/人数/天气/备注
    time_t t = time(0);
    char *cur_time = (char*)malloc(64);
    memset(cur_time, 0, 64);
    strftime(cur_time, 64, "%Y/%m/%d %X %A 本年第%j天 %z", localtime(&t));

    const char *location = "CS";
    const char *count = "6";
    const char *weather = "cloud";
    const char *remark = "well good";

    fprintf(fp, "%s,%s,%s,%s,%s;\n", cur_time, location, count, weather, remark);

    free(cur_time);
    cur_time = NULL;
    fclose(fp);
    fp = NULL;
    return true;
}

static bool file_read(const char *file_path)
{
    printf("--------- %s ---------\n", __FUNCTION__);
    assert(file_path);

    FILE* fp = NULL;
    fp = fopen(file_path, "r");
    if (fp == NULL) {
        printf("open [%s] file failed!\n", file_path);
        return false;
    }

    char *data = (char *)malloc(64);
    memset(data, 0, 64);
    while (fscanf(fp, "%s\n", data) == 1) {
        printf("%s\n", data);
        memset(data, 0, 64);
    }
    
    free(data);
    data = NULL;
    fclose(fp);
    fp = NULL;
    return true;
}

int main(int argc, char *argv[])
{
    const char* dir_path = "./usb/";
    //判断文件夹是否存在,不存在就创建
    if (!access(dir_path, F_OK)) {
        printf("%s directory is exist.\n", dir_path);
    } else {
        #ifdef _WIN32
            mkdir(dir_path);
        #else
            mkdir(dir_path, 0666);
        #endif
        printf("%s directory is not exist.\n", dir_path);
    }

    const char *udev_opt_log_prefix = "udev_opt_";
    const char *vmid = "3158";
    size_t len = strlen(udev_opt_log_prefix) + strlen(vmid) + strlen(".log") + 1;
    char *udev_opt_log_path = (char*)malloc(len);
    memset(udev_opt_log_path, 0, len);
    snprintf(udev_opt_log_path, len, "%s%s.log", udev_opt_log_prefix, vmid);
    //判断文件是否存在
     if (!access(udev_opt_log_path, F_OK)) {
        printf("%s file is exist.\n", udev_opt_log_path);
     } else {
        printf("%s file is not exist.\n", udev_opt_log_path);
     }
    
    file_write(udev_opt_log_path, "hello world");
    file_read(udev_opt_log_path);
    return 0;
}
