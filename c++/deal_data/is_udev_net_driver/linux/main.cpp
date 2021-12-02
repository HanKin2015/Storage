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
inline bool in_usb_net_driver_list(unsigned short vid, unsigned short pid)
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
static bool is_usb_net_device(vector<string> symlink_file_paths, string udev_path)
{
    Info("\n-----%s [%d]-----\n", __FUNCTION__, __LINE__);
    
    char real_path[MAX_PATH_LEN];
    string real_path_str;
    int ret;
    int index;

    for (string symlink_file_path : symlink_file_paths) {
        memset(real_path, 0, MAX_PATH_LEN);
        ret = readlink(symlink_file_path.c_str(), real_path, MAX_PATH_LEN);
        if (ret == -1) {
            Info("readlink failed, ret:%d (%s)", ret, strerror(errno));
            return false;
        }

        real_path_str = real_path;
        index = real_path_str.find(udev_path);
        if (index == -1) {
            Info("index not found, real_path: %s, udev_path: %s\n", real_path, udev_path.c_str());
            continue;
        }
        Info("real_path: %s, udev_path: %s\n", real_path, udev_path.c_str());
        return true;
    }
    return false;
}

#define MAX_PORTS_NUM 256
static void get_usb_device_path(libusb_device *udev, string &udev_path)
{
    Info("\n-----%s [%d]-----\n", __FUNCTION__, __LINE__);
    assert(udev != NULL);
    
    uint8_t ports[MAX_PORTS_NUM];
    int bus = libusb_get_bus_number(udev);
    
    int ports_num = libusb_get_port_numbers(udev, ports, MAX_PORTS_NUM);
    if (ports_num < 0) {
        perror("libusb_get_port_numbers");
        return;
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
    return;
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

#include <dirent.h>
#include <vector>
int get_symlink_file_path(vector<string> &symlink_file_paths)
{
    Info("\n-----%s [%d]-----\n", __FUNCTION__, __LINE__);
    
    struct dirent *ptr;
    DIR *dir;
    string PATH = "/sys/class/net/";
    
    dir = opendir(PATH.c_str());
    cout << "文件列表: "<< endl;
    while ((ptr = readdir(dir)) != NULL) {
        //cout << ptr->d_name << ' ' << ptr->d_type << endl;
        if (ptr->d_type == DT_LNK) {
            printf("name: %s, type: %d\n", ptr->d_name, ptr->d_type);
            string tmp = PATH + ptr->d_name;
            symlink_file_paths.push_back(tmp);
            printf("path: %s\n", tmp.data());
        }
    }
    return 0;
}

int main()
{
    Info("\n-----%s [%d]-----\n", __FUNCTION__, __LINE__);
    
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
    
    assert(udev != NULL);
    
    vector<string> symlink_file_paths;
    get_symlink_file_path(symlink_file_paths);

    string udev_path;
    get_usb_device_path(udev, udev_path);
    if (udev_path.empty()) {
        perror("get_usb_device_path");
        return -2;;
    }
    
    bool ret = is_usb_net_device(symlink_file_paths, udev_path);
    if (ret) {
        Info("this usb device[0x%04x:0x%04x] is usb net device.\n", vid, pid);
    }
    
    ret = in_usb_net_driver_list(vid, pid);
    if (ret) {
        Info("this usb device[0x%04x:0x%04x] in usb net driver list.\n", vid, pid);
    }
    
    gettimeofday(&timeEnd, NULL); 
    double runTime = (timeEnd.tv_sec - timeStart.tv_sec ) + (double)(timeEnd.tv_usec -timeStart.tv_usec)/1000000;  
    printf("\nrunTime is %lf s\n", runTime);
    return 0;
}