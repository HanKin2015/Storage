#!/bin/bash
#
# 文 件 名: preinst.sh
# 文件描述: 安装包前置操作
# 作    者: HanKin
# 创建日期: 2024.01.15
# 修改日期：2024.01.15
# 
# Copyright (c) 2024 HanKin. All rights reserved.
#

UNPACK="/tmp"
PWD=`pwd`
g_opt=$1
g_arg_count=$#
g_is_ok=0
g_allow_space=200000

CHECK_ARGS()
{
    if [ ${g_arg_count} -ne 1 ] || [[ "$g_opt" != "install" && "$g_opt" != "uninstall" ]]
    then
	echo ""
	echo "EX: ./linux-xxx.bin install or uninstall"
	echo ""
	exit 1;
    fi

    opt_user=`whoami`
    if [ "$opt_user"x != "root"x ]
    then
        echo ""
        echo "==============================="
        echo ""
        echo "  Please use root permission ! " 
        echo ""
        echo "==============================="
        echo ""
            exit -1
    fi
}

CHECK_SPACE()
{
	space=`df -l / |grep -F "/" | awk '{print $4}'`
	if [ ${space} -lt ${g_allow_space} ];then
		echo ""
		echo "=========================================="
		echo ""
		echo "Free disk space is less than 200MB,"
	 	echo "please expand the disk capacity first !"
		echo ""
		echo "=========================================="
		echo ""
		exit 1
	fi
}

UNPACK_FILE()
{
    # 这里是本脚本的行数往后就是安装包zip的内容
    tail -n +120 "$0" > tmp.zip
    unzip tmp.zip -d ${UNPACK}
    if [ $? -ne 0 ]; then
        echo $LOGTAG "unzip tmp.zip failed"
        exit 1
    fi
    echo "[1]---------------package: unpack file success----------------"
}

INSTALL_FILE()
{
    chmod a+x ${UNPACK}/install.sh
    ${UNPACK}/install.sh $g_opt
    
    if [ $? -ne 0 ]
    then
    	echo "[2]------------package: install/uninstall file failed----------------"
    else
    	echo "[2]------------package: install/uninstall file success----------------"
		g_is_ok=1
    fi
}
CLEAR_SOURCE_FILE()
{
    rm -rf ${UNPACK}/install.sh
    rm -rf ${PWD}/tmp.zip
    rm -rf ${UNPACK}/bin

    echo "[3]---------------package: clear resource success----------------"
}

REBOOT_ACTION()
{
    echo ""
    echo "=================================================================="
    echo "=================================================================="
    echo "---------------- Please reboot your system ! ---------------------"
    echo "=================================================================="
    echo "=================================================================="
    echo ""
    echo ""
 
    exit 0
}

###############################################################################
CHECK_ARGS
CHECK_SPACE
UNPACK_FILE
INSTALL_FILE
CLEAR_SOURCE_FILE

if [ $g_is_ok -eq 1 ] && [ "$g_opt" = "install" ]
then
	REBOOT_ACTION
fi

exit 0 