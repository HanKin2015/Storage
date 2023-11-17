#!/bin/bash
#
# 文 件 名: usb_device_info_detect.sh
# 文件描述: usb设备部分信息检测
# 作    者: HanKin
# 创建日期: 2023.11.15
# 修改日期：2023.11.15
# 
# Copyright (c) 2023 HanKin. All rights reserved.
#

# 脚本参数
#set -euxo pipefail

# 全局变量
g_otg_bus_number='001'
g_dev_bus_bumber='000'
g_driver_type='0'
g_is_usbfs_driver='false'

# 显示打包脚本的具体版本信息
show_version()
{
    echo "version: 1.0"
}

show_help()
{
    cat<<EOF
用法: ${0} [options]

选项：    
  -h,   显示帮助信息
  -V,   显示当前命令版本
  -d pack_dir     打包目录名（具体见特别说明）
  -v version      基础版本号
EOF
}

# 获取otg的总线id
get_otg_bus_number()
{
    g_otg_bus_number=`lsusb | grep usb20_otg | awk '{printf $1}' | awk -F'/' '{printf $5}'`
    echo "g_otg_bus_number: ${g_otg_bus_number}"
    return 0
}

# 获取usb设备的总线id
get_dev_bus_number()
{
    local vid_pid=$1
    g_dev_bus_number=`lsusb | grep ${vid_pid} | awk '{printf $2}'`
    echo "g_dev_bus_number: ${g_dev_bus_number}"
    return 0
}

# 获取usb主控驱动类型
get_driver_type()
{
    g_driver_type=`cat /sys/module/dwc_plat_dev/parameters/dwc_driver`
    g_driver_type=`cat /sys/module/xhci_hcd/coresize`
    echo "g_driver_type: ${g_driver_type}"
    return 0
}

# 判断是否加载是usbfs驱动
is_usbfs_driver()
{
    local vid_pid=$1
    
    # 获取设备端口编号
    raw_port_number=$(lsusb | grep ${vid_pid} | head -n 1 | awk '{print $4}')
    echo "raw_port_number: ${raw_port_number}"
    
    # 去掉尾部冒号
    port_number=${raw_port_number%%[^0-9]}
    
    # 去掉编号前缀0
    port_number=$(echo -e $port_number | sed -r 's/0*([0-9])/\1/')
    echo "port_number: ${port_number}"
    
    driver_type=`lsusb -t | grep "Dev ${port_number}" | head -n 1 | awk -F',' '{printf $(NF-1)}' | awk 'BEGIN{FS="="} {print $2}'`
    echo "driver_type: ${driver_type}"
    if [ -z "${driver_type}" ]
    then
        echo "not found ${vid_pid} device driver"
        return 1
    fi
    
    if [ ${driver_type} = "usbfs" ]
    then
        g_is_usbfs_driver='true'
    fi
    echo "g_is_usbfs_driver: ${g_is_usbfs_driver}"
    return 0
}
    

# 解析用户传递的参数
while getopts "hVou:di:" arg 
do
    case $arg in
        h)
            show_help
            exit 0
            ;;
        V)
            show_version
            exit 0
            ;;
        o)
            get_otg_bus_number
            ;;
        u)
            get_dev_bus_number "$OPTARG"
            ;;
        d)
            get_driver_type
            ;;
        i)
            is_usbfs_driver "$OPTARG"
            ;;
        ?)  #当有不认识的选项的时候arg为?
            echo "unkonw argument"
            show_help
            exit 1
            ;;
    esac
done

exit 0