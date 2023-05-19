/**
* 文 件 名: write_file.cpp
* 文件描述: 读取文件内容
* 参    考: https://blog.csdn.net/zinnc/article/details/90723432
* 作    者: HanKin
* 创建日期: 2022.08.12
* 修改日期：2022.08.12
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include <fstream>
#include <chrono>
#include <vector>
#include <cstdint>
#include <numeric>
#include <random>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <unistd.h>
#include <fcntl.h>

std::vector<uint64_t> data;

std::vector<uint64_t> GenerateData(std::size_t bytes)
{
    assert(bytes % sizeof(uint64_t) == 0);
    std::vector<uint64_t> data(bytes / sizeof(uint64_t));
    std::iota(data.begin(), data.end(), 0);
    std::shuffle(data.begin(), data.end(), std::mt19937{ std::random_device{}() });
    return data;
}

long long option_1(std::size_t bytes)
{
    auto startTime = std::chrono::high_resolution_clock::now();
    auto myfile = std::fstream("file.binary", std::ios::out | std::ios::binary);
    myfile.write((char*)&data[0], bytes);
    myfile.close();
    auto endTime = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
}

long long option_2(std::size_t bytes)
{
    auto startTime = std::chrono::high_resolution_clock::now();
    FILE* file = fopen("file.binary", "wb");
    fwrite(&data[0], 1, bytes, file);
    fclose(file);
    auto endTime = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
}

long long option_3(std::size_t bytes)
{
    auto startTime = std::chrono::high_resolution_clock::now();
    int file_fd = open("file.binary", O_WRONLY | O_CREAT, 00666);
    write(file_fd, &data[0], bytes);
    close(file_fd);
    auto endTime = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
}

int main(int argc, char * argv[])
{
    if(argc < 2)
    {
        std::cout << "Need argv[1],like 100 (Unit:MB)" << std::endl;	
        return 0;
    }

    const std::size_t kB = 1024;
    const std::size_t MB = 1024 * kB;
    const std::size_t GB = 1024 * MB;

    size_t size = atoi(argv[1]) *MB;	

    data = GenerateData(size);

    std::cout << "Testing begin...."  << std::endl;

    std::cout << "option1, " << size / MB << "MB: " << option_1(size) << "ms" << std::endl;
    std::cout << "option2, " << size / MB << "MB: " << option_2(size) << "ms" << std::endl;
    std::cout << "option3, " << size / MB << "MB: " << option_3(size) << "ms" << std::endl;

    unlink("file.binary");

    return 0;
}
