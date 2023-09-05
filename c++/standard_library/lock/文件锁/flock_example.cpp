/**
* 文 件 名: flock_example.cpp
* 文件描述: 日志类版本，支持多进程并使用文件锁来避免多个进程同时写入日志文件
* 作    者: HanKin
* 创建日期: 2023.09.01
* 修改日期：2023.09.01
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>   // flock

class Logger
{
public:
    Logger(const std::string& filename) : m_filename(filename)
    {
        m_file.open(filename, std::ios::app);
        if (!m_file.is_open()) {
            std::cerr << "Failed to open log file: " << filename << std::endl;
        }
    }

    ~Logger()
    {
        if (m_file.is_open()) {
            m_file.close();
        }
    }

    void log(const std::string& message)
    {
        // 写入日志
        m_file << message << std::endl;
        m_file.flush();
    }

private:
    std::string m_filename;
    std::ofstream m_file;
    std::mutex m_mutex;
};

int main()
{
    Logger logger("test.log");
    std::mutex m_mutex;
    std::string m_filename = "test.log";

    pid_t pid = fork();
    if (pid == 0) {
        // 这行不能保证多进程日志写入
        //std::lock_guard<std::mutex> lock(m_mutex);
        // 获取文件锁
        int fd = open(m_filename.c_str(), O_WRONLY | O_CREAT, 0644);
        if (fd == -1) {
            std::cerr << "Failed to open log file: " << m_filename << std::endl;
            return;
        }
        flock(fd, LOCK_EX);
        // 子进程写入日志
        for (int i = 0; i < 100000; i++) {
            std::string str = "== " + std::to_string(i) + " Child process log message";
            logger.log(str);
        }
        // 释放文件锁
        flock(fd, LOCK_UN);
        close(fd);
    } else if (pid > 0) {
        // 获取文件锁
        int fd = open(m_filename.c_str(), O_WRONLY | O_CREAT, 0644);
        if (fd == -1) {
            std::cerr << "Failed to open log file: " << m_filename << std::endl;
            return;
        }
        flock(fd, LOCK_EX);
        // 父进程写入日志
        for (int i = 0; i < 100000; i++) {
            std::string str = "** " + std::to_string(i) + " Child process log message";
            logger.log(str);
        }
        // 释放文件锁
        flock(fd, LOCK_UN);
        close(fd);
    } else {
        std::cerr << "Failed to fork process" << std::endl;
        return 1;
    }

    return 0;
}