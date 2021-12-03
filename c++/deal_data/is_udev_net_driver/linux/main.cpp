/**
* 文 件 名: study_libusb.cpp
* 文件描述: 学习libusb
* 作    者: HanKin
* 备    注: 编译需要安装libusb库,并且需要增加-lusb-1.0 -lpthread -lm参数
* 创建日期: 2021.10.12
* 修改日期：2021.10.12
*
* Copyright (c) 2021 HanKin. All rights reserved.
*/

#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdio>
#include <string>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <set>
#include <map>
#include <ctime>
#include <sys/time.h>
#include <unistd.h>
#include "usb_net_driver_list.h"
#include <libusb-1.0/libusb.h>
#include <ftw.h>
#include <vector>
#include <errno.h>
using namespace std;

#define INNER_NET_FILE "./udev_net_driver_vpid.txt"
#define Info printf
#define NET_CLASS_PATH "/sys/class/net/"
#include <dirent.h>
#include <vector>
#define LOG_DEBUG printf
#define LOG_INFO printf
#define LOG_ERROR printf

// 读取文件方案
void readInnerUdevNetDriverVpid(unsigned short v, unsigned short p)
{
    Info("\n-----%s [%d]-----\n", __FUNCTION__, __LINE__);
    
    FILE *fp = NULL;
    unsigned short vid = 0;
    unsigned short pid = 0;
    
    fp = fopen(INNER_NET_FILE, "r");
    if (fp == NULL) {
        Info("fopen file [%s] failed\n", INNER_NET_FILE);
        return;
    }
    
    int index = 0;
    while (fscanf(fp, "0x%hx,0x%hx\n", &vid, &pid) != EOF) {
        //Info("0x%04x, 0x%04x\n", vid, pid);
        //break;
        index++;
        //Info("index: %d\n", index);
        if (v == vid && p == pid) {
            Info("index: %d, [0x%04x:0x%04x]\n", index, vid, pid);
        }
    }
    return;
}

// 内联函数
inline bool is_in_usb_net_driver_list(unsigned short vid, unsigned short pid)
{
    Info("\n-----%s [%d]-----\n", __FUNCTION__, __LINE__);
    
    for (int i = 0; i < USB_NET_DRIVER_NUM; i++) {
        if (usb_net_driver_ist[i][0] == vid && usb_net_driver_ist[i][1] == pid) {
            Info("this usb device in usb net driver list, index: %d, [0x%04x:0x%04x]\n", i + 1, vid, pid);
            return true;
        }
    }
    return false;
}

#define MAX_PATH_LEN 256
static bool is_usb_net_device(vector<string> net_symlink_file_paths, string udev_path)
{
    Info("\n-----%s [%d]-----\n", __FUNCTION__, __LINE__);
    
    char real_path[MAX_PATH_LEN];
    std::string real_path_str;
    int ret;
    int index;

    std::vector<std::string>::iterator it = net_symlink_file_paths.begin();
    //for (std::string net_symlink_file_path : net_symlink_file_paths) {
    for (it != net_symlink_file_paths.end(); it++) {
        memset(real_path, 0, MAX_PATH_LEN);
        ret = readlink((*it).c_str(), real_path, MAX_PATH_LEN);
        if (ret == -1) {
            LOG_ERROR("readlink failed, ret=%d, err=%u, %s", errno, strerror(errno));
            return false;
        }

        real_path_str = real_path;
        index = real_path_str.find(udev_path);
        if (index == -1) {
            LOG_DEBUG("real_path: %s, udev_path: %s", real_path, udev_path.c_str());
            continue;
        }
        LOG_DEBUG("real_path: %s, udev_path: %s\n", real_path, udev_path.c_str());
        return true;
    }
    return false;
}

#define MAX_PORTS_NUM 256
static bool get_usb_device_path(libusb_device *udev, string &udev_path)
{
    Info("\n-----%s [%d]-----\n", __FUNCTION__, __LINE__);
    assert(udev != NULL);
    
    uint8_t ports[MAX_PORTS_NUM];
    int bus = libusb_get_bus_number(udev);
    
    int ports_num = libusb_get_port_numbers(udev, ports, MAX_PORTS_NUM);
    if (ports_num < 0) {
        perror("libusb_get_port_numbers");
        return false;
    }
    
    for (int i = 0; i < ports_num; i++) {
        Info("%d ", ports[i]);
    }
    Info("\n");
    
    std::stringstream ss;
    ss << bus;
    ss << "-";
    ss << (unsigned int)ports[0];
    for(int i = 1; i < ports_num; i++) {
        ss << ".";
        ss << (unsigned int)ports[i];
    }
    udev_path = ss.str();
    Info("udev_path: %s\n", udev_path.data());
    return true;
}

static libusb_device *find_udev(unsigned short vid, unsigned short pid)
{
    Info("\n-----%s [%d] 0x%04x:0x%04x-----\n", __FUNCTION__, __LINE__, vid, pid);
    
    static libusb_device **udevs;
    int ret;
    ssize_t udevs_cnt;
    struct libusb_device_descriptor desc;

    ret = libusb_init(NULL);
    if (ret < 0) {
        perror("libusb_init");
        return NULL;
    }

    udevs_cnt = libusb_get_device_list(NULL, &udevs);
    if (udevs_cnt < 0) {
        perror("libusb_get_device_list");
        return NULL;
    }
    
    for (int i = 0; i < udevs_cnt; i++) {
        libusb_device *udev = udevs[i];
        ret = libusb_get_device_descriptor(udev, &desc);
        if (ret < 0) {
            perror("libusb_get_device_descriptor");
            return NULL;
        }

        printf("%04x:%04x (bus %d, port %d, device %d, speed %d, class 0x%x)\n",
            desc.idVendor, desc.idProduct, libusb_get_bus_number(udev), 
            libusb_get_port_number(udev), libusb_get_device_address(udev), 
            libusb_get_device_speed(udev), desc.bDeviceClass);
            
        if (desc.idVendor == vid && desc.idProduct == pid) {
            Info("find usb device [0x%04x:0x%04x].\n", vid, pid);
            return udev;
        }
    }
    return NULL;
}

int fn(const char* file, const struct stat* sb, int flag)
{
    Info("\n-----%s [%d]-----\n", __FUNCTION__, __LINE__);
    
    char    line[256] = {0};
    int     count = 0;

    if (flag == FTW_F) {    // 如果是文件
        cout<<"The File's name : "<<file<<endl;
        /*
        ifstream file(file);
        if (file.isopen()) {
            file.getline(line, 100);
            cout<<line<<endl;
        }
        */
       
        FILE*   fp;
        fp = fopen(file, "r");
        fgets(line, sizeof(line), fp);
        fclose(fp);
        printf("Line's data######## : %s\n", line);
       
    }else if (flag == FTW_D) {  // 如果是子目录(遍历的第一个是根目录)
        cout<<"The Directory name : "<<file<<endl;
    }

    return 0;
}

static bool get_net_symlink_file_path(vector<string> &net_symlink_file_paths)
{
    Info("\n-----%s [%d]-----\n", __FUNCTION__, __LINE__);
    
    struct dirent *st_dirent;
    DIR *dir;
    string net_symlink_file_path;
    
    dir = opendir(NET_CLASS_PATH);
    if (dir == NULL) {
        LOG_ERROR("opendir failed, err=%u, %s", errno, strerror(errno));
        return false;
    }
    while ((st_dirent = readdir(dir)) != NULL) {
        if (st_dirent->d_type == DT_LNK) {
            net_symlink_file_path = NET_CLASS_PATH;
            net_symlink_file_path += st_dirent->d_name;
            net_symlink_file_paths.push_back(net_symlink_file_path);
            LOG_DEBUG("net_symlink_file_path: %s", net_symlink_file_path.c_str());
        }
    }
    closedir(dir);
    dir = NULL;
    return true;
}

static bool is_ethernet(libusb_device *device, unsigned short vid, unsigned short pid)
{
    bool ret;
    string udev_path;
    vector<string> net_symlink_file_paths;
    
    // 通过网卡驱动名单判断是否是网卡
    ret = is_in_usb_net_driver_list(vid, pid);
    if (ret) {
        LOG_INFO("device 0x%04x 0x%04x is in usb net driver list.\n", vid, pid);
        return true;
    }
    
    // 获取设备路径(bus-port1.port2...)
    ret = get_usb_device_path(device, udev_path);
    if (!ret) {
        LOG_ERROR("device 0x%04x 0x%04x get usb device path failed!\n", vid, pid);
        return false;
    }

    // 获取网卡软链接路径
    ret = get_net_symlink_file_path(net_symlink_file_paths);
    if (!ret) {
        LOG_ERROR("device 0x%04x 0x%04x get net symbolic link file path failed!\n", vid, pid);
        return false;
    }

    // 通过软链接判断是否是网卡
    ret = is_usb_net_device(net_symlink_file_paths, udev_path);
    if (ret) {
        LOG_INFO("device 0x%04x 0x%04x is ethernet adapter.\n", vid, pid);
        return true;
    }
    LOG_INFO("device 0x%04x 0x%04x is not ethernet adapter.\n", vid, pid);
    return false;
}

int main()
{
    Info("\n-----%s [%d]-----\n", __FUNCTION__, __LINE__);
    printf("%lu\n", USB_NET_DRIVER_NUM);
    //ftw("/media/sangfor/vdb/study", fn, 0);
    
    struct timeval timeStart, timeEnd, timeSystemStart; 
    gettimeofday(&timeStart, NULL);
    //usleep(3000000);
    
    //unsigned short vid = 61953, pid = 21360;
    unsigned short vid = 0x0b95, pid = 0x772b;
    //readInnerUdevNetDriverVpid(vid, pid);
    //isUdevNetDriverVpid(vid, pid);
    libusb_device *udev = find_udev(vid, pid);
    if (!udev) {
        perror("find_udev");
        return -1;
    }
    
    if (is_ethernet(udev, vid, pid)) {
        LOG_INFO("device 0x%04x 0x%04x is ethernet adapter, we think it is a local device.\n", vid, pid);
    }
    
    gettimeofday(&timeEnd, NULL); 
    double runTime = (timeEnd.tv_sec - timeStart.tv_sec ) + (double)(timeEnd.tv_usec -timeStart.tv_usec)/1000000;  
    printf("\nrunTime is %lf s\n", runTime);
    return 0;
}

/*
static bool is_in_usb_net_driver_list(unsigned short vid, unsigned short pid)
{
    for (int i = 0; i < USB_NET_DRIVER_NUM; i++) {
        if (usb_net_driver_ist[i][0] == vid && usb_net_driver_ist[i][1] == pid) {
            LOG_INFO("device 0x%04x 0x%04x is in usb net driver list", vid, pid);
            return true;
        }
    }
    LOG_INFO("device 0x%04x 0x%04x is not in usb net driver list", vid, pid);
    return false;
}


static bool get_usb_device_path(libusb_device *device, string &udev_path)
{
    assert(device != NULL);
    
    uint8_t ports[MAX_PATH_PORTS_NUM];
    int bus;
    int ports_num;
    
    bus = libusb_get_bus_number(device);
    ports_num = libusb_get_port_numbers(device, ports, MAX_PATH_PORTS_NUM);
    if (ports_num < 0) {
        LOG_ERROR("libusb_get_port_numbers failed");
        return false;
    }

    std::stringstream ss;
    ss << bus;
    ss << "-";
    ss << ports[0];
    for(int i = 1; i < ports_num; i++) {
        ss << ".";
        ss << ports[i];
    }
    udev_path = ss.str();
    LOG_INFO("udev_path: %s\n", udev_path.c_str());
    return true;
}

static bool get_net_symlink_file_path(std::vector<std::string> &net_symlink_file_paths)
{
    struct dirent *st_dirent;
    DIR *dir;
    std::string net_symlink_file_path;
    
    dir = opendir(NET_CLASS_PATH);
    if (dir == NULL) {
        LOG_ERROR("opendir failed, err=%u, %s", errno, strerror(errno));
        return false;
    }
    while ((st_dirent = readdir(dir)) != NULL) {
        if (st_dirent->d_type == DT_LNK) {
            net_symlink_file_path = NET_CLASS_PATH;
            net_symlink_file_path += st_dirent->d_name;
            net_symlink_file_paths.push_back(net_symlink_file_path);
            LOG_DEBUG("net_symlink_file_path: %s", net_symlink_file_path.c_str());
        }
    }
    closedir(dir);
    dir = NULL;
    return true;
}

static bool is_usb_net_device(std::vector<std::string> net_symlink_file_paths, std::string udev_path)
{
    char real_path[MAX_PATH_LEN];
    std::string real_path_str;
    int ret;
    int index;

    std::vector<std::string>::iterator it = net_symlink_file_paths.begin();
    for (; it != net_symlink_file_paths.end(); it++) {
        memset(real_path, 0, MAX_PATH_LEN);
        ret = readlink((*it).c_str(), real_path, MAX_PATH_LEN);
        if (ret == -1) {
            LOG_ERROR("readlink failed, ret=%d, err=%u, %s", ret, errno, strerror(errno));
            return false;
        }

        real_path_str = real_path;
        index = real_path_str.find(udev_path);
        if (index == -1) {
            LOG_DEBUG("real_path: %s, udev_path: %s", real_path, udev_path.c_str());
            continue;
        }
        LOG_DEBUG("real_path: %s, udev_path: %s\n", real_path, udev_path.c_str());
        return true;
    }
    return false;
}
*/