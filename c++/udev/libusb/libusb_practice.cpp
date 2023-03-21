/**
* 文 件 名: libusb_practice.cpp
* 文件描述: libusb实战练习
* 作    者: HanKin
* 备    注: 编译需要安装libusb库,并且需要增加-lusb-1.0 -lpthread -lm参数
* 创建日期: 2021.10.14
* 修改日期：2021.10.14
*
* Copyright (c) 2021 HanKin. All rights reserved.
*/

#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <sys/types.h>
#include <iostream>
#include <vector>
#include <sstream>

#define BUFFERSIZE 15

static int get_usbdevice_port_describe(libusb_device *dev, std::vector<int> &describe_ports)
{
    uint8_t ports[BUFFERSIZE];

    int bus = libusb_get_bus_number(dev);
    int ports_num = libusb_get_port_numbers(dev, ports, BUFFERSIZE);

    if (ports_num < 0) {
        printf("ports_num letter than 0, ports_num: %d", ports_num);
        return -1;
    }

    describe_ports.push_back(bus);

    printf("bus: %d, ports_num: %d", bus, ports_num);
    for (int i = 0; i < ports_num; i++) {
        describe_ports.push_back(ports[i]);
        printf(", %d", ports[i]);
    }
    printf("\n");
    return 0;
}

static void port_path_string(std::vector<int> &port_vec, std::string &port_str)
{
    std::stringstream ss;
    int size = 0;

    size = port_vec.size();

    // at least with a bus number and a port number(有设备)
    if (size < 2) {
        port_str = "invalid";
        perror("port_str");
        return;
    }
    
    // bus-port1.port2.port3
    ss << port_vec[0] << "-";
    for (size_t i = 1; i < size - 1; i++) {
        ss << port_vec[i] << ".";
    }
    ss << port_vec[size - 1];
    port_str = ss.str();
    
    printf("port_str: %s\n", port_str.data());
    return;
}


static void get_port_bind_usb_channel(libusb_device *dev)
{
    std::vector<int> dev_ports_vec;
    std::string dev_ports_str;
    std::string bind_ports_str;

    if (get_usbdevice_port_describe(dev, dev_ports_vec) !=0) {
        perror("get_usbdevice_port_describe fialed");
        return;
    }

    port_path_string(dev_ports_vec, dev_ports_str);

    //printf("current usb_path:%s, ports_array.size(): %d", dev_ports_str.c_str(), ports_array.size());
    return;
}

static void enumerate_device(libusb_device **devs)
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

#if 0
        printf("%04x:%04x (bus %d, port %d, device %d, speed %d, class 0x%x)\n",
            desc.idVendor, desc.idProduct, libusb_get_bus_number(dev), 
            libusb_get_port_number(dev), libusb_get_device_address(dev), 
            libusb_get_device_speed(dev), desc.bDeviceClass);
#endif

        get_port_bind_usb_channel(dev);
    }
    return;
}

int main(int argc, char *argv[])
{
    libusb_device **devs;
    int ret;
    ssize_t cnt;

    ret = libusb_init(NULL);
    if (ret < 0) {
        perror("ret");
        return ret;
    }

    cnt = libusb_get_device_list(NULL, &devs);
    if (cnt < 0) {
        perror("cnt");
        return (int) cnt;
    }
    
    printf("cnt: %ld\n", cnt);

    enumerate_device(devs);
    
    libusb_free_device_list(devs, 1);
    libusb_exit(NULL);
    return 0;
}