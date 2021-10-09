#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h> 

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


/**
 * 判断文件是否为zip后缀
 */
static int is_zip_suffix(const char *file_name)
{
    const char *suffix = strrchr(file_name, '.');
    return strncmp(suffix, ZIP_SUFFIX, strlen(ZIP_SUFFIX));
}

/*
 * @brief 解压zip文件到目标文件夹
 * @note  
 *
 * @param path [in] 数据文件路径
 * @param target_dir [in] 目标文件夹路径
 * @return 无
 */
void unzip_file(const char *zfile_path, const char *target_path)
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
    struct stat file_stat;
    size_t file_len;
    
    if (zfile_path == NULL || strlen(zfile_path) == 0) {
        printf("file path [%s] error!\n", zfile_path);
        goto FINI;
    }
    
    if (is_zip_suffix(zfile_path) != 0) {
        printf("file type [%s] error!\n", zfile_path);
        goto FINI;
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

        memset(file_path, 0, sizeof(file_path));
        strncpy(file_path, target_path, strlen(target_path));
        strncat(file_path, file_name, strlen(file_name));
        
        //printf("file_path: %s\n", file_path);
        
        file_len = strlen(file_path);
        if (file_path[file_len - 1] == DIR_DELIMITER) {
            printf("mkdir directory [%s]\n", file_path);
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
    const char *zfile_path = "./test.zip";
    const char *target_path = "./tmp/";
    unzip_file(zfile_path, target_path);
    return 0;
}

