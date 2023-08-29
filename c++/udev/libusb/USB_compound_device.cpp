/**
* 文 件 名: USB_compound_device.cpp
* 文件描述: USB Compound Device，USB复合设备，内嵌Hub和多个Function，每个Function都相当于一个独立的USB外设，有自己的PID/VID/DID
* 作    者: HanKin
* 备    注: 编译需要安装libusb库,并且需要增加-lusb-1.0参数  g++ USB_compound_device.cpp -lusb-1.0 -std=c++11
*           仔细想了想，好像还是不能通过代码来判断多个设备是不是属于一个设备（复合设备）
*           并不能通过父系hub路径相同来判断是一个设备，也可能是物理机自带hub
* 创建日期: 2023.08.29
* 修改日期：2023.08.29
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <assert.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <sstream>
#include <vector>
#define HUB_INTERFACE_CLASS 0x09

int get_usb_device_path(libusb_device *device, std::string &path)
{
    uint8_t ports[BUFSIZ];
    int ret;
    int bus;
    int i;
    std::stringstream ss;

    assert(device != NULL);

    bus = libusb_get_bus_number(device);

    ret = libusb_get_port_numbers(device, ports, sizeof(ports));
    if(ret < 0){
        printf("cannot get device path %s\n", libusb_strerror(ret));
        return -1;
    }

    ss << bus;
    ss << "-";
    ss << (unsigned int )ports[0];


    for(i = 1;i<ret;i++){
        ss << ".";
        ss << (unsigned int )ports[i];
    }

    path = ss.str();
    return 0;
}

int get_interface_class(libusb_device *dev, std::vector<uint8_t> &iface_class)
{
    struct libusb_device_descriptor dev_desc;
    libusb_get_device_descriptor(dev, &dev_desc);
    
    int config_cnt = dev_desc.bNumConfigurations;
    for (int conf_idx = 0; conf_idx < config_cnt; conf_idx++) {
        struct libusb_config_descriptor *conf_desc = NULL;
        libusb_get_config_descriptor(dev, conf_idx, &conf_desc);
        assert(conf_desc);
        int iface_cnt = conf_desc->bNumInterfaces;
        for (int iface_idx = 0; iface_idx < iface_cnt; ++iface_idx) {
            const struct libusb_interface_descriptor *iface_desc = NULL;
            iface_desc = &(conf_desc->interface[iface_idx].altsetting[0]);
            assert(iface_desc);
    
            int ep_cnt = iface_desc->bNumEndpoints;
            for (int ep_idx = 0; ep_idx < ep_cnt; ++ep_idx) {
                const struct libusb_endpoint_descriptor *ep_desc = NULL;
                ep_desc = &(iface_desc->endpoint[ep_idx]);
                assert(ep_desc);
            }
            iface_class.push_back(iface_desc->bInterfaceClass);
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    libusb_context *ctx = NULL;
    int result = libusb_init(&ctx);
    assert(result >= 0);
    
    // 获取设备列表
    struct libusb_device **devs;
    int dev_cnt = (int)libusb_get_device_list(ctx, &devs);
    assert(dev_cnt>=0 && devs);
    
    // 枚举
    for (int i = 0; i < dev_cnt; ++i) {
        // 获取当前设备vpid
        struct libusb_device_descriptor desc;
        libusb_get_device_descriptor(devs[i], &desc);
        
        // 获取父设备
        libusb_device *parent_dev = NULL;
        parent_dev = libusb_get_parent(devs[i]);
        if (parent_dev == NULL) {
            printf("%04x:%04x has no parent device\n\n", desc.idVendor, desc.idProduct);
            continue;
        }
        
        uint8_t bus_number = libusb_get_bus_number(parent_dev);
        uint8_t port_number = libusb_get_port_number(parent_dev);
        struct libusb_device_descriptor parent_desc;
        libusb_get_device_descriptor(parent_dev, &parent_desc);
        printf("%04x:%04x has parent device %04x:%04x(%d-%d)\n", desc.idVendor, desc.idProduct,
            parent_desc.idVendor, parent_desc.idProduct, bus_number, port_number);
        
        std::string path = "";
        get_usb_device_path(devs[i], path);
        printf("%04x:%04x device path is %s\n", desc.idVendor, desc.idProduct, path.c_str());
        
        std::vector<uint8_t> interface_class;
        get_interface_class(devs[i], interface_class);
        bool is_hub = false;
        for (uint8_t iface_class : interface_class) {
            if (iface_class == HUB_INTERFACE_CLASS) {
                is_hub = true;
                break;
            }
        }
        if (is_hub) {
            printf("%04x:%04x is a hub device\n\n", desc.idVendor, desc.idProduct);
        } else {
            printf("%04x:%04x is a usb device\n\n", desc.idVendor, desc.idProduct);
        }
    }
    
    libusb_exit(ctx);
    return 0;
}