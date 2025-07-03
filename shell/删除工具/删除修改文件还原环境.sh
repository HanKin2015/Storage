#!/bin/bash

BINARY_FOLDER_PATH="/usr/local/bin/"
LIBRARY_FOLDER_PATH="/usr/local/lib/"
LOG_FOLDER_PATH="/var/log/hankin/"
CONFIGURATION_FOLDER_PATH="/etc/hankin/"
SOCKET_FOLDER_PATH="/run/hankin/"
CONF_FOLDER_PATH="/etc/hankin/"
SERVICE_FOLDER_PATH="/lib/systemd/system/"

BINARY_FILE_NAMES=(
    "usbhankind"
    "test_ctrl_client"
    "hankin-hankin"
    "hankin-bar"
)
LIBRARY_FILE_NAMES=(
    "libusbhankin_common.so"
    "libusbhankin_usbredir.so"
    "libusbhankin_ctrl.so"
    "libusbredirhost.so.1.0.0"
    "libusbredirparser.so.1.0.0"
    "libusb-1.0.so.0.1.0"
    "libcameraclnt.so"
)
LOG_FILE_NAMES=(
    "usbhankind.log"
    "usbhankin_redir.log"
    "usbhankin_ctrl.log"
)
CONFIGURATION_FILE_NAMES=(
    "usbhankin_log.config"
)
SERVICE_FILE_NAMES=(
    "vdi_usbhankind.service"
)

systemctl stop vdi_usbhankind

rm_failed_number=0
rm_succeed_number=0
function remove_files_or_folder()
{
    if [ $# -eq 1 ]
    then
        local folder_path=$1
        echo "尝试删除文件夹: ${folder_path}"
        rm -r ${folder_path}
        if [ $? -ne 0 ]; then
            echo "${folder_path} 删除失败"
            ((rm_failed_number++))
        else
            ((rm_succeed_number++))
        fi
        return
    fi

    local folder_path=$1
    shift  # 移除第一个参数，剩下的都是文件名
    local file_names=("$@")  # 将剩下的参数作为数组
    for file_name in ${file_names[@]}
    do
        local full_path="${folder_path}${file_name}"
        echo "尝试删除文件: ${full_path}"
        rm ${full_path}
        if [ $? -ne 0 ]; then
            echo "${file_name} 删除失败"
            ((rm_failed_number++))
        else
            ((rm_succeed_number++))
        fi
    done
}

remove_files_or_folder ${BINARY_FOLDER_PATH} ${BINARY_FILE_NAMES[@]}
remove_files_or_folder ${LIBRARY_FOLDER_PATH} ${LIBRARY_FILE_NAMES[@]}
remove_files_or_folder ${LOG_FOLDER_PATH} ${LOG_FILE_NAMES[@]}
remove_files_or_folder ${CONFIGURATION_FOLDER_PATH} ${CONFIGURATION_FILE_NAMES[@]}
remove_files_or_folder ${SOCKET_FOLDER_PATH}
remove_files_or_folder ${CONF_FOLDER_PATH}
remove_files_or_folder ${SERVICE_FOLDER_PATH} ${SERVICE_FILE_NAMES[@]}

echo "全部拷贝完成! 其中${rm_failed_number}个文件(夹)删除失败，${rm_succeed_number}个删除成功!"