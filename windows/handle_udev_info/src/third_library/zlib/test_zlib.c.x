#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h> 
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>

#ifdef _WIN32
# include <direct.h>
# include <io.h>
#else
# include <unistd.h>
# include <utime.h>
#endif

#include "unzip.h"
#include "zip.h"
#define ZIP_SUFFIX ".zip"
#include <sys/stat.h>
#include <sys/types.h>
#define READ_SIZE 256
#define MAX_FILENAME 256
#define DIR_DELIMITER '/'
#define MALLOC_MAX_LENGTH 256

/**
 * 判断文件是否为zip后缀
 */
static int is_zip_suffix(const char *file_name)
{
    const char *suffix = strrchr(file_name, '.');
    //printf("suffix: %s\n", suffix);
    return strncmp(suffix, ZIP_SUFFIX, strlen(ZIP_SUFFIX));
}

/*
 * 创建多级目录
 * @param [in]path  路径
 * @return true创建成功, false创建失败
 */
static int mkdirs(const char *path) 
{
    char str[MALLOC_MAX_LENGTH];    
    strncpy(str, path, MALLOC_MAX_LENGTH);
    
    int length = strlen(str);
    int i;
    for (i = 0; i < length; i++) {
        if (str[i] == '/') {
            str[i] = '\0';
            if (strlen(str) && access(str, F_OK)) {
                if (mkdir(str, S_IRWXU)) {
                    printf("[usb record] mkdir folder failed");
                    return -1;
                }
            }
            str[i] = '/';
        }
    }
    //可能末尾未加斜线/
    if (length > 0 && access(str, F_OK)) {
        if (mkdir(str, S_IRWXU)) {
            printf("[usb record] mkdir folder failed");
            return -1;
        }
    }
    return 0;
}

/*
 * @brief 获取文件名
 * @note  一定能找到/符号
 *
 * @param file_path   [in] 文件路径
 * @param target_path [in] 目标路径
 * @return 无
 */
static void move_file(const char *file_path, const char *target_path)
{
    const char *file_name = strrchr(file_path, '/');
    char new_file_path[MAX_FILENAME] = {0};
    strncpy(new_file_path, target_path, strlen(target_path));
    strncat(new_file_path, file_name+1, strlen(file_name)-1);
    rename(file_path, new_file_path);
}

/*
 * @brief 删除文件夹
 * @note
 *
 * @param dir_path   [in] 文件夹路径
 * @return 无
 */
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

/*
 * @brief 解压zip文件到目标文件夹
 * @note  
 *
 * @param path [in] 数据文件路径
 * @param target_dir [in] 目标文件夹路径
 * @return 无
 */
void unzip_file(const char *zfile_path, const char *tmp_path, const char *target_path)
{
    unzFile zfile = NULL;
    unz_global_info zfile_ginfo;
    char read_buffer[READ_SIZE];
    int i = 0;
    unz_file_info file_info;
    char file_name[MAX_FILENAME];
    char file_path[MAX_FILENAME];
    FILE *fp = NULL;
    int error = UNZ_OK;
    size_t file_len;
    
    if (zfile_path == NULL || strlen(zfile_path) == 0) {
        printf("file path [%s] error!\n", zfile_path);
        goto FINI;
    }
    
    if (is_zip_suffix(zfile_path) != 0) {
        printf("file type [%s] error!\n", zfile_path);
        goto FINI;
    }
    
    if (access(tmp_path, F_OK)) {
        mkdirs(tmp_path);
    }
    if (access(target_path, F_OK)) {
        mkdirs(target_path);
    }

    zfile = unzOpen(zfile_path);
    if (zfile == NULL) {
        printf("not found\n");
        goto FINI;
    }

    if (unzGetGlobalInfo(zfile, &zfile_ginfo) != UNZ_OK) {
        printf("unzGetGlobalInfo failed\n");
        goto FINI;
    }

    if (unzGoToFirstFile(zfile) != UNZ_OK) {
        printf("unzGoToFirstFile failed\n");
        goto FINI;
    }
    for (i = 0; i < zfile_ginfo.number_entry; i++) {
        if (unzGetCurrentFileInfo(
                zfile,
                &file_info,
                file_name,
                MAX_FILENAME,
                NULL, 0, NULL, 0)
            != UNZ_OK) {
            printf("could not read file info\n");
            goto FINI;
        }
        
        printf("file_name: %s\n", file_name);
        
        memset(file_path, 0, sizeof(file_path));
        strncpy(file_path, tmp_path, strlen(tmp_path));
        strncat(file_path, file_name, strlen(file_name));
        
        //printf("file_path: %s\n", file_path);
        
        file_len = strlen(file_path);
        if (file_path[file_len - 1] == DIR_DELIMITER) {
            //printf("mkdir directory [%s]\n", file_path);
            mkdir(file_path, 0775);
        } else {
            if (unzOpenCurrentFile(zfile) != UNZ_OK) {
                printf("could not open file\n");
                goto FINI;
            }

            fp = fopen(file_path, "wb");
            if (fp == NULL) {
                printf("could not open destination file\n");
                unzCloseCurrentFile(zfile);
                goto FINI;
            }

            do {
                error = unzReadCurrentFile(zfile, read_buffer, READ_SIZE);
                if (error < 0) {
                    printf("error %d\n", error);
                    unzCloseCurrentFile(zfile);
                    goto FINI;
                }
                if (error > 0) {
                    fwrite(read_buffer, error, 1, fp);
                }
            } while (error > 0);
            fclose(fp);
            fp = NULL;
            
            if (is_zip_suffix(file_path) == 0) {
                unzip_file(file_path, tmp_path, target_path);
            } else {
                move_file(file_path, target_path);
            }
        }
 
        unzCloseCurrentFile(zfile);
        if (unzGoToNextFile(zfile) != UNZ_OK) {
            printf("cound not read next file\n");
            goto FINI;
        }
    }

FINI:
    if (zfile) {
        unzClose(zfile);
        zfile = NULL;
    }
    if (fp) {
        fclose(fp);
        fp = NULL;
    }
    return;
}

int main(int argc, char *argv[])
{
    clock_t start_time = clock();
    
    const char *zfile_path = "./外设信息.zip";
    const char *tmp_path = "./tmp/";
    const char *target_path = "./target/";
    unzip_file(zfile_path, tmp_path, target_path);
    del_dir(tmp_path);
    
    clock_t spent_time = clock() - start_time;
    printf("exec spent time %lf s.\n", (double)spent_time / CLOCKS_PER_SEC);
    return 0;
}

