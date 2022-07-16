#!/bin/bash
#
# 文 件 名: cp_usbip_driver.sh
# 文件描述: 拷贝文件到指定目录下
# 作    者: HanKin
# 创建日期: 2022.07.06
# 修改日期：2022.07.06
# 
# Copyright (c) 2022 HanKin. All rights reserved.
#

function get_info()
{
	grep -w "$1" /etc/os-release | sed 's/\"//g' | awk -F'=' '{print  $NF}'
}

g_platform=$(get_info ID)

# 拷贝usbip驱动到指定的目录下
function cp_usbip_driver()
{
	#根据平台类型以及内核版本加载对应的usbip驱动
	system_arch=`uname -m`
	kernel_ver=`uname -r`

	#uos系统相同内核版本也会存在差异,非uos系统为空字符串
	uos_ver=''

	#先卸对应的驱动模块
	rmmod usbip-host
	rmmod usbip-core

    echo ${g_platform}

	if [ "${g_platform}" = "uos" ]
	then
		major_ver=`grep -w "MajorVersion" /etc/os-version | sed 's/\"//g' | awk -F'=' '{print  $NF}'`
		if [ "${major_ver}" = "20" ]
			then
				minjor_ver=`grep -w "MinorVersion" /etc/os-version | sed 's/\"//g' | awk -F'=' '{print  $NF}'`
				uos_ver="uos${minjor_ver:0:3}x/"
		fi
	fi
    
    echo ${uos_ver}
}

cp_usbip_driver