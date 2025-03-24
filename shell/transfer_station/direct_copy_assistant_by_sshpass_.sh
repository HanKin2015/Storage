#!/bin/bash
#
# 文 件 名: direct_copy_assistant_by_sshpass.sh
# 文件描述: 支持单个文件拷贝
# 注    意: 需要安装sshpass库
# 作    者: HanKin
# 创建日期: 2025.03.21
# 修改日期：2025.03.21
# 
# Copyright (c) 2025 HanKin. All rights reserved.
#

# 目标地址、用户名、密码
TARGET_IP='172.22.16.56'
TARGET_USER='root'
TARGET_PWD='1'

SINGLE_FILENAME=""
if [ $# -eq 1 ]
then
    SINGLE_FILENAME=$1
fi

FILES_ABSPATH=(
    "/root/code/src/hc_usbmagic2/build/outlib/libusbmagic_common.so"
    "/root/code/src/hc_usbmagic2/build/outlib/libusbmagic_usbredir.so"
    "/root/code/src/hc_usbmagic2/build/outlib/libusbmagic_usbip.so"
    "/root/code/src/hc_usbmagic2/build/outbin/usbmagicd"
    "/root/code/src/hc_session/spice-0.12.5/hc_session"
    "/root/code/src/rapp_session/output/rapp_session"
    "/root/code/src/hc_tray/hc_tray"
    "/root/code/src/hc_tray/hc_tray_ZH.qm"
    "/root/code/src/hc_client/hc_client"
    "/root/code/src/hc_bar/hc_bar"
)

copy_filed_count=0
for FILE_ABSPATH in ${FILES_ABSPATH[*]}
do
    # 检查文件是否存在
    if [[ ! -e "${FILE_ABSPATH}" ]]; then
        echo "文件不存在: ${FILE_ABSPATH}"
        continue
    fi
    
    # 计算目标路径
    target_abspath=""
    case "${FILE_ABSPATH}" in
        *.so)
            echo "${FILE_ABSPATH} 是一个共享库文件 (.so)"
            target_abspath="/usr/local/hankin/hcclient/lib/"
            ;;
        *.qm)
            echo "${FILE_ABSPATH} 是一个 Qt 翻译文件 (.qm)"
            target_abspath="/etc/hankin/hcclient/i18n/"
            ;;
        *)
            # 使用 file 命令判断文件类型
            file_type=$(file -b "${FILE_ABSPATH}")
            if [[ "${file_type}" == *"executable"* ]]; then
                echo "${FILE_ABSPATH} 是一个二进制可执行文件"
                target_abspath="/usr/local/hankin/hcclient/bin/"
            else
                echo "${FILE_ABSPATH} 是其他类型的文件: ${file_type}"
            fi
            ;;
    esac
    
    if [ -n "${SINGLE_FILENAME}" ]
    then
        if [ "${SINGLE_FILENAME}" != $(basename "${FILE_ABSPATH}") ]
        then
            continue
        fi
    fi

    # 拷贝到测试机
    sshpass -p ${TARGET_PWD} scp ${FILE_ABSPATH} ${TARGET_USER}@${TARGET_IP}:${target_abspath}
    if [ $? -ne 0 ]; then
        echo "${FILE_ABSPATH} 拷贝失败"
        ((copy_filed_count++))
    fi
    echo ''
done
echo "全部拷贝完成! 其中${copy_filed_count}个文件拷贝失败!"