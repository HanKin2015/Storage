#!/bin/bash
#
# 文 件 名: log_interface.sh
# 文件描述: 日志接口
# 作    者: HanKin
# 创建日期: 2024.10.21
# 修改日期：2024.10.21
# 
# Copyright (c) 2024 HanKin. All rights reserved.
#

# 定义日志文件路径
LOG_FILE="/var/log/hj.log"
 
# 函数：用于打印日志信息
log_message() {
    local message="$1"
    echo "$(date '+%Y-%m-%d %H:%M:%S') - $message" >> "$LOG_FILE"
}
 
# 打印日志
log_message "这是一条日志信息。"
 
# 你还可以使用printf进行格式化输出
printf "%s - %s\n" "$(date '+%Y-%m-%d %H:%M:%S')" "这是另一条日志信息。"

log_info() {
    MODULENAME=$(basename $0)
    LOGFILE=/tmp/logfile-`date +%Y%m%d`

    datetime=`date "+%Y-%m-%d %H:%M:%S"`
    $1
    result=$?
    if [ $result -eq 0 ];then
      echo -e "\033[32m [ ${datetime} ] - [ INFO ] -  ${MODULENAME} - $1 - $result  \033[0m" | tee -a ${LOGFILE}
    else
      echo -e "\033[31m [ ${datetime} ] - [ ERROR ] - ${MODULENAME} - $1 - $result  \033[0m" | tee -a ${LOGFILE}
    fi
}
log_info "echo abc"
log_info "abcd"
test() {
    who
}
log_info "test"