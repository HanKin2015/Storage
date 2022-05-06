/**
* 文 件 名: udev_get_pci.cpp
* 文件描述: 获取USB设备的PCI地址
* 作    者: HanKin
* 备    注: 编译需要安装libusb库,并且需要增加-lusb-1.0参数
* 创建日期: 2021.10.25
* 修改日期：2021.10.25
*
* Copyright (c) 2021 HanKin. All rights reserved.
*/

#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <sys/types.h>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <errno.h>
#include <string.h>
using namespace std;

#ifndef DEBUG
#define DEBUG 0
#endif

#if DEBUG
#define DPRINTF printf
#else
#define DPRINTF(...)
#endif

#define BUF_SIZE 1024

// 获取设备的bus和port
static int get_udev_bus_port_describe(libusb_device *dev, vector<int>& bus_port_desc)
{
    int bus = libusb_get_bus_number(dev);
    bus_port_desc.push_back(bus);
    
    uint8_t ports[BUF_SIZE];
    int ports_num = libusb_get_port_numbers(dev, ports, BUF_SIZE);
    if (ports_num < 0) {
        perror("libusb_get_port_numbers");
        return -1;
    }
    for (int i = 0; i < ports_num; i++) {
        bus_port_desc.push_back(ports[i]);
    }
    return 0;
}

// 获取pci地址
static void get_pci_address(const char *symblink_path, string& pci_addr)
{
    char pci_path[BUF_SIZE];
    int ret = readlink(symblink_path, pci_path, BUF_SIZE);
    if (ret == -1) {
        printf("ret:%d (%s)\n", ret, strerror(errno));
        return;
    }
    DPRINTF("pci_path: %s\n", pci_path);
    
    string pci_path_str = pci_path;
    DPRINTF("pci_path: %s\n", pci_path_str.c_str());
    //int sidx = pci_path_str.find("/0000:"); // 不可取../../../devices/pci0000:00/0000:00:1c.3/0000:04:00.0/usb4/4-1
    int index = pci_path_str.find("/usb");
    if (index == -1) {
        printf("index not found!\n");
        return;
    }
    pci_addr = pci_path_str.substr(index - 7, 7);    // 固定取pci地址长度7位
    DPRINTF("index: %d, pci_addr: %s\n", index, pci_addr.c_str());
    return;
}

// 将pci地址和port拼接成字符串
static void pci_port_string(vector<int>& bus_port_desc, string& pci_port_str)
{
    int size = bus_port_desc.size();
    // at least with a bus number and a port number
    if (size < 2) {
        printf("size = %d, bus = %d\n", size, bus_port_desc[0]);
        pci_port_str = "invalid";
        return;
    }

    // 获取设备的pci地址
    string udev_path = "/sys/bus/usb/devices/";
    std::stringstream ss;
    for (size_t i = 1; i < size - 1; i++) {
        ss << bus_port_desc[i] << ".";
    }
    ss << bus_port_desc[size - 1];
    string port_str = ss.str();
    
    ss.clear();
    ss.str("");
    ss << udev_path << bus_port_desc[0] << "-" << port_str;
    string bus_port_path_str = ss.str();
    DPRINTF("bus_port_path_str: %s\n", bus_port_path_str.c_str());
    
    
    string pci_addr;
    get_pci_address(bus_port_path_str.c_str(), pci_addr);
    pci_port_str = pci_addr + "-" + port_str;
    return;
}

// 枚举USB设备
static void enum_devs(libusb_device **devs)
{
    libusb_device *dev;
    int i = 0;

    while ((dev = devs[i++]) != NULL) {
        struct libusb_device_descriptor desc;
        int r = libusb_get_device_descriptor(dev, &desc);
        if (r < 0) {
            fprintf(stderr, "failed to get device descriptor");
            return;
        }

        DPRINTF("%04x:%04x (bus %d, port %d, device %d, speed %d, class 0x%x)\n",
            desc.idVendor, desc.idProduct, libusb_get_bus_number(dev), 
            libusb_get_port_number(dev), libusb_get_device_address(dev), 
            libusb_get_device_speed(dev), desc.bDeviceClass);
        
        vector<int> bus_port_desc;
        get_udev_bus_port_describe(dev, bus_port_desc);
        
        string pci_port_str;
        pci_port_string(bus_port_desc, pci_port_str);
        printf("pci_port_str: %s\n", pci_port_str.data());
        
        if (pci_port_str == "00:14.0-4.3") {
            int speed = libusb_get_device_speed(dev);
            printf("success!!! speed: %d.\n", speed);
        }
    }
    return;
}

int main(int argc, char *argv[])
{
    libusb_device **devs;
    int r;
    ssize_t cnt;

    r = libusb_init(NULL);
    if (r < 0) {
        perror("libusb_init");
        return r;
    }

    cnt = libusb_get_device_list(NULL, &devs);
    if (cnt < 0) {
        perror("libusb_get_device_list");
        return (int) cnt;
    }

    enum_devs(devs);
    
    libusb_free_device_list(devs, 1);
    libusb_exit(NULL);
    return 0;
}








