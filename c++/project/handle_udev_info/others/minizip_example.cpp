/**
* 文 件 名: minizip_example.cpp
* 文件描述: 在C++中，可以使用第三方库来实现解压zip包的功能。其中，比较常用的库有zlib和minizip。
* 备    注：在使用minizip库时，需要将minizip文件夹中的头文件和源文件添加到项目中，并在编译时链接minizip库。
* 作    者: HanKin
* 创建日期: 2023.05.18
* 修改日期：2023.05.18
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <iostream>
#include <string>
#include "minizip/zip.h"
#include "minizip/unzip.h"

int main() {
    std::string zip_file = "test.zip";
    std::string extract_path = "extracted/";

    unzFile uf = unzOpen(zip_file.c_str());
    if (uf == NULL) {
        std::cerr << "Failed to open zip file: " << zip_file << std::endl;
        return 1;
    }

    unz_global_info gi;
    if (unzGetGlobalInfo(uf, &gi) != UNZ_OK) {
        std::cerr << "Failed to get global info of zip file: " << zip_file << std::endl;
        unzClose(uf);
        return 1;
    }

    char filename_inzip[256];
    unz_file_info file_info;
    uLong i;
    for (i = 0; i < gi.number_entry; i++) {
        if (unzGetCurrentFileInfo(uf, &file_info, filename_inzip, sizeof(filename_inzip), NULL, 0, NULL, 0) != UNZ_OK) {
            std::cerr << "Failed to get file info of zip file: " << zip_file << std::endl;
            unzClose(uf);
            return 1;
        }

        std::string filename = extract_path + filename_inzip;
        if (filename.back() == '/') {
            // Create directory
            if (mkdir(filename.c_str(), 0777) != 0) {
                std::cerr << "Failed to create directory: " << filename << std::endl;
                unzClose(uf);
                return 1;
            }
        } else {
            // Create file
            FILE* fp = fopen(filename.c_str(), "wb");
            if (fp == NULL) {
                std::cerr << "Failed to create file: " << filename << std::endl;
                unzClose(uf);
                return 1;
            }

            char buffer[4096];
            int read_size;
            if (unzOpenCurrentFile(uf) != UNZ_OK) {
                std::cerr << "Failed to open file in zip file: " << filename_inzip << std::endl;
                fclose(fp);
                unzClose(uf);
                return 1;
            }
            while ((read_size = unzReadCurrentFile(uf, buffer, sizeof(buffer))) > 0) {
                fwrite(buffer, 1, read_size, fp);
            }
            fclose(fp);
            unzCloseCurrentFile(uf);
        }

        if (i + 1 < gi.number_entry) {
            if (unzGoToNextFile(uf) != UNZ_OK) {
                std::cerr << "Failed to go to next file in zip file: " << zip_file << std::endl;
                unzClose(uf);
                return 1;
            }
        }
    }

    unzClose(uf);
    return 0;
}
