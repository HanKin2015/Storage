#include <iostream>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>

/* 增加文件 */
/* 删除文件 */
static void del_file(const char *file_path)
{
    int ret = remove(file_path);
    if (ret == 0) {
        printf("delete file [%s] success\n", file_path);
    } else {
        printf("delete file [%s] failed, %s\n", file_path, strerror(errno));
    }
}

/* 删除文件夹 */
static int del_dir(const char *dir_path)
{
    DIR *dir;
    struct dirent *dirinfo;
    struct stat statbuf;
    char new_dir_path[256];
    lstat(dir_path, &statbuf);
 
    if (S_ISREG(statbuf.st_mode)) {
        remove(dir_path);
    } else if (S_ISDIR(statbuf.st_mode)) {
        if ((dir = opendir(dir_path)) == NULL) {
            perror("opendir");
            return -1;
        }   
 
        while ((dirinfo = readdir(dir)) != NULL) {
            if (strcmp(dirinfo->d_name, ".") == 0 || strcmp(dirinfo->d_name, "..") == 0) continue;
            memset(new_dir_path, 0, sizeof(new_dir_path));
            strncpy(new_dir_path, dir_path, sizeof(new_dir_path));
            strncat(new_dir_path, "/", 1);
            strncat(new_dir_path, dirinfo->d_name, strlen(dirinfo->d_name));
            del_dir(new_dir_path);
        }
        closedir(dir);
        rmdir(dir_path);
    } else {
        perror("unkonow");
        return -2;
    }
 
    return 0;
}

/* 判断文件或文件夹是否存在 */
static int is_exist(const char *path)
{
    return access(path, F_OK);
}

int main()
{
    del_file("./file");
    
    int ret = del_dir("./dir");
    if (ret == 0) {
        printf("delete directory [./dir] success\n");
    } else {
        printf("delete directory [./dir] failed, %s\n", strerror(errno));
    }
    
    if (is_exist("./handle_udev_info") == 0) {
        printf("yes\n");
    }
    if (is_exist("./handle_udv_info") != 0) {
        printf("yes\n");
    }
    if (is_exist("./safe_function.cpp") == 0) {
        printf("yes\n");
    }
    return 0;
}
