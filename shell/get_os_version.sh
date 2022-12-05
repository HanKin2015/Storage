#!/bin/bash
#
# 文 件 名: get_os_version.sh
# 文件描述: 获取操作系统信息
# 作    者: HanKin
# 创建日期: 2022.12.05
# 修改日期：2022.12.05
# 
# Copyright (c) 2022 HanKin. All rights reserved.
#

function get_info()
{
    grep -w "$1" /etc/os-release | sed 's/\"//g' | awk -F'=' '{print $NF}'
}

# 获取架构以及内核版本
system_arch=`uname -m`
kernel_ver=`uname -r`
echo ${system_arch} ${kernel_ver}

# uos系统相同内核版本也会存在差异,非uos系统为空字符串
uos_ver=''

# 获取系统平台
g_platform=$(get_info ID)
echo ${g_platform}

if [ "${g_platform}" = "uos" ]
then
    major_ver=`grep -w "MajorVersion" /etc/os-version | sed 's/\"//g' | awk -F'=' '{print $NF}'`
    if [ "${major_ver}" = "20" ]
    then
        minjor_ver=`grep -w "MinorVersion" /etc/os-version | sed 's/\"//g' | awk -F'=' '{print $NF}'`
        if [ "${system_arch}" = "aarch64" ] && [ "${minjor_ver}" = "1032" ]
        then
            uos_ver="uos1032/"
        elif [ "${system_arch}" = "x86_64" ] && [ "${minjor_ver}" = "1031" ]
        then
            uos_ver="uos1031/"
        else
            uos_ver="uos${minjor_ver:0:3}x/"
        fi
    fi
fi
echo ${uos_ver}