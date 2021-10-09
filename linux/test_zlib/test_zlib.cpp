#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <iostream>

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
#define dir_delimter '/'

//解压代码片段 本例子将代码解压到和zip文件同一目录下
void ZipUtil::UnzipFile(const char *strFilePath)
{
//    LOGDBG("===========================");
    clock_t start = clock();
    if (strFilePath == NULL || strlen(strFilePath) == 0) {
        printf("Zip Path Error!%s\n", strFilePath);
        return; 
    }
 
    std::string rootPath = strFilePath;
    if (rootPath.substr(rootPath.find_last_of(".")).compare(ZIP_SUFFIX) != 0) {
        printf("File Type Error!%s \t", strFilePath);
        return;
    }
    rootPath = rootPath.substr(0, rootPath.find_last_of("/")) + "/";
 
    unzFile zipFile = unzOpen(strFilePath);// Open the zip file
    if (zipFile == NULL) {
        printf("not found\n");
        return;
    }
 
    unz_global_info globalInfo;
    if (UNZ_OK != unzGetGlobalInfo(zipFile, &globalInfo)) {
        printf("获取全局zip信息失败!\n");
        unzClose(zipFile);
        zipFile = NULL;
        return;
    }
 
    int zipInfo = unzGoToFirstFile(zipFile);
    if (UNZ_OK != zipInfo) {
        printf("无法获取zip包内文件信息zip包可能是null的!\n");
        unzClose(zipFile);
        zipFile = NULL;
        return;
    }
    char read_buffer[READ_SIZE];
 
    uLong i;
    for (i = 0; i < globalInfo.number_entry; ++i) {
        // Get info about current file.
        unz_file_info file_info;
        char filename[MAX_FILENAME];
        if (unzGetCurrentFileInfo(
                zipFile,
                &file_info,
                filename,
                MAX_FILENAME,
                NULL, 0, NULL, 0)
            != UNZ_OK) {
            printf("could not read file info\n");
            unzClose(zipFile);
            return;
        }
        //名字拼接 解压到同一目录下
        std::string fileNameStr = rootPath + filename;
        strncpy(filename, fileNameStr.c_str(), fileNameStr.length() + 1);
 
        // Check if this entry is a directory or file.
        const size_t filename_length = strlen(filename);
        if (filename[filename_length - 1] == dir_delimter) {
            // Entry is a directory, so create it.
            printf("dir:%s\n", filename);
            mkdir(filename, 0775);
        }
        else {
            // Entry is a file, so extract it.
            printf("file:%s\n", filename);
            if (unzOpenCurrentFile(zipFile) != UNZ_OK) {
                printf("could not open file\n");
                unzClose(zipFile);
                return;
            }
 
            // Open a file to write out the data.
            FILE *out = fopen(filename, "wb");
            if (out == NULL) {
                printf("could not open destination file\n");
                unzCloseCurrentFile(zipFile);
                unzClose(zipFile);
                return;
            }
 
            int error = UNZ_OK;
            do {
                error = unzReadCurrentFile(zipFile, read_buffer, READ_SIZE);
                if (error < 0) {
                    printf("error %d\n", error);
                    unzCloseCurrentFile(zipFile);
                    unzClose(zipFile);
                    return;
                }
                // Write data to file.
                if (error > 0) {
                    fwrite(read_buffer, error, 1, out);// You should check return of fwrite...
                }
            } while (error > 0);
            fclose(out);
        }
 
        unzCloseCurrentFile(zipFile);
        // Go the the next entry listed in the zip file.
        if ((i + 1) < globalInfo.number_entry) {
            if (unzGoToNextFile(zipFile) != UNZ_OK) {
                printf("cound not read next file\n");
                unzClose(zipFile);
                return;
            }
        }
    }
    unzClose(zipFile);
    clock_t end = clock();
    printf("Elapsed Time %f\n", (double) (end - start));
}

int main(int argc, char *argv[])
{

    UnzipFile(argv[1]);

    return 0;
}

